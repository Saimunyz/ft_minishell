/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:22:02 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/14 21:09:44 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_simple_redirect(char *filename, char *cmd)
// {

// }

t_list	*ft_parse_right_redir(char *redir, int type)
{
	t_file	*f;
	char	*space;

	f = malloc(sizeof(t_file));
	f->mode = type;
	while (*redir == '>')
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


t_list	*ft_parse_redirect(char** str)
{
	t_list	*files;
	//t_list	*file_to_read;
	int		i;

	i = 0;
	files = NULL;
	while (str[0][i])
	{
		if (str[0][i] == ' ' && str[0][i + 1] == '>')
			ft_memmove((*str) + i, (*str) + i + 1, ft_strlen(str[0] + i));
		if (str[0][i] == '>' && str[0][i + 1] == '>')
			ft_lstadd_back(&files, ft_parse_right_redir(str[0] + i, 1089));
		else if (str[0][i] == '>')
			ft_lstadd_back(&files, ft_parse_right_redir(str[0] + i, 577));
		i++;
	}
	return (files);
}

void	ft_redirect(t_list *files, t_cmd cmd, t_memory *mem)
{
	int		fd;
	int		original;
	int		mode;
	char	*filename;
	int		i;

	original = dup(1);
	while (files)
	{
		mode = ((t_file *)files->content)->mode;
		filename = ((t_file *)files->content)->filename;
		fd = open(filename, mode, 0755);
		if (!files->next)
		{
			dup2(fd,1);
			//ft_putstr_fd("\n", 1);
			ft_start_commands(cmd.cmd, mem);
		}
		close (fd);
		files = files->next;
	}
	dup2(original, 1);
	i = 0;
	while (cmd.cmd[i])
		free(cmd.cmd[i++]);
	cmd.cmd[0] = ft_strdup("echo");
	cmd.cmd[1] = NULL;
}
