/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:53:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 01:06:15 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(const char *s1, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)malloc(sizeof(char) * (len + 1));
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

int		set_result(int ret, char *line)
{
	if (ret == 0 && line)
		return (0);
	else
		return (-1);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*rem[1024];
	char			*tmp;
	int				ret;

	// if (fd < 0 || BUFFER_SIZE <= 0 || !line)
	// 	return (-1); Удалить эти строки для нормы
	*line = ft_strdup_gnl("", 0);
	if (rem[fd] && *line)
	{
		tmp = save_buff(rem[fd], line);
		free(rem[fd]);
		rem[fd] = tmp;
		if (rem[fd] && *line)
			return (1);
	}
	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0 && *line)
	{
		buff[ret] = '\0';
		rem[fd] = save_buff(buff, line);
		if (rem[fd] && *line)
			return (1);
		ret = read(fd, buff, BUFFER_SIZE);
	}
	free(rem[fd]);
	return (set_result(ret, *line));
}
