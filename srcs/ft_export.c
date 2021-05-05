/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:45:27 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/05 18:54:42 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_memory *mem, char **strs_cmd)
{
	if (strs_cmd[1] == NULL)
		ft_lstadd_back(&mem->env, ft_lstnew(strs_cmd[0]));
}
