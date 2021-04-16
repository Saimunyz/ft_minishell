/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:08:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 16:18:10 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(char *line, int len)
{
	char	**splt;
	int		_x;
	int		splt_len;

	splt = ft_split(line, ' ');
	_x = len;
	splt_len = ft_strlen(splt[0]);
	if (!ft_strncmp(splt[0], "pwd", ft_strlen(splt[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(splt[0], "echo", ft_strlen(splt[0])) && splt_len != 0)
		ft_echo(splt[1], 1);
	free_text(splt, ft_maslen(splt));
	return (0);
}
