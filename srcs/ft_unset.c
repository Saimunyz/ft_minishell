/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:52 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/02 00:53:53 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_memory *mem, char **var)
{
	int		i;
	t_list	*tmp;

	i = 1;
	if (ft_maslen(var) > 1)
	{
		while (var[i])
		{
			if (!ft_isalpha(var[i][0]))
			{
				printf("minishell$: uset: '%s' not a valid identifier\n", var[i]);
				i++;
				continue;
			}
			tmp = ft_lstfind_struct(mem->env, var[i]);
			if (tmp)
				ft_lstremove(&mem->env, tmp);
			tmp = ft_lstfind_struct(mem->var, var[i]);
			if (tmp)
				ft_lstremove(&mem->var, tmp);
			i++;
		}
	}
}
