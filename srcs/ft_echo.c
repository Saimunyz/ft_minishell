#include "minishell.h"

void	ft_echo_write(char *str, int space)
{
	g_error = 0;
	if (space)
		write(1, " ", 1);
	if (str)
			ft_putstr_fd(str, 1);
}

void	ft_echo(char **str)
{
	int i;
	int	flag;
	int space;

	g_error = 0;
	i = 1;
	flag = 1;
	space = 0;
	if (str[1])
	{
		if (!ft_strncmp(str[1], "-n", ft_strlen(str[1])))
		{
			flag = 0;
			i = 2;
		}
		while (str[i]) {
			ft_echo_write(str[i], space);
			i++;
			space = 1;
		}
	}
	if (flag)
		write(1, "\n", 1);
}

