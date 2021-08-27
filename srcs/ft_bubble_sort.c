#include "minishell.h"

static void	ft_swap_lst(t_list *lst1, t_list *lst2)
{
	t_var	*tmp;

	tmp = ((t_var *)lst1->content);
	lst1->content = ((t_var *)lst2->content);
	lst2->content = tmp;
}

t_list	*ft_bubble_sort(t_list *lst)
{
	t_list	*lst_curr;
	t_list	*lst_next;
	char	*name_curr;
	char	*name_next;

	lst_curr = lst;
	while (lst_curr && lst_curr->next)
	{
		lst_next = lst_curr->next;
		while(lst_next)
		{
			name_curr = ((t_var *)lst_curr->content)->name;
			name_next = ((t_var *)lst_next->content)->name;
			if (ft_strncmp(name_curr, name_next, ft_strlen(name_curr)) > 0)
				ft_swap_lst(lst_curr, lst_next);
			lst_next = lst_next->next;
		}
		lst_curr = lst_curr->next;
	}
	return (lst);
}
