/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:30:27 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/27 21:36:34 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	if_first(t_list **begin_list, t_list *delete, void (*del)(void *))
{
	*begin_list = (*begin_list)->next;
	del(delete->content);
	free(delete->content);
	delete->content = NULL;
	delete->next = NULL;
	free(delete);
	delete = NULL;
}

void	ft_lstremove(t_list **begin_list, t_list *delete, void (*del)(void *))
{
	t_list	*tmp;

	if (*begin_list == delete)
		if_first(begin_list, delete, del);
	tmp = *begin_list;
	while (tmp && tmp->next)
	{
		if (tmp->next == delete)
		{
			tmp->next = delete->next;
			del(delete->content);
			free(delete->content);
			delete->content = NULL;
			delete->next = NULL;
			free(delete);
			delete = NULL;
		}
		tmp = tmp->next;
	}
}
