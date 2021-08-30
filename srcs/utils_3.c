/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:03:11 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/30 14:13:08 by swagstaf         ###   ########.fr       */
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
	env = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	ft_check_errno();
	while (tmp)
	{
		var = ((t_var *)tmp->content);
		name = ft_strjoin(var->name, "=");
		if (var->value)
		{
			env[i] = ft_strjoin(name, var->value);
			i++;
		}
		free(name);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_turn_signals(int on)
{
	if (on)
	{
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_handler);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	ft_check_symbols(char chr)
{
	if (chr == '\n' || chr == '\4' || chr == '\t' || chr == '\034')
		return (1);
	else if (!ft_isprint(chr))
		return (1);
	return (0);
}
