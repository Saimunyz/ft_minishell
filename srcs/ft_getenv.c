#include "minishell.h"

char	*ft_getenv(char *name, t_memory *mem)
{
	t_var	*var;
	t_list	*find;

	find = ft_lstfind_struct(mem->env, name);
	if (!find)
		return NULL;
	var = ((t_var*)find->content);
	return (var->value);
}
