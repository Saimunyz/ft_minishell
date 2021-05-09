/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:19:03 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/07 17:41:51 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*ft_init_val(char *envp)
{
	t_var	*tmp_var;
	char	**splt;

	tmp_var = (t_var *)malloc(sizeof(t_var)); //TODO нет обработки на null
	ft_check_errno();
	splt = ft_split(envp, '=');
	if (ft_maslen(splt) != 2)
		ft_check_errno(); // не уверен, что не нул просто
	tmp_var->name = ft_strdup(splt[0]);
	if (!splt[1])	//Сергей, тут нал бывает и крашится
		tmp_var->value = ft_strdup("");
	else
		tmp_var->value = ft_strdup(splt[1]);
	free_text(splt, ft_maslen(splt));
	return (tmp_var);
}

void	ft_null_mem(t_memory *mem)
{
		mem->env = NULL;
		mem->oldpwd = NULL;
		mem->var = NULL;
		mem->shlvl = NULL;
		mem->pwd = NULL;
}

void	ft_set_pwd(t_memory *mem)
{
	t_var	*tmp_var;
	t_list	*tmp;

	tmp_var = (t_var *)malloc(sizeof(t_var));
	tmp_var->name = ft_strdup("OLDPWD");
	tmp_var->value = NULL;
	tmp = ft_lstnew(tmp_var);
	ft_lstadd_back(&mem->env, tmp);
	mem->oldpwd = tmp;
}

void	ft_init_mem(t_memory *mem, char **envp)
{
	int		i;
	t_list	*tmp;
	int		shlvl;

	i = 0;
	ft_null_mem(mem);
	while (envp[i])
	{
		tmp = ft_lstnew(ft_init_val(envp[i]));
		ft_lstadd_back(&mem->env, tmp);
		if (ft_strnstr(envp[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(((t_var *)tmp->content)->value);
			free(((t_var *)tmp->content)->value);
			((t_var *)tmp->content)->value = ft_itoa(shlvl + 1);
			mem->shlvl = tmp;
		}
		else if (ft_strnstr(envp[i], "PWD=", 4))
			mem->pwd = tmp;
		else if (ft_strnstr(envp[i], "OLDPWD=", 7))
			mem->oldpwd = tmp;
		i++;
	}
	if (!mem->oldpwd)
		ft_set_pwd(mem);
}
