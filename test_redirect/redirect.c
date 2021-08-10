# include "stdio.h"
# include "stdlib.h"
# include "errno.h"
# include "string.h"
# include "fcntl.h"
# include "signal.h"
# include "sys/stat.h"
# include "libft/libft.h"

typedef struct	s_redir
{
	char** cmd;
	t_list	files;
	int 	p_priv;
	char	*to_file;
	char*	from_file;
	int		fd[2];
}				t_redir;


char	*ft_strremove(char *str, char *substr)
{
	char	*p;
	size_t	len;

	p = str;
	if (len > 0)
	{
		p = ft_strnstr(p, substr, ft_strlen(p));
		while (p)
		{
			ft_memmove(p, p + len, ft_strlen(p + len) + 1);
			p = ft_strnstr(p, substr, ft_strlen(p));
		}
	}
	return (str);
}

void	ft_echo(char* str)
{
	printf("%s", str);
}

void	ft_join_split_line(char** newstr, char* splt, char** name)
{
	char* new_str;
	char* tmp;
	int	i;

	if (name && name[1])
	{
		i = 2;
		new_str = ft_strdup(name[1]);
		while (name[i])
		{
			tmp = ft_strjoin(new_str, name[i]);
			free(new_str);
			new_str = tmp;
			i++;
		}
		tmp = ft_strjoin(*newstr, new_str);
		free(*newstr);
		*newstr = tmp;
	}
	if (splt)
	{
		tmp = ft_strjoin(*newstr, splt);
		free(*newstr);
		*newstr = tmp;
	}
}

t_list	*parse_redirect(char** str)
{
	int	i;
	char** splt;
	char* newstr;
	char** splt_name;
	t_list	*files;

	files = NULL;
	splt = ft_split(*str, '>');
	if (splt)
	{
		i = 1;
		newstr = ft_strdup(splt[0]);
		while (splt[i])
		{
			splt_name = ft_split(splt[i], ' ');
			if (splt_name)
			{
				ft_lstadd_back(&files, ft_lstnew(ft_strdup(splt_name[0])));
				ft_join_split_line(&newstr, NULL, splt_name);
				free_text(splt_name, ft_maslen(splt_name));
			}
			else
			{
				ft_lstadd_back(&files, ft_lstnew(ft_strdup(splt[i])));
				ft_join_split_line(&newstr, splt[i], NULL);
			}
			i++;
		}
		free_text(splt, ft_maslen(splt));
		*str = newstr;
	}
	return (files);
}

void	ft_redirect(t_list *files, char *str)
{
	int fd;
	int original;

	while (files->next)
	{
		fd = open((char*)(files->content), O_WRONLY | O_CREAT, 0755);
		close (fd);
		files = files->next;
	}
	fd = open((char*)(files->content), O_WRONLY | O_CREAT, 0755);
	original = dup(1);
	dup2(fd,1);
	ft_putstr_fd(str, 1);
	dup2(original, 1);
	ft_putstr_fd(str, 1);
}

int 	main(int argc, char** argv, char** env)
{
	t_list* files;
	char *str = "echo a > t echo a > y";

	files = parse_redirect(&str);
	ft_redirect(files, str);
	return (0);
}
