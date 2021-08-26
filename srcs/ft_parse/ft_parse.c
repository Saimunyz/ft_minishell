#include "minishell.h"

char ft_spec_char_step(char spec_char, char **line)
{
	if (spec_char == 0)
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

char *ft_spec_char_loop(char **str)
{
	int i;
	char *tmp;
	char spec_char;
	char *tmp_str;

	i = 0;
	tmp_str = *str;
	spec_char = 0;
	if (!(*str))
		return (*str);
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

int ft_variables(char **strs_cmd, t_memory *mem)
{
	int i;

	i = 0;
	while (strs_cmd && strs_cmd[i])
	{
		if (!ft_strnstr(strs_cmd[i], "=", ft_strlen(strs_cmd[i])) || strs_cmd[i][0] == '='
			|| !ft_isalpha(strs_cmd[i][0]))
			return (0);
		i++;
	}
	i = 0;
	while (strs_cmd && strs_cmd[i])
	{
		ft_check_var(strs_cmd[i], mem);
		i++;
	}
	return (1);

}

void ft_check_var(char *strs_cmd, t_memory *mem)
{
	char **splt;
	char *tmp_splt;
	int isPlus;

	splt = NULL;
	isPlus = 0;
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
	if (splt)
	{
		splt[1] = ft_spec_char_loop(&splt[1]);
		ft_add_var(splt, mem, isPlus);
		free_text(splt, ft_maslen(splt));
	}
}

void ft_add_var(char **splt, t_memory *mem, int is_plus)
{
	t_var *tmp_var;
	t_list *tmp_lst;
	char *value;

	tmp_lst = ft_lstfind_struct(mem->env, splt[0]);
	if (!tmp_lst)
		tmp_lst = ft_lstfind_struct(mem->var, splt[0]);
	if (tmp_lst)
	{
		value = ((t_var *) tmp_lst->content)->value;
		if (is_plus && splt[1] && value)
			((t_var *) tmp_lst->content)->value = ft_strjoin(value, splt[1]);
		else if (splt[1])
			((t_var *) tmp_lst->content)->value = ft_strdup(splt[1]);
		else
			((t_var *) tmp_lst->content)->value = ft_strdup("");
		free(value);
	}
	else if (ft_maslen(splt) == 2)
	{
		tmp_var = (t_var *) malloc(sizeof(t_var));
		tmp_var->name = ft_strdup(splt[0]);
		tmp_var->value = ft_strdup(splt[1]);
		ft_lstadd_back(&mem->var, ft_lstnew(tmp_var));
	}
}

char ft_spec_char(char spec_char, char line)
{
	if (spec_char == 0)
	{
		if (line == 34 || line == 39)
			return line;
	}
	else if (spec_char == line)
		return (0);
	return (spec_char);
}

void ft_start_commands(char **strs_cmd, t_memory *mem, int not_found, char **env) //add ref
{
	int splt_len;

	if (not_found)
		return;
	splt_len = ft_strlen(strs_cmd[0]);
	if (!ft_strncmp(strs_cmd[0], "pwd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(strs_cmd[0], "echo", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_echo(strs_cmd);
	else if (!ft_strncmp(strs_cmd[0], "cd", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_cd(strs_cmd[1], mem);        //Todo доделать "-bash: cd: too many arguments"
	else if (!ft_strncmp(strs_cmd[0], "exit", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_exit(strs_cmd);
	else if (!ft_strncmp(strs_cmd[0], "env", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_env(mem);    //Todo он вроде как то с параметрами работает, надо расспросить как
	else if (!ft_strncmp(strs_cmd[0], "export", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_export(mem, strs_cmd);
	else if (!ft_strncmp(strs_cmd[0], "unset", ft_strlen(strs_cmd[0])) && splt_len != 0)
		ft_unset(mem, strs_cmd);
	else if (*strs_cmd[0] != '\3')  //сергей 25.08.21
		execve(strs_cmd[0], strs_cmd, env);
}


int ft_str_len_space(char *line)
{
	int count;
	char spec_char;

	count = 0;
	spec_char = 0;
	spec_char = ft_spec_char(spec_char, *line);
	while (*line && (*line != ' ' || spec_char))
	{

		line++;
		count++;
		spec_char = ft_spec_char(spec_char, *line);
	}
	return (count);
}

void ft_go_end_space(char **line)
{
	while (**line && **line == ' ')
		(*line)++;
}

int ft_count_commands(char *line)
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
		else if (*line)
			line++;
	}
	return count;
}

void clean_a_cmd(t_cmd *a_cmd)
{
	a_cmd->p_priv = 0;
	a_cmd->p_next = 0;
	a_cmd->files = 0;
	a_cmd->echo = 0;
}

char **ft_parse_strings(char *line)
{
	char **arr_strings;
	int count_commands;
	int i;
	int j;
	char spec_char;
	int len;

	spec_char = 0;
	count_commands = ft_count_commands(line);
	arr_strings = (char **) malloc(sizeof(char **) * (count_commands + 1));
	ft_go_end_space(&line);
	i = 0;
	while (i < count_commands)
	{
		j = 0;
		len = ft_str_len_space(line) + 1;
		arr_strings[i] = (char *) malloc(sizeof(char) * len);
		while (*line && j < len)
		{
			spec_char = ft_spec_char_step(spec_char, &line);
			if ((!spec_char && (*line == 34 || *line == 39)) || spec_char == *line)  //18.08.2021
				continue;
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
	arr_strings[i] = 0;
	if (count_commands > 0 && arr_strings[0][0] == 0)
	{
		free(arr_strings[0]);
		arr_strings[0] = ft_strdup("''"); //todo защитить от утечек
	}
	return (arr_strings);
}

int ft_count_strs(char *line)
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
		if (*line == '|' && *(line + 1) && !spec_char)
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

int ft_find_char(char *str, int i, t_cmd *a_cmd)
{
	char spec_char;

	spec_char = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		spec_char = ft_spec_char(spec_char, str[i]);
		if (str[i] == '|' && !spec_char)
		{
			if (str[i] == '|')
				a_cmd->p_next = 1;
			return (i);
		}
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
		if (str[i] == ' ' || str[i] == '$' || str[i] == '"' || str[i] == 39 || str[i] == '=') //25.08.21
			return (i);
		i++;
	}
	return (i);
}

char *ft_find_doll(char *line, t_memory *mem)
{
	t_list *find;
	char *str_find;
	int end;
	char *tmp;

	end = ft_find_space(line);
	tmp = ft_substr(line, 0, end);
	if (*line == 34 || *line == 39) //костыли
		return (0);
	if (end == 1 && *line == '$' && *(line + 1) == '"')
	{//костыли для "$"
		free(tmp); //Сергей 25.08.21
		return (ft_strdup("$"));
	} // c=12
	find = ft_lstfind_struct(mem->env, tmp + 1);
	if (!find)
		find = ft_lstfind_struct(mem->var, tmp + 1);
	if (find)
	{
		str_find = (char *) ((t_var *) find->content)->value; //TODO тут каст char * можно?
		free(tmp);
		return (ft_strdup(str_find)); //Сергей 25.08.21 костыль для фри
	}
	free(tmp);
	return (0);
}

int ft_len_doll(char *line, t_memory *mem)
{
	int len;
	int doll;
	char *tmp;

	len = 0;
	doll = 1;
	while (*line)
	{
		if (*line == '$')
		{
			doll = 1;
			tmp = ft_find_doll(line, mem); //Сергей 25.08.21
			len = len + ft_strlen(tmp); //Сергей 25.08.21
			if (tmp)
				free(tmp); //Сергей 25.08.21
		}
		if (doll && *line == ' ')
			doll = 0;
		if (doll)
			len++;
		line++;
	}
	return (len);
}

/////////////////////////////////////////////////////////////////
void change_doll_var (char ***line, char **str_find, char **tmp, int *j) //ref 26.08.21
{
	char *tmp_find;

	tmp_find = *str_find; //Сергей 25.08.21
	(**line)++;
	while (**str_find ||
		   (***line && ***line != ' ' && ***line != '$' && ***line != 39 && ***line != 34 &&
			***line != '=')) //25.08.21
	{
		if (**str_find)
		{
			(*tmp)[*j] = **str_find;
			(*j)++;
			(*str_find)++;
		}
		while (***line && ***line != ' ' && ***line != 39 && ***line != 34 && ***line != '$' &&
			   ***line != '=')  //25.08.21
			(**line)++;
	}
	free(tmp_find); //Сергей 25.08.21
}


//void change_doll (char ***line, char **str_find, char **tmp, int *j) //ref 26.08.21
void change_doll (char ***line, char **tmp, int *j, t_memory *mem) //ref 26.08.21
{
	char *str_find;

	str_find = ft_find_doll(**line, mem);
	if (!str_find)
	{
		(**line)++;
		while (***line && ***line != ' ' && ***line != 39 && ***line != 34 && ***line != '$' &&
			   ***line != '=')  //16.08.21
			(**line)++;
	}
	else
		change_doll_var (line, &str_find, tmp, j);
}

void change_doll_quest(char ***line, char **tmp, int *j) //ref 26.08.21
{
	int i;
	char *num;

	i = 0;
	num = ft_itoa(g_error);
	while (num[i])
		(*tmp)[(*j)++] = num[i++];
	free(num);
	(**line) += 2;
}

void ft_chane_free(char ***line, char **tmp_line, char **tmp, int *j)
{
	(*tmp)[*j] = '\0';
	free(*tmp_line);
	**line = *tmp;
}

void ft_change_var(char **line, t_memory *mem)
{
	int j;
	char *tmp;
	char *tmp_line;
	char spec_char;
	int size;

	spec_char = 0;
	tmp = 0; //возможно избыточно
	tmp_line = *line;
	j = 0;
	size = (ft_strlen(*line) + ft_len_doll(*line, mem) + 1);
	tmp = (char *) malloc(size * sizeof(char));
	if (!tmp)
		return;//TODO тут какая то ошибка должна выводится
	while (**line)
	{
		spec_char = ft_spec_char(spec_char, **line);
		if (!spec_char && (**line == 34 || **line == 39))  //18.08.2021
			continue;
		if (!(**line))//16.08.2021
		{
			ft_chane_free(&line, &tmp_line, &tmp, &j);
			return;//16.08.2021
		}
		if (**line == '$' && *((*line) + 1) == '?' && spec_char != 39)
			change_doll_quest(&line, &tmp, &j);
		else if (**line == '$' && *((*line) + 1) != ' ' && *((*line) + 1) && spec_char != 39)
			change_doll (&line, &tmp, &j, mem);
		else
		{
			tmp[j] = **line;
			(*line)++;
			j++;
		}
	}
	ft_chane_free(&line, &tmp_line, &tmp, &j);
}

//////////////////////////////////////////////////////////////////////////////////

t_cmd *ft_split_string_2(t_cmd *a_cmd, char *line, t_memory *mem, int count_strs)
{
	int i;
	int start;
	int end;
	char *tmp;

	i = 0;
	start = 0;
	while (i < count_strs)
	{
		clean_a_cmd(&a_cmd[i]);
		end = ft_find_char(line, start, &a_cmd[i]);
		if (i > 0)
			a_cmd[i].p_priv = a_cmd[i - 1].p_next;
		tmp = ft_substr(line, start, end - start);
		ft_change_var(&tmp, mem);
		ft_parse_redirect(&tmp, mem, &(a_cmd[i]));
		pipe(a_cmd[i].fd);
		free(tmp);
		start = end + 1;
		i++;
	}
	a_cmd[i].cmd = 0;
	return (a_cmd);
}

t_cmd *ft_split_string(char *line, t_memory *mem)
{
	int count_strs;
	t_cmd *a_cmd;

	count_strs = ft_count_strs(line);
	if (count_strs == 0)
		return NULL;
	a_cmd = (t_cmd *) malloc(sizeof(t_cmd) * (count_strs + 1));
	ft_split_string_2(a_cmd, line, mem, count_strs);
	return (a_cmd);
}

/////////////////////////////////////////////////////////////

void rm_pipe(t_cmd **a_cmd, int i)
{
	if ((*a_cmd)[i].p_next)
	{
		(*a_cmd)[i].p_next = 0;
		if ((*a_cmd)[i + 1].p_priv)
		{
			(*a_cmd)[i + 1].p_priv = 0;
		}
	}
}

void clear_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void clear_a_cmd(t_cmd *a_cmd, int i) // 26.08.21 ref
{
	int j;

	j = 0;
	while (a_cmd[i].cmd[j]) //Сергей 26.08.21
		free(a_cmd[i].cmd[j++]);
	free(a_cmd[i].cmd);
}

void ft_parse_command(t_cmd *a_cmd, int i, t_memory *mem) // 26.08.21 ref
{
	if (a_cmd[i].cmd[0] && a_cmd[i].cmd[0][0] == '\3')
	{
		ft_clear_arr(a_cmd[i].cmd); //Сергей 26.08.21
		free(a_cmd); //Сергей 26.08.21
		return;
	}
	if (!a_cmd[i].red)
		ft_commands(a_cmd, i, mem);
	if (a_cmd[i].echo) //Сергей 24.08.21
		clear_a_cmd(a_cmd, i);
}

void ft_parse(char *line, char *home, t_memory *mem)
{
	t_cmd *a_cmd;
	int i;

	i = 0;
	a_cmd = ft_split_string(line, mem);
	ft_write_history(line, home); //перенес вверх, что бы все писало (Сергей)
	while (a_cmd && a_cmd[i].cmd)
	{
		if (ft_variables(a_cmd[i].cmd, mem))
		{
			rm_pipe(&a_cmd, i);
			clear_a_cmd(a_cmd, i);
			i++;
			continue;
		}
		ft_parse_command(a_cmd, i, mem);
		i++;
	}
	free(a_cmd);
}
