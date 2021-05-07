/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:45:27 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/07 18:21:08 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// поменять лист на разбитый по name value
// и добавть сортировку с ковычками на вывод
// починить дублирование после починки листа

void	ft_print_export(t_memory *mem)
{
	t_list	*tmp;
	char	*name;
	char	*value;

	tmp = mem->env;
	while (tmp)
	{
		name = ((t_var *)tmp->content)->name;
		value = ((t_var *)tmp->content)->value;
		if (value)
			printf("declare -x %s=\"%s\"\n", name, value);
		else
			printf("declare -x %s\n", name);
		tmp = tmp->next;
	}
}

void	ft_export_set(t_memory *mem, char *name, t_list *find_var)
{
	t_list	*find_env;
	char	*value;
	t_var	*tmp;

	if (find_var)
	{
		value = ((t_var *)find_var->content)->value;
		find_env = ft_lstfind_struct(mem->env, name);
		if (!find_env)
			ft_lstadd_back(&mem->env, ft_lstnew(find_var->content));
		else
		{
			free(((t_var *)find_env->content)->value);
			((t_var *)find_env->content)->value = ft_strdup(value);
		}
	}
	else
	{
		tmp = (t_var *)malloc(sizeof(t_var));
		tmp->name = ft_strdup(name);
		tmp->value = NULL;
		ft_lstadd_back(&mem->env, ft_lstnew(tmp));
	}
}

void	ft_export(t_memory *mem, char **strs_cmd)
{
	char	*name;
	t_list	*find_var;

	if (!strs_cmd[1])
	{
		ft_print_export(mem);
		return ;
	}
	name = strs_cmd[1];
	if (ft_strnstr(name, "=", ft_strlen(name)))
	{
		ft_check_var(name, mem);
		name = ((t_var *)ft_lstlast(mem->var)->content)->name;
	}
	find_var = ft_lstfind_struct(mem->var, name);
	ft_export_set(mem, name, find_var);
}
