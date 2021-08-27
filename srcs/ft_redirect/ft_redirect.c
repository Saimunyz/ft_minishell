/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:22:02 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/25 21:15:29 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_parse_redir(char *redir, int type, char *sign)
{
	t_file	*f;
	char	*space;

	f = malloc(sizeof(t_file));
	f->mode = type;
	f->type = sign;
	while (*redir == *sign)
		ft_memmove(redir, redir + 1, ft_strlen(redir));
	if (*redir == ' ')
		ft_memmove(redir, redir + 1, ft_strlen(redir));
	space = ft_strnstr(redir, " ", ft_strlen(redir));
	if (space)
	{
		f->filename = ft_substr(redir, 0, space - redir);
		ft_memmove(redir, redir + (space - redir), ft_strlen(redir));
	}
	else
	{
		f->filename = ft_strdup(redir);
		ft_memmove(redir, redir + ft_strlen(redir), ft_strlen(redir));
	}
	return (ft_lstnew(f));
}

void	ft_free_file(void *file)
{
	t_file	*f;

	f = (t_file *)file;
	free(f->filename);
	free(file);
	file = NULL;
}

static void	ft_start_redirect(t_cmd *a_cmd, t_memory *mem)
{
	ft_commands(a_cmd, 0, mem);
	ft_lstclear(&a_cmd->files, ft_free_file);
	a_cmd->files = NULL;
	unlink("temporary");
	if (errno != 0)
		errno = 0;
	ft_clear_arr(a_cmd->cmd);
	a_cmd->cmd = (char **) malloc (sizeof (char **) * 3);
	a_cmd->echo = 1;
	a_cmd->cmd[0] = ft_strdup("echo");
	a_cmd->cmd[1] = ft_strdup("-n");
	a_cmd->cmd[2] = NULL;
}

void	ft_parse_redirect_2(char** str, char *spec_char, int i, t_list	**files)
{
	*spec_char = ft_spec_char(*spec_char, str[0][i]);
	if (str[0][i] == ' ' && (str[0][i + 1] == '>' || str[0][i + 1] == '<') && !(*spec_char))
		ft_memmove((*str) + i, (*str) + i + 1, ft_strlen(str[0] + i));
	if (str[0][i] == '>' && str[0][i + 1] == '>' && !(*spec_char))
		ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 1089, ">"));
	else if (str[0][i] == '<' && str[0][i + 1] == '<' && !(*spec_char))
		ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 0, "<<"));
	else if (str[0][i] == '>' && !(*spec_char))
		ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 577, ">"));
	if (str[0][i] == '<' && !(*spec_char))
		ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 0, "<"));
}

void	ft_parse_redirect(char** str, t_memory *mem, t_cmd *a_cmd)
{
	t_list	*files;
	int		i;
	char spec_char;

	spec_char = 0;
	i = 0;
	files = NULL;
	while (str[0][i])
	{
		ft_parse_redirect_2(str, &spec_char, i, &files);
		i++;
	}
	a_cmd->files = files;
	a_cmd->cmd = ft_parse_strings(str[0]);
	if (a_cmd->files)
	{
		a_cmd->red = 1; //Сергей 23.08.21
		ft_start_redirect(a_cmd, mem);
	} else
		a_cmd->red = 0; //Сергей 23.08.21
}

char	*ft_read_input(char *stop)
{
	char	*str;
	char	*line;
	char	*tmp;
	char	*delim;
	int		fd;

	str = (char *)malloc(sizeof(char) * 10000);
	delim = ft_strjoin(stop, "\n");
	line = ft_strdup("");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		fd = read(STDIN_FILENO, str, 10000);
		str[fd] = '\0';
		if (!ft_strncmp(str, delim, ft_strlen(str)))
			break;
		tmp = ft_strjoin(line, str);
		free(line);
		line = tmp;
	}
	free(str);
	free(delim);
	return (line);
}

void	ft_here_document(t_file *f)
{
	int		fd;
	char	*line;
	int		orig;

	line = ft_read_input(f->filename);
	//ft_change_var(&line, mem);
	fd = open("temporary", O_WRONLY | O_CREAT, 0755);
	orig = dup(1);
	dup2(fd, 1);
	ft_putstr_fd(line, 1);
	dup2(orig, 1);
	close(fd);
	free(line);
	fd = open("temporary", O_RDONLY, 0755);
	dup2(fd, 0);
	close(fd);
}

int	ft_other_redirects(t_file *file)
{
	int	fd;

	fd = open(file->filename, file->mode, 0755);
	if (fd == -1)
	{
		printf("%s: No such file or directory\n", file->filename);
		return (fd);
	}
	if (!ft_strncmp(file->type, ">", ft_strlen(file->type)))
		dup2(fd,1);
	else
		dup2(fd,0);
	close(fd);
	return (fd);
}

int		ft_check_filename(t_list *lst)
{
	t_list	*tmp;
	t_file	*f;
	int		len;

	tmp = lst;
	while (tmp)
	{
		f = ((t_file*)tmp->content);
		len = ft_strlen(f->filename);
		if (ft_strchr(f->filename, '<') || ft_strchr(f->filename, '>') || len == 0)
		{
			printf("syntax error near unexpected token `%s'\n", f->filename);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_redirect(t_cmd *cmd, t_memory *mem)
{
	int		fd;
	t_list	*tmp;
	t_file	*f;
	char 	**env;

	tmp = cmd->files;
	if (ft_check_filename(tmp))
		return;
	while (tmp)
	{
		f = ((t_file*)tmp->content);
		if (!ft_strncmp(f->type, "<<", ft_strlen(f->type)))
			ft_here_document(f);
		else
		{
			fd = ft_other_redirects(f);
			if (fd == -1)
				return;
		}
		tmp = tmp->next;
	}
	env = ft_lst2str(mem->env); //22.08.21 free
	if (cmd->cmd[0]) //Сергей 25.08.21
		ft_start_commands(cmd->cmd, mem, 0, env);
	ft_clear_arr(env);; //22.08.21 free
}