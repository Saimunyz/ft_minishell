/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 00:20:55 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/02 00:27:35 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env env)
{
	while (env.env)
	{
		ft_putstr_fd((char *)env.env->content, 1);
		write(1, "\n", 1);
		env.env = env.env->next;
	}
}
