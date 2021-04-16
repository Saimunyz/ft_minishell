/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:01:07 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 16:21:28 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * flag or 0 or 1.
 */
void	ft_echo(char *str, int flag)
{
	while (str && *str && *str != '\n')
	{
		write(1, str, 1);
		str++;
	}
	if (flag)
		write(1, "\n", 1);
}
