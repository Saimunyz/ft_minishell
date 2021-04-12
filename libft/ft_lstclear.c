/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:05:59 by swagstaf          #+#    #+#             */
/*   Updated: 2020/11/03 14:37:55 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*free_list;

	tmp = *lst;
	while (tmp && tmp->next)
	{
		free_list = tmp;
		tmp = tmp->next;
		(*del)(free_list->content);
		free(free_list);
	}
	(*del)(tmp->content);
	free(tmp);
	*lst = NULL;
}
