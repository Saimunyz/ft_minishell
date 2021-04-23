/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:21:01 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/10 17:27:09 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	len;
	long	num;

	num = n;
	len = get_len(num);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (num == 0)
		res[0] = '0';
	len--;
	if (num < 0)
	{
		res[0] = '-';
		num = num * -1;
	}
	while (num)
	{
		res[len] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	return (res);
}
