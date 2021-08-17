/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:22:02 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/17 18:12:29 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_parse_redir(char *redir, int type, char sign)
{
	t_file	*f;
	char	*space;

	f = malloc(sizeof(t_file));
	f->mode = type;
	f->type = sign;
	while (*redir == sign)
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
	//int	i;

	//i = 0;
	ft_commands(a_cmd, 0, mem);
	ft_lstclear(&a_cmd->files, ft_free_file);
	a_cmd->files = NULL;
	//ft_redirect(a_cmd, mem);
	// while (a_cmd->cmd[i])
	// 	free(a_cmd->cmd[i++]);
	a_cmd->cmd[0] = ft_strdup("echo");
	a_cmd->cmd[1] = ft_strdup("-n");
	a_cmd->cmd[2] = NULL;
}

void	ft_parse_redirect(char** str, t_memory *mem, t_cmd *a_cmd)
{
	t_list	*files;
	int		i;

	i = 0;
	files = NULL;
	while (str[0][i])
	{
		if (str[0][i] == ' ' && (str[0][i + 1] == '>' || str[0][i + 1] == '<'))
			ft_memmove((*str) + i, (*str) + i + 1, ft_strlen(str[0] + i));
		if (str[0][i] == '>' && str[0][i + 1] == '>')
			ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 1089, '>'));
		else if (str[0][i] == '>')
			ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 577, '>'));
		if (str[0][i] == '<')
			ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 0, '<'));
		// else if (str[0][i] == '<' && str[0][i + 1] == '<')
		// 	ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 0, '<'));
		i++;
	}
	a_cmd->files = files;
	a_cmd->cmd = ft_parse_strings(str[0]);
	if (a_cmd->files)
		ft_start_redirect(a_cmd, mem);
}

char	*ft_read_file(int fd)
{
	int		ret;
	char	*line;
	char	*text;
	char	*tmp;

	ret = get_next_line(fd, &text);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strjoin(text, line);
		free(line);
		free(text);
		text = tmp;
	}
	return (text);
}

void	ft_redirect(t_cmd *cmd, t_memory *mem)
{
	int		fd;
	t_list	*tmp;
	t_file	*file;

	tmp = cmd->files;
	while (tmp)
	{
		file = ((t_file*)tmp->content);
		fd = open(file->filename, file->mode, 0755);
		if (file->type == '>')
			dup2(fd,1);
		else
			dup2(fd,0);
		close(fd);
		tmp = tmp->next;
	}
	ft_start_commands(cmd->cmd, mem);
}
