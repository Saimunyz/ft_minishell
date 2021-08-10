/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:05:58 by swagstaf          #+#    #+#             */
/*   Updated: 2021/06/11 15:47:45 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_char(int *len, char **line)
{
	char	*tmp;

	if ((*len) + 12 > 12)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		(*len)--;
		tmp = ft_substr(*line, 0, *len);
		free(*line);
		*line = tmp;
		write(1, *line, *len);
	}
}

void	ft_del_line(int *len, char **line)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	free(*line);
	*len = 0;
	*line = NULL;
}

//void	ft_print_var(char *command, t_memory *mem)
//{
//	t_list	*find;
//	char	**splt;
//
//	if (*(command + 1) =='?')
//	{
//		printf("minishell: %d: command not found\n", g_error);
//		g_error = 127;
//	}
//	else
//	{
//		find = ft_lstfind_struct(mem->env, command + 1);
//		if (!find)
//			find = ft_lstfind_struct(mem->var, command + 1);
//		if (find)
//		{
//			splt = ft_split(((t_var *)find->content)->value, ' ');
//			//printf("%s: command not found\n", splt[0]);
//			ft_start_commands(splt, mem);
//			g_error = 127;
//		}
//	}
//}

void	ft_free_content(void *content)
{
	if (content)
	{
		if (((t_var *)content)->name)
		{
			free(((t_var *)content)->name);
			((t_var *)content)->name = NULL;
		}
		if (((t_var *)content)->value)
		{
			free(((t_var *)content)->value);
			((t_var *)content)->value = NULL;
		}
	}
}

t_list	*ft_lstfind_struct(t_list *lst, void *name)
{
	int		len;
	char	*lst_name;

	len = ft_strlen((char *)name);
	if (!lst || !name)
		return (NULL);
	while (lst)
	{
		lst_name = (char *)((t_var *)lst->content)->name;
		if (!ft_strncmp(lst_name, (char *)name, len))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
