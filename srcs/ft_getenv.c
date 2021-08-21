/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 13:49:31 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/21 14:10:24 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_memory *mem)
{
	t_var	*var;
	t_list	*find;

	find = ft_lstfind_struct(mem->env, name);
	if (!find)
		return NULL;
	var = ((t_var*)find->content);
	return (var->value);
}
