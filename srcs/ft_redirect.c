/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:22:02 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/15 18:40:29 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file	*ft_parse_redir(char *redir, int type, char sign)
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
	return (f);
}


t_list	*ft_parse_redirect(char** str)
{
	//t_list	*files;
	//t_list	*file_to_read;
	t_file	*f;
	int		i;

	i = 0;
	//files = NULL;
	f = NULL;
	// ft_change_var();
	while (str[0][i])
	{
		if (str[0][i] == ' ' && (str[0][i + 1] == '>' || str[0][i + 1] == '<'))
			ft_memmove((*str) + i, (*str) + i + 1, ft_strlen(str[0] + i));
		if (str[0][i] == '>' && str[0][i + 1] == '>')
			f = ft_parse_redir(str[0] + i, 1089, '>');

			//ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 1089, '>'));
		else if (str[0][i] == '>')
			f = ft_parse_redir(str[0] + i, 577, '>');
			//ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 577, '>'));
		if (str[0][i] == '<')
			f = ft_parse_redir(str[0] + i, 0, '<');
			//ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 0, '<'));
		if (f)
		{
			ft_redirect()
			f = NULL;
		}
		i++;
	}
	return (files);
}

char	*ft_read_file(int fd, t_cmd cmd)
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
	free(line);

}

void	ft_redirect(t_list *files, t_cmd cmd, t_memory *mem)
{
	int		fd;
	int		original_out;
	char	*filename;
	int		i;

	original_out = dup(1);
	while (files)
	{
		filename = ((t_file *)files->content)->filename;
		fd = open(filename, ((t_file *)files->content)->mode, 0755);
		if (((t_file *)files->content)->type == '>')
			dup2(fd,1);
		else
			ft_read_file();
		files = files->next;
	}
	ft_start_commands(cmd.cmd, mem);
	close (fd);
	dup2(original_out, 1);
	i = 0;
	while (cmd.cmd[i])
		free(cmd.cmd[i++]);
	cmd.cmd[0] = ft_strdup("echo");
	cmd.cmd[1] = NULL;
}
