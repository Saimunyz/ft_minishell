#include "minishell.h"

void	ft_env(t_memory *mem)
{
	t_list	*tmp;
	char	*name;
	char	*value;

	tmp = mem->env;
	while (tmp)
	{
		name = ((t_var *)tmp->content)->name;
		value = ((t_var *)tmp->content)->value;
		if (value)
			printf("%s=%s\n", name, value);
		tmp = tmp->next;
	}
}
