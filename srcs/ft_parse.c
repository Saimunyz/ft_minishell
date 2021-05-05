/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:08:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/06 01:07:43 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var(char *strs_cmd, t_memory *mem)
{
	char	**splt;
	char	*tmp;

	if (ft_strnstr(strs_cmd, "+=", ft_strlen(strs_cmd)))
	{
		splt = ft_split(strs_cmd, '+');
		if (ft_maslen(splt) == 2)
		{
			tmp = splt[1];
			splt[1] = ft_strdup(tmp + 1);
			free(tmp);
			ft_add_var(splt, mem, 1);
		}
	}
	else if (ft_strnstr(strs_cmd, "=", ft_strlen(strs_cmd)))
	{
		splt = ft_split(strs_cmd, '=');
		if (ft_maslen(splt) == 2)
			ft_add_var(splt, mem, 0);
	}
	else
		return (0);
	free_text(splt, ft_maslen(splt));
	return (1);
}

void	ft_add_var(char	**splt, t_memory *mem, int is_plus)
{
	t_var	*tmp_var;
	t_list	*tmp_lst;
	char	*value;

	tmp_lst = ft_lstfind_struct(mem->var, splt[0]);
	if (tmp_lst)
	{
		value = ((t_var *)tmp_lst->content)->value;
		if (is_plus)
			((t_var *)tmp_lst->content)->value = ft_strjoin(value, splt[1]);
		else
			((t_var *)tmp_lst->content)->value = ft_strdup(splt[1]);
		free(value);
	}
	else
	{
		tmp_var = (t_var *)malloc(sizeof(t_var));
		tmp_var->name = ft_strdup(splt[0]);
		tmp_var->value = ft_strdup(splt[1]);
		ft_lstadd_back(&mem->var, ft_lstnew(tmp_var));
	}
}

void ft_start_commands(char	**strs_cmd, t_memory *mem)
{
	int		splt_len;

	splt_len = ft_strlen(strs_cmd[0]);
	if (strs_cmd[1] == NULL && ft_check_var(strs_cmd[0], mem))
		return (free_text(strs_cmd, ft_maslen(strs_cmd)));
	else if (!ft_strncmp(strs_cmd[0], "pwd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(strs_cmd[0], "echo", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_echo(strs_cmd[1], 1);
	else if (!ft_strncmp(strs_cmd[0], "cd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_cd(strs_cmd[1], mem);
	else if (!ft_strncmp(strs_cmd[0], "exit", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_exit();
	else if (!ft_strncmp(strs_cmd[0], "env", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_env(*mem);
	else if (!ft_strncmp(strs_cmd[0], "export", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_export(mem, strs_cmd);
	// else if (!ft_strncmp(strs_cmd[0], "unset", ft_strlen(strs_cmd[0])) && splt_len != 0)
	// 	ft_unset(*env);
	else if (!ft_strncmp(strs_cmd[0], "$?", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_print_bash_err();
	else if (*strs_cmd[0] != '\3')
		ft_commands(strs_cmd);
	free_text(strs_cmd, ft_maslen(strs_cmd));
}


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
	while (**line && **line == ' ')
		(*line)++;
}

int	ft_count_commands(char *line)
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
			if (*line)
				count++;
		}
		line++;
	}
	return count;
}

char** ft_parse_strings(char *line)
{
	char **arr_strings;
	int count_commands;
	int i;
	int j;

	count_commands = ft_count_commands(line);
	arr_strings = (char **) malloc(sizeof (char **) * (count_commands + 1));
	ft_go_end_space(&line);
	i = 0;
	while (i < count_commands)
	{
		j = 0;
		arr_strings[i] = (char *) malloc(sizeof (char *) * (ft_str_len_space(line) + 1));
		while (*line) {
			arr_strings[i][j] = *line;
			if (*line == ' ' || !line )
			{
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

int	ft_count_strs(char *line)
{
	int count;

	if (*line)
		count = 1;
	else
		return (0);
	while (*line)
	{
		if ((*line == ';' || *line == '|') && *(line + 1))
		{
			line++;
			count++;
		}
		if (*line)
			line++;
	}
	return count;
}

int ft_find_char(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i])
	{
		if(str[i] == ';')
			return (i);
		i++;
	}
	return (ft_strlen(str));
}

char	***ft_split_string(char *line)
{
	char ***arr_strs;
	int count_strs;
	int	i;
	int start;
	int end;
	char *tmp;

	count_strs = ft_count_strs(line);
	if (count_strs == 0)
		return NULL;
	arr_strs = (char ***) malloc(sizeof(char ***) * (count_strs + 1));
	i = 0;
	start = 0;
	while (i < count_strs)
	{
		end = ft_find_char(line, start);
		tmp = ft_substr(line, start, end - start);
		arr_strs[i] = ft_parse_strings(tmp);
		start = end + 1;
		i++;
	}
	arr_strs[i] = NULL;
	return (arr_strs);
}


////TODO Доделать
////	""  ''
////  "\"
//// |
//// << >> <
////  git checkout  main (несколько параметров)
//int	ft_parse(char *line, char *home)
void	ft_parse(char *line, char *home, t_memory *mem)
{
	char	***arr_commands;
	int	i;

	i = 0;
	arr_commands = ft_split_string(line);
	while (arr_commands && arr_commands[i])
	{
		ft_start_commands(arr_commands[i], mem);
		i++;
	}
	free(arr_commands);
	ft_write_history(line, home);
}
