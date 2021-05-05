/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:19:03 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/05 18:15:55 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_mem(t_memory *mem, char **envp)
{
	int		i;
	t_list	*tmp;

	i = 0;
	mem->env = NULL;
	mem->var = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&mem->env, tmp);
		if (ft_strnstr(envp[i], "SHLVL=", 6))
		{
			free(tmp->content);
			tmp->content = ft_strdup("SHLVL=2");
			mem->shlvl = tmp;
		}
		else if (ft_strnstr(envp[i], "PWD=", 4))
			mem->pwd = tmp;
		else if (ft_strnstr(envp[i], "OLDPWD=", 7))
			mem->oldpwd = tmp;
		i++;
	}
}
