/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 00:41:01 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/10 17:32:02 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen_base(long n, int base)
{
	int	len;

	len = 1;
	while (n >= 1)
	{
		len++;
		n /= base;
	}
	return (len);
}

static int	itoa_check_sign(int *len, long value, int base)
{
	if (value < 0 && base == 10)
	{
		(*len)++;
		return (-1);
	}
	return (0);
}

char	*ft_itoa_b(long value, int base, char reg)
{
	char	*str;
	long	n;
	int		sign;
	int		len;

	n = value;
	if (value < 0)
		n *= -1;
	len = ft_numlen_base(n, base);
	sign = itoa_check_sign(&len, value, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- + sign)
	{
		if (n % base < 10)
			str[len] = n % base + '0';
		else
			str[len] = n % base + reg - 10;
		n /= base;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
