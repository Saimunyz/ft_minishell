/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:33:52 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 14:57:12 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_global(void)
{
	free(g_var.env_home);
	free(g_var.path_hist);
}

void	ft_global_init(void)
{
	g_var.env_home = getenv("HOME");
	g_var.path_hist = ft_strjoin(g_var.env_home, "/.minishell_history");
}
