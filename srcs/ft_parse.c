/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:08:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 14:18:54 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(char *line, int len)
{
	char	**splited_line;
	int		_x;

	_x = len;
	splited_line = ft_split(line, ' ');
	if (!ft_strncmp(splited_line[0], "pwd", ft_strlen(splited_line[0])))
		ft_pwd();
	free_text(splited_line, ft_maslen(splited_line));
	return (0);
}
