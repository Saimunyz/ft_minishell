#include "minishell.h"

//////////////////////////////////////////////////////////////////////////////

void check_var_splt(char ***splt, t_memory *mem, int *isPlus)
{
	if (*splt)
	{
		(*splt)[1] = ft_spec_char_loop(&((*splt)[1]));
		ft_add_var(*splt, mem, *isPlus);
		free_text(*splt, ft_maslen(*splt));
	}
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
	check_var_splt(&splt, mem, &isPlus);
}

//////////////////////////////////////////////////////////////////////////



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
