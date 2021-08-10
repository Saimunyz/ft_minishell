/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrcopy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:37:54 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/10 21:44:17 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrcopy(char **arr)
{
	int		len;
	int		i;
	char	**newarr;

	i = 0;
	len = ft_maslen(arr);
	newarr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!newarr)
		return (NULL);
	while (i < len)
	{
		newarr[i] = ft_strdup(arr[i]);
		if (!newarr[i])
		{
			free_text(newarr, ft_maslen(newarr));
			return (NULL);
		}
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}
