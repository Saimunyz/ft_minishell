#include "minishell.h"

char	ft_spec_char_step(char spec_char, char **line)
{
	if (spec_char == 0)
	{
		if (**line == 34 || **line == 39)
		{
			spec_char = **line;
			(*line)++;
			return (spec_char);
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
	int		i;
	char	*tmp;
	char	spec_char;
	char	*tmp_str;

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
	return (tmp);
}

int	ft_variables(char **strs_cmd, t_memory *mem)
{
	int	i;

	i = 0;
	while (strs_cmd && strs_cmd[i])
	{
		if (!ft_strnstr(strs_cmd[i], "=", ft_strlen(strs_cmd[i])) \
			|| strs_cmd[i][0] == '=' || !ft_isalpha(strs_cmd[i][0]))
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
