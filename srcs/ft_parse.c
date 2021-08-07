/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:08:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/07 19:16:17 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	ft_spec_char_step(char spec_char, char **line)
{
	if(spec_char == 0)
	{
		if (**line == 34 || **line == 39)
		{
			spec_char = **line;
			(*line)++;
			return spec_char;
		}
	}
	else if (spec_char == **line)
	{
		(*line)++;
		return (0);
	}
	return (spec_char);
}



char	*ft_spec_char_loop(char **str)
{
	int i;
	char *tmp;
	char spec_char;
	char *tmp_str;

	i = 0;
	tmp_str = *str;
	spec_char = 0;
	tmp = (char *) malloc(sizeof(char) * (ft_strlen(*str) + 1));
	while (**str)
	{
		spec_char = ft_spec_char_step(spec_char, str);
		tmp[i] = **str;
		(*str)++;
		i++;
	}
	tmp[i] = '\0';
	free(tmp_str);
	return tmp;
}

int	ft_check_for_equal_sign(char ***strs_cmd, t_memory *mem)
{
	int		i;
	char	**new_str_cmd;

	i = 0;
	while (strs_cmd && (*strs_cmd)[i])
	{
		if (!(ft_strnstr(strs_cmd[0][i], "+=", ft_strlen(strs_cmd[0][i]))
				|| ft_strnstr(strs_cmd[0][i], "=", ft_strlen(strs_cmd[0][i]))))
		{
			if (i)
			{
				new_str_cmd = ft_strarrcopy(*(strs_cmd) + i);
				free_text(*strs_cmd, ft_maslen(*strs_cmd));
				*strs_cmd = new_str_cmd;
			}
			return (0);
		}
		i++;
	}
	i = 0;
	while (strs_cmd && (*strs_cmd)[i])
		ft_check_var(strs_cmd[0][i++], mem);
	free_text(*strs_cmd, ft_maslen(*strs_cmd));
	return (1);
}

void	ft_check_var(char *strs_cmd, t_memory *mem)
{
	char	**splt;
	char	*tmp_splt;
	int		isPlus;

	splt = NULL; // Исправить, так как будет сега!!!!!
	isPlus = 0; // Вышли за кол-во строк :-)
	if (ft_strnstr(strs_cmd, "+=", ft_strlen(strs_cmd)))
	{
		splt = ft_split(strs_cmd, '+');
		if (ft_maslen(splt) == 2)
		{
			tmp_splt = splt[1];
			splt[1] = ft_strdup(tmp_splt + 1);
			free(tmp_splt);
		}
		isPlus = 1;
	}
	else if (ft_strnstr(strs_cmd, "=", ft_strlen(strs_cmd)))
	{
		splt = ft_split(strs_cmd, '=');
		isPlus = 0;
	}
	splt[1] = ft_spec_char_loop(&splt[1]);
	ft_add_var(splt, mem, isPlus);
	free_text(splt, ft_maslen(splt));
}



void	ft_add_var(char	**splt, t_memory *mem, int is_plus)
{
	t_var	*tmp_var;
	t_list	*tmp_lst;
	char	*value;

	tmp_lst = ft_lstfind_struct(mem->env, splt[0]);
	if (!tmp_lst)
		tmp_lst = ft_lstfind_struct(mem->var, splt[0]);
	if (tmp_lst)
	{
		value = ((t_var *)tmp_lst->content)->value;
		if (is_plus && splt[1] && value)
			((t_var *)tmp_lst->content)->value = ft_strjoin(value, splt[1]);
		else if (splt[1])
			((t_var *)tmp_lst->content)->value = ft_strdup(splt[1]);
		else
			((t_var *)tmp_lst->content)->value = ft_strdup("");
		free(value);
	}
	else if (ft_maslen(splt) == 2)
	{
		tmp_var = (t_var *)malloc(sizeof(t_var));
		tmp_var->name = ft_strdup(splt[0]);
		tmp_var->value = ft_strdup(splt[1]);
		ft_lstadd_back(&mem->var, ft_lstnew(tmp_var));
	}
}

