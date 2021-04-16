/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:23:26 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 15:52:20 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, size_t newsize)
{
	char	*newstr;

	if (!ptr)
		return (malloc(sizeof(char) * (newsize + 1)));
	newstr = (char *)ft_calloc(newsize + 1, sizeof(char));
	ft_strlcat(newstr, ptr, newsize + 1);
	free(ptr);
	return (newstr);
}
