/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:30:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/02 00:55:51 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path, t_env *env)
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
	free(env->oldpwd->content);
	env->oldpwd->content = ft_strjoin("OLD", env->pwd->content);
	free(env->pwd->content);
	env->pwd->content = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_check_errno();
}
