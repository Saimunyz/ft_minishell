/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 14:28:17 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/24 17:47:43 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lst2str(t_list *lst)
{
	char	*name;
	t_list	*tmp;
	char	**env;
	int		i;
	t_var	*var;

	i = 0;
	tmp = lst;
	env = (char **)malloc(sizeof(char*) * (ft_lstsize(lst) + 1));
	while (tmp)
	{
		var = ((t_var *)tmp->content);
		name = ft_strjoin(var->name, "=");
		env[i] = ft_strjoin(name, var->value);
		free(name);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

int	ft_check_symbols(char chr)
{
	if (chr == '\n' || chr == '\4' || chr == '\t' || chr == '\034')
		return (1);
	else if (!ft_isprint(chr))
		return (1);
	return (0);
}
