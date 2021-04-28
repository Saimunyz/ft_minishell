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

int	ft_str_len_space(char *line)
{
	int	count;

	count = 0;
	while (*line && *line != ' ')
	{
		line++;
		count++;
	}
	return (count);
}

void ft_go_end_space(char **line)
{
	if (**line && **line == ' ')
		(*line)++;
}

int	ft_count_str(char *line)
{
	int count;

	ft_go_end_space(&line);
	if (*line)
		count = 1;
	else
		return (0);
	while (*line)
	{
		if (*line == ' ')
		{
			ft_go_end_space(&line);
			count++;
		}
		line++;
	}
	return count;
}

char** ft_parse_strings(char *line)
{
	char **arr_strings;
	int count_lines;
	int i;
	int j;

	count_lines = ft_count_str(line);
	arr_strings = (char **) malloc(sizeof (char **) * (count_lines + 1));
	ft_go_end_space(&line);
	i = 0;
	while (i < count_lines)
	{
		j = 0;
		arr_strings[i] = (char *) malloc(sizeof (char *) * (ft_str_len_space(line) + 1));
		while (*line) {
			arr_strings[i][j] = *line;
			if (*line == ' ' || !line) {
				ft_go_end_space(&line);
				break;
			}
			j++;
			line++;
		}
		arr_strings[i][j] = '\0';
		i++;
	}
	arr_strings[i] = NULL;
	return (arr_strings);
}

int	ft_parse(char *line, char *home)
{
	char	**strs_cmd;
	int		splt_len;

	strs_cmd = ft_parse_strings(line);
	splt_len = ft_strlen(strs_cmd[0]);
	if (!ft_strncmp(strs_cmd[0], "pwd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(strs_cmd[0], "echo", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_echo(strs_cmd[1], 1);
	else if (!ft_strncmp(strs_cmd[0], "cd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_cd(strs_cmd[1]);
	else if (!ft_strncmp(strs_cmd[0], "exit", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_exit();
	else if (!ft_strncmp(strs_cmd[0], "$?", ft_strlen(strs_cmd[0])) && splt_len != 0)
	{
		printf("minishell: %d: command not found\n", g_error);
		g_error = 127;//sergey 27/04/2021
	}
	else if (*line != '\3')
		ft_commands(strs_cmd);
	ft_write_history(line, home);
	free_text(strs_cmd, ft_maslen(strs_cmd));
	return (0);
}
