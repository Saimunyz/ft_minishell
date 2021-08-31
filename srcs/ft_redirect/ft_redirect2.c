/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:00:09 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/31 16:21:29 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input(char *stop)
{
	char	*str;
	char	*line;
	char	*tmp;
	char	*delim;
	int		fd;

	str = (char *)malloc(sizeof(char) * 10000);
	ft_check_errno();
	delim = ft_strjoin(stop, "\n");
	line = ft_strdup("");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		fd = read(STDIN_FILENO, str, 10000);
		str[fd] = '\0';
		if (!ft_strncmp(str, delim, ft_strlen(str)))
			break ;
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
	fd = open(".temporary", O_WRONLY | O_CREAT, 0755);
	orig = dup(1);
	dup2(fd, 1);
	ft_putstr_fd(line, 1);
	dup2(orig, 1);
	close(fd);
	free(line);
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
		dup2 (fd, 1);
	else
		dup2 (fd, 0);
	close (fd);
	return (fd);
}

int	ft_check_filename(t_list *lst)
{
	t_list	*tmp;
	t_file	*f;
	int		len;

	tmp = lst;
	while (tmp)
	{
		f = ((t_file *) tmp->content);
		len = ft_strlen(f->filename);
		if (ft_strchr(f->filename, '<') || ft_strchr(f->filename, '>') \
			|| len == 0)
		{
			if (f->filename && f->filename[0] == '\0')
				printf("syntax error near unexpected token `newline'\n");
			else
				printf("syntax error near unexpected token `%s'\n", f->filename);
			g_error = 258;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_redirect(t_cmd *cmd, t_memory *mem, char	**env)
{
	int		fd;
	t_list	*tmp;
	t_file	*f;
//	char	**env;

	tmp = cmd->files;
	while (tmp)
	{
		f = ((t_file *) tmp->content);
		if (!ft_strncmp(f->type, "<<", ft_strlen(f->type)))
			ft_here_document(f);
		else
		{
			fd = ft_other_redirects(f);
			if (fd == -1)
				return ;
		}
		tmp = tmp->next;
	}
	if (cmd->red_d_l)
	{
		fd = open(".temporary", O_RDONLY, 0755);
		dup2(fd, 0);
		close(fd);
		/////
		if (cmd->p_next)
		{
			dup2(cmd->fd[1], 1);
			close(cmd->fd[0]);
			close(cmd->fd[1]);
		}
		//////
	}


//	env = ft_lst2str(mem->env);
	if (cmd->cmd[0])
		ft_start_commands(cmd->cmd, mem, 0, env);
//	ft_clear_arr(env);
}
