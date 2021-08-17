/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:30:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/15 20:08:50 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_pwd(t_memory *mem, t_list *tmp)
{
	char	*value;
	if (tmp)
	{
		mem->oldpwd = tmp;
		ft_free_content(mem->oldpwd->content);
	}
	value = ((t_var *)mem->pwd->content)->value;
	if (tmp)
	{
		((t_var *)mem->oldpwd->content)->name = ft_strdup("OLDPWD");
		((t_var *)mem->oldpwd->content)->value = ft_strdup(value);
	}
	ft_free_content(mem->pwd->content);
	((t_var *)mem->pwd->content)->name = ft_strdup("PWD");
	((t_var *)mem->pwd->content)->value = getcwd(NULL, 0);
	ft_check_errno();
}

void	ft_cd(char *path, t_memory *mem)
{
	int		ans;
	t_list	*tmp;

	g_error = 0;
	if (!path)
		path = ((t_var *)mem->home->content)->value;
	ans = chdir(path);
	if (ans < 0 || path == NULL)
	{
		write(1, "minishell: cd: ", 15);
		write(1, path, ft_strlen(path));
		write(1, ": No such file or directory\n", 28);
		errno = 0;
	}
	tmp = ft_lstfind_struct(mem->env, "OLDPWD");
	ft_set_pwd(mem, tmp);
}