char	ft_spec_char(char spec_char, char line)
{
	if(spec_char == 0)
	{
		if (line == 34 || line == 39)
			return line;
	}
	else if (spec_char == line)
		return (0);
	return (spec_char);
}

void	ft_start_commands(char	**strs_cmd, t_memory *mem)
{
	int		splt_len;

	splt_len = ft_strlen(strs_cmd[0]);

	if (ft_check_for_equal_sign(&strs_cmd, mem))
		return ;
	else if (!ft_strncmp(strs_cmd[0], "pwd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(strs_cmd[0], "echo", ft_strlen(strs_cmd[0])) && splt_len != 0)
//		ft_echo(strs_cmd, mem);
		ft_echo(strs_cmd);
	else if (!ft_strncmp(strs_cmd[0], "cd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_cd(strs_cmd[1], mem);		//Todo доделать "-bash: cd: too many arguments"
	else if (!ft_strncmp(strs_cmd[0], "exit", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_exit();
	else if (!ft_strncmp(strs_cmd[0], "env", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_env(mem);	//Todo он вроде как то с параметрами работает, надо расспросить как
	else if (!ft_strncmp(strs_cmd[0], "export", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_export(mem, strs_cmd);
	else if (!ft_strncmp(strs_cmd[0], "unset", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_unset(mem, strs_cmd);
	else if (strs_cmd[0][0] == '$' && strs_cmd[0][1] == '?')		//Это теперь не здесь иначе не работает "$a  $b"
		ft_print_varr_err();
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
	char spec_char;

	spec_char = 0;
	ft_go_end_space(&line);
	if (*line)
		count = 1;
	else
		return (0);
	while (*line)
	{
		spec_char = ft_spec_char(spec_char, *line);
		if (*line == ' ' && !spec_char)
		{
			ft_go_end_space(&line);
			if (*line)
				count++;
		}
		else if(*line)
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
	char spec_char;

	spec_char = 0;
	count_commands = ft_count_commands(line);
	arr_strings = (char **) malloc(sizeof (char **) * (count_commands + 1));
	ft_go_end_space(&line);
	i = 0;
	while (i < count_commands)
	{
		j = 0;
		arr_strings[i] = (char *) malloc(sizeof (char *) * (ft_str_len_space(line) + 1));
		while (*line) {
			spec_char = ft_spec_char_step(spec_char, &line);
			arr_strings[i][j] = *line;
			if ((*line == ' ' || !line) && !spec_char)
			{
				ft_go_end_space(&line);
				break;
			}
			j++;
			if (*line)
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
	char spec_char;

	spec_char = 0;
	if (*line)
		count = 1;
	else
		return (0);
	while (*line)
	{
		spec_char = ft_spec_char(spec_char, *line);
		if ((*line == ';' || *line == '|') && *(line + 1) && !spec_char)
		{
			line++;
			count++;
		}
		if (*line)
			line++;
	}
	if (spec_char != 0)
	{
		printf("minishell: syntax error\n"); //TODO доделать
		return 0;
	}
	return count;
}

int ft_find_char(char *str, int i)
{
	char spec_char;

	spec_char = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		spec_char = ft_spec_char(spec_char, str[i]);
		if(str[i] == ';' && !spec_char)
			return (i);
		i++;
	}
	return (ft_strlen(str));
}


int ft_find_space(char *str)
{
	int i = 1;

	if (!str)
		return (0);
	while (str[i])
	{
		if(str[i] == ' ' || str[i] == '$' || str[i] == '"')
			return (i);
		i++;
	}
	return (i);
}

char *ft_find_doll(char *line, t_memory *mem)
{
	t_list	*find;
	char	*str_find;
	int		end;
	char	*tmp;

	end = ft_find_space(line);
	tmp = ft_substr(line, 0, end);
	find = ft_lstfind_struct(mem->env, tmp + 1);
	if (!find)
		find = ft_lstfind_struct(mem->var, tmp + 1);
	if (find) {
		str_find = (char *) ((t_var *) find->content)->value; //TODO тут каст char * можно?
		free(tmp);
		return (str_find);
	}
	free(tmp);
	return (0);
}

int ft_len_doll(char *line, t_memory *mem)
{
	int	len;
	int	doll;

	len = 0;
	doll = 1;
	while (*line)
	{
		if (*line == '$')
		{
			doll = 1;
			len = len + ft_strlen(ft_find_doll(line, mem));
		}
		if (doll && *line == ' ')
			doll = 0;
		if (doll)
			len++;
		line++;
	}
	return (len);
}

void ft_change_var(char **line,  t_memory *mem)
{
	int 	j;
	int		i;
	char	*tmp;
	char	*str_find;
	char	*tmp_line;
	char	*num;
	int		size;

	tmp_line = *line;
	j = 0;
	size = (ft_strlen(*line) + ft_len_doll(*line, mem) + 1);
	tmp = (char *) malloc(size * sizeof (char)); // Перепроверить
	if(!tmp)
		return ;//TODO тут какая то ошибка должна выводится
	while (**line)
	{
		if (**line != '$')
		{
			tmp[j] = **line;
			(*line)++;
			j++;
		}
		else if (!ft_strncmp(*line, "$?", ft_strlen(*line)))
		{
			i = 0;
			num = ft_itoa(g_error);
			tmp = ft_realloc(tmp, size + ft_strlen(num));
			while (num[i])
				tmp[j++] = num[i++];
			free(num);
			(*line) += 2;
		}
		else
		{
			str_find = ft_find_doll(*line, mem);
			if (!str_find)
			{
				(*line)++;
				while (**line && **line != ' ' && **line != '$' )
					(*line)++;
			}
			else
			{
				(*line)++;
				while (*str_find || (**line && **line != ' ' && **line != '$'))
				{
					if (*str_find)
					{
						tmp[j] = *str_find;
						j++;
						str_find++;
					}
					if (**line && **line != ' ' && **line != '$')
						(*line)++;
				}
			}
		}
	}
	tmp[j] = '\0';
	free(tmp_line);
	*line = tmp;
}

//void ft_read_var(char **line, t_memory *mem)
//{
//	char 	*tmp_line;
//
//	tmp_line = *line;
//	while (**line)
//	{
//		if (**line == '$')
//				ft_change_var(&tmp_line, mem);
//		if (**line)
//			(*line)++;
//	}
//	*line = tmp_line;
//}

char	***ft_split_string(char *line, t_memory *mem)
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
		ft_change_var(&tmp, mem);//преобразовываем $
		arr_strs[i] = ft_parse_strings(tmp);
		free(tmp);
		start = end + 1;
		i++;
	}
	arr_strs[i] = NULL;
	return (arr_strs);
}

/*
char	*ft_check_doll(char spec_char, char **str, t_memory *mem)
{
	t_list	*find;
	char 	*str_find;


	if (spec_char)	//TODO доделать "'
		spec_char = spec_char;
	if (**str == '$')
	{
		find = ft_lstfind_struct(mem->env, *str + 1);
		if (!find)
			find = ft_lstfind_struct(mem->var, *str + 1);
		if (find)
			str_find = (char *)((t_var *)find->content)->value;		//TODO тут каст char * можно?
		if (str_find)
			return (str_find);
	}
	return (0);
}
*/


////TODO Доделать
////	$var
////  "\"
//// |
//// << >> <
void	ft_parse(char *line, char *home, t_memory *mem)
{
	char	***arr_commands;
	int	i;

	i = 0;
	arr_commands = ft_split_string(line, mem);
	while (arr_commands && arr_commands[i])
	{
		//тут добавить функцию которая добавляет переменные, или нет
		ft_start_commands(arr_commands[i], mem);
		i++;
	}
	free(arr_commands);
	ft_write_history(line, home);
}
