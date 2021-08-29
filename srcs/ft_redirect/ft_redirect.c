/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:00:04 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/29 22:20:49 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_parse_redir(char *redir, int type, char *sign)
{
	t_file	*f;
	char	*space;

	f = malloc(sizeof(t_file));
	ft_check_errno();
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
	ft_check_errno();
	a_cmd->echo = 1;
	a_cmd->cmd[0] = ft_strdup("echo");
	a_cmd->cmd[1] = ft_strdup("-n");
	a_cmd->cmd[2] = NULL;
}

void	ft_parse_redirect_2(char **str, char *spec_char, int i, t_list	**files)
{
	*spec_char = ft_spec_char(*spec_char, str[0][i]);
	if (str[0][i] == ' ' && (str[0][i + 1] == '>' || str[0][i + 1] == '<') \
		&& !(*spec_char))
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

void	ft_parse_redirect(char **str, t_memory *mem, t_cmd *a_cmd)
{
	t_list	*files;
	int		i;
	char	spec_char;

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
		a_cmd->red = 1;
	if (ft_check_filename(files))
		return ;
	if (a_cmd->files)
	{
		a_cmd->red = 1;
		ft_start_redirect(a_cmd, mem);
	}
	else
		a_cmd->red = 0;
}
