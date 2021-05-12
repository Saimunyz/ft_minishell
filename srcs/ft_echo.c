/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:01:07 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/10 16:28:15 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	ft_echo_write(char *str, int space, t_memory *mem)
void	ft_echo_write(char *str, int space)
{
//	t_list	*find;

	g_error = 0;
	if (space)
		write(1, " ", 1);
	if (str)
//	{		//Сергей $ теперь не тут
//		if (str[0] == '$')
//		{
//			find = ft_lstfind_struct(mem->env, str + 1);
//			if (!find)
//				find = ft_lstfind_struct(mem->var, str + 1);
//			if (find)
//				ft_putstr_fd(((t_var *)find->content)->value, 1);
//		}
//		else
			ft_putstr_fd(str, 1);
//	}
}

//void	ft_echo(char **str, t_memory *mem)
void	ft_echo(char **str)
{
	int i;
	int	flag;
	int space;

	g_error = 0;
	i = 1;
	flag = 1;
	space = 0;
	if (str[1])
	{
		if (!ft_strncmp(str[1], "-n", ft_strlen(str[1])))
		{
			flag = 0;
			i = 2;
		}
		while (str[i]) {
			ft_echo_write(str[i], space);
			i++;
			space = 1;
		}
	}
	if (flag)
		write(1, "\n", 1);
}

