/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:00:47 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 11:00:55 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_len_space(char *line)
{
	int		count;
	char	spec_char;

	count = 0;
	spec_char = 0;
	spec_char = ft_spec_char(spec_char, *line);
	while (*line && (*line != ' ' || spec_char))
	{
		line++;
		count++;
		spec_char = ft_spec_char(spec_char, *line);
	}
	return (count);
}

int	ft_count_strs(char *line)
{
	int		count;
	char	spec_char;

	spec_char = 0;
	if (*line)
		count = 1;
	else
		return (0);
	while (*line)
	{
		spec_char = ft_spec_char(spec_char, *line);
		if (*line == '|' && *(line + 1) && !spec_char)
		{
			line++;
			count++;
		}
		if (*line)
			line++;
	}
	if (spec_char != 0)
	{
		printf("minishell: syntax error\n");
		return (0);
	}
	return (count);
}

int	ft_find_char(char *str, int i, t_cmd *a_cmd)
{
	char	spec_char;

	spec_char = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		spec_char = ft_spec_char(spec_char, str[i]);
		if (str[i] == '|' && !spec_char)
		{
			if (str[i] == '|')
				a_cmd->p_next = 1;
			return (i);
		}
		i++;
	}
	return (ft_strlen(str));
}

int	ft_find_space(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '"' \
			|| str[i] == 39 || str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_find_doll(char *line, t_memory *mem)
{
	t_list	*find;
	char	*str_find;
	int		end;
	char	*tmp;

	end = ft_find_space(line);
	tmp = ft_substr(line, 0, end);
	if (*line == 34 || *line == 39)
		return (0);
	if (end == 1 && *line == '$' && *(line + 1) == '"')
	{
		free(tmp);
		return (ft_strdup("$"));
	}
	find = ft_lstfind_struct(mem->env, tmp + 1);
	if (!find)
		find = ft_lstfind_struct(mem->var, tmp + 1);
	if (find && ((t_var *) find->content)->value)
	{
		str_find = (char *)((t_var *) find->content)->value;
		free(tmp);
		return (ft_strdup(str_find));
	}
	free(tmp);
	return (0);
}
