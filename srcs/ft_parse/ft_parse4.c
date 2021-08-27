#include "minishell.h"

void	ft_go_end_space(char **line)
{
	while (**line && **line == ' ')
		(*line)++;
}

int	ft_count_commands(char *line)
{
	int		count;
	char	spec_char;

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
	return (count);
}

void	clean_a_cmd(t_cmd *a_cmd)
{
	a_cmd->p_priv = 0;
	a_cmd->p_next = 0;
	a_cmd->files = 0;
	a_cmd->echo = 0;
}

void
	parse_strings_2(int i, char *spec_char, char ***arr_strings, char **line)
{
	int	j;
	int	len;

	j = 0;
	len = ft_str_len_space(*line) + 1;
	(*arr_strings)[i] = (char *) malloc(sizeof(char) * len);
	ft_check_errno();
	while (**line && j < len)
	{
		*spec_char = ft_spec_char_step(*spec_char, line);
		if ((!(*spec_char) && (**line == 34 || **line == 39)) \
			|| (*spec_char) == **line)
			continue ;
		(*arr_strings)[i][j] = **line;
		if ((**line == ' ' || !(*line)) && !(*spec_char))
		{
			ft_go_end_space(line);
			break ;
		}
		j++;
		if (**line)
			(*line)++;
	}
	(*arr_strings)[i][j] = '\0';
}

char	**ft_parse_strings(char *line)
{
	char	**arr_strings;
	int		count_commands;
	int		i;
	char	spec_char;

	spec_char = 0;
	count_commands = ft_count_commands(line);
	arr_strings = (char **) malloc(sizeof(char **) * (count_commands + 1));
	ft_check_errno();
	ft_go_end_space(&line);
	i = 0;
	while (i < count_commands)
	{
		parse_strings_2(i, &spec_char, &arr_strings, &line);
		i++;
	}
	arr_strings[i] = 0;
	if (count_commands > 0 && arr_strings[0][0] == 0)
	{
		free(arr_strings[0]);
		arr_strings[0] = ft_strdup("''");
	}
	return (arr_strings);
}
