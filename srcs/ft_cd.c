/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:30:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 02:30:06 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 * вроде бы еще  env надо менять, проверить после обработки env
 */
void	ft_cd(char *path)
{
	int ans;

	if (!path)
		return;
	ans = chdir(path);
	if (ans < 0 || path == NULL)
	{
		write(1, "minishell: cd: ", 15);
		write(1, path, ft_strlen(path));
		write(1, ": No such file or directory\n", 28);
		errno = 0;
	}
	ft_check_errno(); //это тут надо?
}
