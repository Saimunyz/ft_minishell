/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:01:27 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 11:01:28 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_memory *mem)
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
			printf("%s=%s\n", name, value);
		tmp = tmp->next;
	}
}
