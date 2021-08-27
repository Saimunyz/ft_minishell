#include "minishell.h"

void	change_doll_quest(char ***line, char **tmp, int *j)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_itoa(g_error);
	while (num[i])
		(*tmp)[(*j)++] = num[i++];
	free(num);
	(**line) += 2;
}

void	ft_change_free(char ***line, char **tmp_line, char **tmp, int *j)
{
	(*tmp)[*j] = '\0';
	free(*tmp_line);
	**line = *tmp;
}

void	ft_change_tmp(char ***line, char **tmp, int *j)
{
	(*tmp)[*j] = ***line;
	(**line)++;
	(*j)++;
}

void	ft_change_loop(char ***line, char **tmp_line, char **tmp, t_memory *mem)
{
	int		j;
	char	spec_char;

	j = 0;
	spec_char = 0;
	while (**line)
	{
		spec_char = ft_spec_char(spec_char, ***line);
		if (!spec_char && (***line == 34 || ***line == 39))
			continue ;
		if (!(***line))
		{
			ft_change_free(line, tmp_line, tmp, &j);
			return ;
		}
		if (***line == '$' && *((**line) + 1) == '?' && spec_char != 39)
			change_doll_quest(line, tmp, &j);
		else if (***line == '$' && \
			*((**line) + 1) != ' ' && *((**line) + 1) && spec_char != 39)
			change_doll(line, tmp, &j, mem);
		else
			ft_change_tmp(line, tmp, &j);
	}
	ft_change_free(line, tmp_line, tmp, &j);
}

void	ft_change_var(char **line, t_memory *mem)
{
	char	*tmp;
	char	*tmp_line;
	int		size;

	tmp = 0;
	tmp_line = *line;
	size = (ft_strlen(*line) + ft_len_doll(*line, mem) + 1);
	tmp = (char *) malloc(size * sizeof(char));
	if (!tmp)
		return ;
	ft_change_loop(&line, &tmp_line, &tmp, mem);
}
