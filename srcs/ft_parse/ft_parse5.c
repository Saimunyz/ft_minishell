#include "minishell.h"

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
	if (find && ((t_var *) find->content)->value)
	{
		str_find = (char *) ((t_var *) find->content)->value; //TODO тут каст char * можно?
		free(tmp);
		return (ft_strdup(str_find)); //Сергей 25.08.21 костыль для фри
	}
	free(tmp);
	return (0);
}
