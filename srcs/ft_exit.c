#include "minishell.h"

static int	ft_check_exit_num(char *str)
{
	int	i;

	if ((str[0] == '-' || str[0] == '+') && str[1] == '\0')
		return (1);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **cmd)
{
	int	num;

	g_error = 0;
	ft_change_term_mode(0);
	if (!cmd[1])
		exit(0);
	if (ft_check_exit_num(cmd[1]))
	{
		printf("exit\n");
		printf("minishell$: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	if (cmd[2])
	{
		printf("exit\nminishell$: exit: too many arguments\n");
		exit(1);
	}
	num = ft_atoi(cmd[1]);
	if (num > 255)
		num = num % 256;
	else if (num < 0)
		num = 256 + (num + 256 * (num % 256));
	printf("exit\n");
	exit(num);
}
