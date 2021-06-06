/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:30:27 by swagstaf          #+#    #+#             */
/*   Updated: 2020/11/03 13:33:49 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **begin_list, t_list *delete)
{
	t_list	*tmp;

	if (*begin_list == delete)
	{
		*begin_list = (*begin_list)->next;
		free(delete);
		delete = NULL;
	}
	tmp = *begin_list;
	while (tmp && tmp->next)
	{
		if (tmp->next == delete)
		{
			tmp->next = delete->next;
			free(delete);
			delete = NULL;
		}
		tmp = tmp->next;
	}
}
