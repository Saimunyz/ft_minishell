/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:01:36 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 11:01:37 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_set(t_memory *mem, char *name, t_list *find_var)
{
	t_list	*find_env;
	char	*value;
	t_var	*tmp;
	char	*new_var;

	if (find_var)
	{
		value = ((t_var *)find_var->content)->value;
		find_env = ft_lstfind_struct(mem->env, name);
		if (!find_env)
			ft_lstadd_back(&mem->env, ft_lstnew(find_var->content));
		else
		{
			new_var = ft_strdup(value);
			free(((t_var *)find_env->content)->value);
			((t_var *)find_env->content)->value = new_var;
		}
	}
	else if (!ft_lstfind_struct(mem->env, name))
	{
		tmp = (t_var *)malloc(sizeof(t_var));
		tmp->name = ft_strdup(name);
		tmp->value = NULL;
		ft_lstadd_back(&mem->env, ft_lstnew(tmp));
	}
}

char	**ft_wise_split(char *strs_cmd)
{
	char	**splt;
	char	*tmp_splt;

	splt = NULL;
	if (ft_strnstr(strs_cmd, "+=", ft_strlen(strs_cmd)))
	{
		splt = ft_split(strs_cmd, '+');
		tmp_splt = splt[1];
		splt[1] = ft_strdup(tmp_splt + 1);
		free(tmp_splt);
	}
	else if (ft_strnstr(strs_cmd, "=", ft_strlen(strs_cmd)))
		splt = ft_split(strs_cmd, '=');
	return (splt);
}

int	ft_chek_name(char *name, int *i)
{
	if (!ft_isalpha(name[0]))
	{
		printf("minishell$: export: '%s': not a valid identifier\n", name);
		(*i)++;
		return (1);
	}
	return (0);
}

void	ft_export2(t_memory *mem, char *name, char **splt)
{
	t_list	*find_var;

	find_var = ft_lstfind_struct(mem->var, name);
	ft_export_set(mem, name, find_var);
	free_text(splt, ft_maslen(splt));
}

void	ft_export(t_memory *mem, char **strs_cmd)
{
	char	**splt;
	int		i;
	char	*name;

	i = 1;
	if (!strs_cmd[1])
		ft_print_export(mem);
	else
	{
		while (strs_cmd && strs_cmd[i])
		{
			name = strs_cmd[i];
			if (ft_chek_name(name, &i))
				continue ;
			splt = ft_wise_split(strs_cmd[i]);
			if (splt)
			{
				name = splt[0];
				ft_check_var(strs_cmd[i], mem);
			}
			ft_export2(mem, name, splt);
			i++;
		}
	}
}
