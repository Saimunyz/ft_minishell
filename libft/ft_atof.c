/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:48:43 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/10 17:21:10 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int		sign;
	long	res_atoi;
	double	res_atof;
	char	*num;
	size_t	len;

	sign = 1;
	res_atof = 0;
	res_atoi = ft_atoi(str);
	if (res_atoi < 0 || (res_atoi == 0 && *str == '-'))
	{
		sign = -1;
		res_atoi *= -1;
	}
	num = ft_strchr(str, '.');
	if (num)
	{
		len = ft_it_pow(10, ft_strlen(++num));
		while (*num >= '0' && *num <= '9')
			res_atof = res_atof * 10 + *num++ - '0';
		res_atof /= len;
	}
	return ((double)(sign * (res_atoi + res_atof)));
}
