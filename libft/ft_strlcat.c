/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:58:47 by swagstaf          #+#    #+#             */
/*   Updated: 2020/11/01 12:38:38 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;
	size_t	d_len;

	i = 0;
	len = 0;
	if (dstsize == 0 || ft_strlen(dst) > dstsize)
		return (dstsize + ft_strlen(src));
	while (dst[len])
		len++;
	d_len = len;
	while (src[i] && len + 1 < dstsize)
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	dst[len] = '\0';
	return (d_len + ft_strlen(src));
}
