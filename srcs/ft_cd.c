/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:30:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/20 23:40:45 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_check_pwds(t_memory *mem, t_list *tmp_oldpwd, t_list *tmp_pwd)
{
	char	*value;

	value = NULL;
	if (tmp_oldpwd)
	{
		mem->oldpwd = tmp_oldpwd;
		ft_free_content(mem->oldpwd->content);
	}
	if (tmp_pwd)
	{
		mem->pwd = tmp_pwd;
		value = ((t_var *)mem->pwd->content)->value;
	}
	if (!value)
		value = "";
	return (value);
}

static void	ft_set_pwd(t_memory *mem, t_list *tmp_oldpwd, t_list *tmp_pwd)
{
	char	*value;

	value = ft_check_pwds(mem, tmp_oldpwd, tmp_pwd);
	if (tmp_oldpwd)
	{
		((t_var *)mem->oldpwd->content)->name = ft_strdup("OLDPWD");
		((t_var *)mem->oldpwd->content)->value = ft_strdup(value);
	}
	if (tmp_pwd)
	{
		ft_free_content(mem->pwd->content);
		((t_var *)mem->pwd->content)->name = ft_strdup("PWD");
		((t_var *)mem->pwd->content)->value = getcwd(NULL, 0);
	}
	ft_check_errno();
}

void	ft_cd(char *path, t_memory *mem)
{
	int		ans;
	t_list	*tmp_oldpwd;
	t_list	*tmp_pwd;

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
	tmp_oldpwd = ft_lstfind_struct(mem->env, "OLDPWD");
	tmp_pwd = ft_lstfind_struct(mem->env, "PWD");
	ft_set_pwd(mem, tmp_oldpwd, tmp_pwd);
}
