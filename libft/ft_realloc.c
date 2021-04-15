/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:23:26 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/15 16:48:38 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newstr;
	size_t	size_ptr;

	if (!ptr)
		return (malloc(newsize));
	size_ptr = sizeof(ptr);
	if (size_ptr > newsize)
		return (ptr);
	newstr = malloc(newsize);
	ft_memcpy(newstr, ptr, size_ptr);
	free(ptr);
	return (newstr);
}
