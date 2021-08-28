/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:01:39 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 11:01:39 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_memory *mem)
{
	t_list	*tmp;
	char	*name;
	char	*value;

	tmp = ft_bubble_sort(mem->env);
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
