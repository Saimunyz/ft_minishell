#include "minishell.h"

void	ft_pwd(void)
{
	char	*res;

	g_error = 0;
	res = getcwd(NULL, 0);	//тут надо на нал проверять.
	ft_check_errno();
	printf("%s\n", res);
	free(res);
}
