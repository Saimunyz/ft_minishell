#include "minishell.h"

void	ft_exit(void)
{
	ft_change_term_mode(0);
	exit(0);
}
