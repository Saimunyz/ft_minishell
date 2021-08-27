#include "minishell.h"

void	ft_print_export(t_memory *mem)
{
	t_list	*tmp;
	char	*name;
	char	*value;

	tmp = ft_bubble_sort(mem->env);
	while (tmp)
	{
		name = ((t_var *)tmp->content)->name;
		value = ((t_var *)tmp->content)->value;
		if (value)
			printf("declare -x %s=\"%s\"\n", name, value);
		else
			printf("declare -x %s\n", name);
		tmp = tmp->next;
	}
}
