/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:00:04 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/31 22:16:39 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_parse_redir(char *redir, int type, char *sign)
{
	t_file	*f;
	char	*space;
	int		i;

	i = 0;
	f = malloc(sizeof(t_file));
	ft_check_errno();
	f->mode = type;
	f->type = sign;
	while (*redir == *sign && i++ < 2)
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
	unlink(".temporary");
	if (errno != 0)
		errno = 0;
}

void
	ft_parse_redirect_2(char **str, char *spc_chr, t_list	**files, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[0][i])
	{
		*spc_chr = ft_spec_char(*spc_chr, str[0][i]);
		if (str[0][i] == ' ' && (str[0][i + 1] == '>' || str[0][i + 1] == '<') \
			&& !(*spc_chr))
			ft_memmove((*str) + i, (*str) + i + 1, ft_strlen(str[0] + i));
		if (str[0][i] == '>' && str[0][i + 1] == '>' && !(*spc_chr))
			ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 1089, ">"));
		else if (str[0][i] == '<' && str[0][i + 1] == '<' && !(*spc_chr))
		{
			ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 0, "<<"));
			cmd->red_d_l = 1;
		}
		else if (str[0][i] == '>' && !(*spc_chr))
			ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 577, ">"));
		if (str[0][i] == '<' && !(*spc_chr))
			ft_lstadd_back(&(*files), ft_parse_redir(str[0] + i, 0, "<"));
		i++;
	}
}

void	ft_parse_redirect(char **str, t_memory *mem, t_cmd *a_cmd)
{
	t_list	*files;
	char	spec_char;

	spec_char = 0;
	files = NULL;
	ft_parse_redirect_2(str, &spec_char, &files, a_cmd);
	a_cmd->files = files;
	a_cmd->cmd = ft_parse_strings(str[0]);
	if (ft_check_filename(files))
	{
		a_cmd->red_err = 1;
		a_cmd->files = NULL;
		return ;
	}
	if (a_cmd->files)
	{
		a_cmd->red = 1;
		ft_start_redirect(a_cmd, mem);
	}
	else
		a_cmd->red = 0;
}
