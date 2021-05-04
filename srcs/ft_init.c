/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:19:03 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/02 01:04:49 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_env(t_env *env, char **envp)
{
	int		i;
	t_list	*tmp;

	i = 0;
	env->env = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&env->env, tmp);
		if (ft_strnstr(envp[i], "SHLVL=", 6))
		{
			free(tmp->content);
			tmp->content = ft_strdup("SHLVL=2");
			env->shlvl = tmp;
		}
		else if (ft_strnstr(envp[i], "PWD=", 4))
			env->pwd = tmp;
		else if (ft_strnstr(envp[i], "OLDPWD=", 7))
			env->oldpwd = tmp;
		i++;
	}
}
