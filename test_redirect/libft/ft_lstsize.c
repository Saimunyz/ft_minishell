/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:36:57 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/10 17:33:07 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	counter;

	counter = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}
