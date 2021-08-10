/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:23:13 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/05 14:33:37 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *content)
{
	int	len;

	len = ft_strlen((char *)content);
	if (!lst || !content)
		return (NULL);
	while (lst)
	{
		if (!ft_strncmp((char *)lst->content, (char *)content, len))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
