/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:02:45 by swagstaf          #+#    #+#             */
/*   Updated: 2021/09/01 11:59:26 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*res;

	g_error = 0;
	res = getcwd(NULL, 0);
	ft_check_errno();
	if (res)
		printf("%s\n", res);
	free(res);
}
