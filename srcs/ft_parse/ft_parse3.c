/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:00:39 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 11:00:57 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_doll(char *line, t_memory *mem)
{
	int		len;
	int		doll;
	char	*tmp;

	len = 0;
	doll = 1;
	while (*line)
	{
		if (*line == '$')
		{
			doll = 1;
			tmp = ft_find_doll(line, mem);
			len = len + ft_strlen(tmp);
			if (tmp)
				free(tmp);
		}
		if (doll && *line == ' ')
			doll = 0;
		if (doll)
			len++;
		line++;
	}
	return (len);
}

void	change_doll_var(char ***line, char **str_find, char **tmp, int *j)
{
	char	*tmp_find;

	tmp_find = *str_find;
	(**line)++;
	while (**str_find || (***line && ***line != ' ' \
		&& ***line != '$' && ***line != 39 && ***line != 34 && ***line != '='))
	{
		if (**str_find)
		{
			(*tmp)[*j] = **str_find;
			(*j)++;
			(*str_find)++;
		}
		while (***line && ***line != ' ' && ***line != 39 && \
			***line != 34 && ***line != '$' && ***line != '=')
			(**line)++;
	}
	free(tmp_find);
}

void	change_doll(char ***line, char **tmp, int *j, t_memory *mem)
{
	char	*str_find;

	str_find = ft_find_doll(**line, mem);
	if (!str_find)
	{
		(**line)++;
		while (***line && ***line != ' ' && ***line != 39 && \
			***line != 34 && ***line != '$' && ***line != '=')
			(**line)++;
	}
	else
		change_doll_var(line, &str_find, tmp, j);
}

t_cmd
	*ft_split_string_2(t_cmd *a_cmd, char *line, t_memory *mem, int count_strs)
{
	int		i;
	int		start;
	int		end;
	char	*tmp;

	i = 0;
	start = 0;
	while (i < count_strs)
	{
		clean_a_cmd(&a_cmd[i]);
		end = ft_find_char(line, start, &a_cmd[i]);
		if (i > 0)
			a_cmd[i].p_priv = a_cmd[i - 1].p_next;
		tmp = ft_substr(line, start, end - start);
		ft_change_var(&tmp, mem);
		pipe(a_cmd[i].fd);
		ft_parse_redirect(&tmp, mem, &(a_cmd[i]));
		free(tmp);
		start = end + 1;
		i++;
	}
	a_cmd[i].cmd = 0;
	return (a_cmd);
}

t_cmd	*ft_split_string(char *line, t_memory *mem)
{
	int		count_strs;
	t_cmd	*a_cmd;

	count_strs = ft_count_strs(line);
	if (count_strs == 0)
		return (NULL);
	a_cmd = (t_cmd *) malloc(sizeof(t_cmd) * (count_strs + 1));
	ft_split_string_2(a_cmd, line, mem, count_strs);
	return (a_cmd);
}
