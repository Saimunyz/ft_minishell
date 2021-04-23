
#include "minishell.h"

void	ft_clear_global(void)
{
	//free(g_var.env_home);
	free(g_var.path_hist);
}

void	ft_global_init(void)
{
	g_var.env_home = getenv("HOME");
	g_var.path_hist = ft_strjoin(g_var.env_home, "/.minishell_history");
}
