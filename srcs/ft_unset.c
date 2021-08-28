/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:02:57 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 16:28:21 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_list_rem(t_list **begin_list, t_list *delete)
{
	t_list	*tmp;

	if (*begin_list == delete)
	{
		*begin_list = (*begin_list)->next;
		delete->next = NULL;
		free(delete);
		delete = NULL;
	}
	tmp = *begin_list;
	while (tmp && tmp->next)
	{
		if (tmp->next == delete)
		{
			tmp->next = delete->next;
			delete->next = NULL;
			free(delete);
			delete = NULL;
		}
		tmp = tmp->next;
	}
}

static void	ft_remove(t_memory *mem, t_list *tmp_env, t_list *tmp_var)
{
	if (tmp_env && tmp_var)
	{
		ft_lstremove(&mem->env, tmp_env, ft_free_content);
		ft_list_rem(&mem->var, tmp_var);
	}
	else if (tmp_env)
		ft_lstremove(&mem->env, tmp_env, ft_free_content);
	else if (tmp_var)
		ft_lstremove(&mem->var, tmp_var, ft_free_content);
}

void	ft_unset(t_memory *mem, char **var)
{
	int		i;
	t_list	*tmp_env;
	t_list	*tmp_var;

	i = 1;
	if (ft_maslen(var) > 1)
	{
		while (var[i])
		{
			if (!ft_isalpha(var[i][0]))
			{
				printf("minishell$: ");
				printf("unset: '%s' not a valid identifier\n", var[i]);
				i++;
				continue ;
			}
			tmp_env = ft_lstfind_struct(mem->env, var[i]);
			tmp_var = ft_lstfind_struct(mem->var, var[i]);
			ft_remove(mem, tmp_env, tmp_var);
			i++;
		}
	}
}
