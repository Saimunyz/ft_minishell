/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/26 11:23:08 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "term.h"
# include "termios.h"
# include "libft.h"
# include "errno.h"
# include "string.h"
# include "fcntl.h"
# include "signal.h"
# include "sys/stat.h"
# include "sys/wait.h"

# define BUFF_SIZE 10
# define GET_DATA_ERR 1
# define COMMAND_ERR 2




typedef	struct s_file
{
	char	*filename;
	int		mode;
	char	*type;
}				t_file;

typedef struct	s_cmd
{
	char	**cmd;
	int 	p_next;
	int 	p_priv;
	int		fd[2];
	int		original;
	t_list	*files;
	int 	red;	//Сергей 23.08.21
	int 	echo;	//Сергей 23.08.21
}				t_cmd;

typedef struct	s_var
{
	char	*name;
	char 	*value;
}				t_var;

typedef struct	s_pipe
{
	int		fd0;
	int		fd1;
	int		fd[2];
	int 	order;
}				t_pipe;

typedef struct s_hist
{
	t_list	*hist;
	t_list	*start;
}			t_hist;

typedef struct s_memory
{
	t_list	*shlvl;
	t_list	*pwd;
	t_list	*oldpwd;
	t_list	*env;
	t_list	*var;
}			t_memory;

typedef	struct s_l_cmd
{
	char *cmd;
	char *local_cmd;
	char *aur_cmd;
	char **env;
	t_memory *mem;
}		t_l_cmd;

int		g_error;

void	ft_check_errno(void);
void	ft_change_term_mode(int change);
int		ft_get_term_info(void);
void	ft_parse(char *line, char *home, t_memory *mem);
void	ft_pwd(void);
void	ft_del_char(int *len, char **line);
void	ft_del_line(int *len, char **line);
//void	ft_echo(char **str, t_memory *mem);
void	ft_echo(char **str);
void	ft_cd(char *path, t_memory *mem);
void	ft_exit(char **cmd);
void	ft_commands(t_cmd *a_cmd, int i, t_memory *mem);
void	ft_init_read(t_hist *hist, char **line, char **lettr, char *home);
void	ft_write_history(char *command, char *home);
t_list	*ft_read_history(char *home);
t_list	*ft_lstfind_struct(t_list *lst, void *name);
void	ft_put_history_down(int *len, char **line, t_hist *hist);
void	ft_put_history_up(int *len, char **line, t_hist *hist);
int		ft_check_sigint(char **line, char *character);
void	ft_check_eof(char **line, char *character, t_hist *hist);
void	ft_init_mem(t_memory *env, char **envp);
void	ft_env(t_memory *mem);
void	ft_add_var(char	**splt, t_memory *mem, int is_plus);
void	ft_check_var(char *strs_cmd, t_memory *mem);
void	ft_export(t_memory *mem, char **strs_cmd);
void	ft_free_content(void *content);
void	ft_start_commands(char **strs_cmd, t_memory *mem, int not_found, char **env);
char	**ft_wise_split(char *strs_cmd);
void	ft_unset(t_memory *mem, char **var);
void	ft_parse_redirect(char** str, t_memory *mem, t_cmd *a_cmd);
void	ft_redirect(t_cmd *cmd, t_memory *mem);
t_list	*ft_bubble_sort(t_list *lst);
void	ft_print_varr_err(void);
char	**ft_parse_strings(char *line);
void	ft_change_var(char **line,  t_memory *mem);
char	ft_spec_char(char spec_char, char line);
void	ft_sig_handler(int num);
char	*ft_getenv(char *name, t_memory *mem);
char	**ft_lst2str(t_list *lst);
void	ft_clear_arr(char **arr);
int		ft_chek_for_equal_sign(char **strs_cmd);
int		ft_check_symbols(char chr);
void	commands_close(t_cmd *a_cmd, int i);
t_cmd	*ft_split_string(char *line, t_memory *mem);
int		ft_variables(char **strs_cmd, t_memory *mem);
void	change_doll(char ***line, char **tmp, int *j, t_memory *mem);
int		ft_len_doll(char *line, t_memory *mem);
char	*ft_find_doll(char *line, t_memory *mem);
void	clean_a_cmd(t_cmd *a_cmd);
int		ft_find_char(char *str, int i, t_cmd *a_cmd);
int		ft_count_strs(char *line);
int		ft_str_len_space(char *line);
char	ft_spec_char_step(char spec_char, char **line);
char	*ft_spec_char_loop(char **str);
char	*ft_find_local_command(char *command);
void	ft_command_not_found(char *cmd);
char	*ft_find_command(char *command, char **path);
char	*ft_find_aur_command(char *command);
void	command_fork(t_cmd *a_cmd, int i, t_l_cmd l_cmds);
void	command_pid(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found);
void	ft_print_export(t_memory *mem);
#endif
