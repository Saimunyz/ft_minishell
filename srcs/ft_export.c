/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:45:27 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/06 02:24:35 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// поменять лист на разбитый по name value
// и добавть сортировку с ковычками на вывод
// починить дублирование после починки листа
void	ft_print_export(t_memory mem)
{
	t_list	*tmp;

	tmp = mem.env;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(tmp->content, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	ft_export(t_memory *mem, char **strs_cmd)
{
	t_list	*find;
	char	*content;
	char	*tmp;
	char	*str;

	if (!strs_cmd[1])
	{
		ft_print_export(*mem);
		return ;
	}
	str = strs_cmd[1];
	if (ft_strnstr(str, "=", ft_strlen(str)))
	{
		ft_check_var(str, mem);
		str = ((t_var *)ft_lstlast(mem->var)->content)->name;
	}
	find = ft_lstfind_struct(mem->var, str);
	if (find)
	{
		tmp = ft_strjoin(((t_var *)find->content)->name, "=");
		content = ft_strjoin(tmp, ((t_var *)find->content)->value);
		free(tmp);
		// mem->shlvl->next = ft_lstnew(content);
		// mem->shlvl->next->next = tmp_lst;
		ft_lstadd_back(&mem->env, ft_lstnew(content));
	}
}
