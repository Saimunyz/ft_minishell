#include "minishell.h"

int	ft_parse(char *line, char *home)
{
	char	**splt;
	int		splt_len;

	splt = ft_split(line, ' ');
	splt_len = ft_strlen(splt[0]);
	if (!ft_strncmp(splt[0], "pwd", ft_strlen(splt[0])) && splt_len != 0)
		ft_pwd();
	else if (!ft_strncmp(splt[0], "echo", ft_strlen(splt[0])) && splt_len != 0)
		ft_echo(splt[1], 1);
	else if (!ft_strncmp(splt[0], "cd", ft_strlen(splt[0])) && splt_len != 0)
		ft_cd(splt[1]);
	else if (!ft_strncmp(splt[0], "exit", ft_strlen(splt[0])) && splt_len != 0)
		ft_exit();
	else if (!ft_strncmp(splt[0], "$?", ft_strlen(splt[0])) && splt_len != 0)
		printf("minishell: %d: command not found\n", g_error);
	else if (*line != '\0')
		ft_commands(splt);
	ft_write_history(line, home);
	free_text(splt, ft_maslen(splt));
	return (0);
}
