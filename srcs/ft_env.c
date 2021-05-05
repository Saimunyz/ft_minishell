/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 00:20:55 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/05 18:07:40 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_memory mem)
{
	while (mem.env)
	{
		ft_putstr_fd((char *)mem.env->content, 1);
		write(1, "\n", 1);
		mem.env = mem.env->next;
	}
}