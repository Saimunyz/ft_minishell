/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:30:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/05 18:05:00 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path, t_memory *mem)
{
	int ans;

	g_error = 0;
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
	free(mem->oldpwd->content);
	mem->oldpwd->content = ft_strjoin("OLD", mem->pwd->content);
	free(mem->pwd->content);
	mem->pwd->content = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_check_errno();
}
