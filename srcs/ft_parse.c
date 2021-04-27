/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:08:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/26 17:11:20 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(char *line, char *home)
{
	char	**splt;
	int		splt_len;

	splt = ft_split(line, ' ');
	splt_len = ft_strlen(splt[0]);
	if (!ft_strncmp(splt[0], "pwd", ft_strlen(splt[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(splt[0], "echo", ft_strlen(splt[0])) && splt_len != 0)
		ft_echo(splt[1], 1);
	else if (!ft_strncmp(splt[0], "cd", ft_strlen(splt[0])) && splt_len != 0)
		ft_cd(splt[1]);
	else if (!ft_strncmp(splt[0], "exit", ft_strlen(splt[0])) && splt_len != 0)
		ft_exit();
	else if (!ft_strncmp(splt[0], "$?", ft_strlen(splt[0])) && splt_len != 0)
	{
		printf("minishell: %d: command not found\n", g_error);
		g_error = 127;//sergey 27/04/2021
	}
//<<<<<<< HEAD
	else if (*line != '\3')
		ft_commands(splt);
//=======
	// else if (*line != '\3')
	// 	ft_print_bash_err(line);
//>>>>>>> 80f33e5685362b963513f8511fae5d1b2b2896ea
	ft_write_history(line, home);
	free_text(splt, ft_maslen(splt));
	return (0);
}
