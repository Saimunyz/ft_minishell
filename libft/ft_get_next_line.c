/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:53:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/27 15:56:13 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(const char *s1, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*save_buff(char *buff, char **line)
{
	size_t	len;
	char	*str;
	char	*tmp;

	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	str = ft_strdup_gnl(buff, len);
	tmp = ft_strjoin(*line, str);
	free(*line);
	free(str);
	*line = tmp;
	if (buff[len] == '\n')
		return (ft_strdup_gnl(buff + len + 1, ft_strlen(buff + len + 1)));
	return (NULL);
}

int	set_result(int ret, char *line)
{
	if (ret == 0 && line)
		return (0);
	else
		return (-1);
}

int	get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*rem;
	char			*tmp;
	int				ret;

	*line = ft_strdup_gnl("", 0);
	if (rem && *line)
	{
		tmp = save_buff(rem, line);
		free(rem);
		rem = tmp;
		if (rem && *line)
			return (1);
	}
	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0 && *line)
	{
		buff[ret] = '\0';
		rem = save_buff(buff, line);
		if (rem && *line)
			return (1);
		ret = read(fd, buff, BUFFER_SIZE);
	}
	free(rem);
	return (set_result(ret, *line));
}
