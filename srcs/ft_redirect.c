/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:22:02 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/16 22:30:38 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file	*ft_parse_redir(char *redir, int type, char sign)
{
	t_file	*f;
	char	*space;

	f = malloc(sizeof(t_file));
	f->mode = type;
	f->type = sign;
	while (*redir == sign)
		ft_memmove(redir, redir + 1, ft_strlen(redir));
	if (*redir == ' ')
		ft_memmove(redir, redir + 1, ft_strlen(redir));
	space = ft_strnstr(redir, " ", ft_strlen(redir));
	if (space)
	{
		f->filename = ft_substr(redir, 0, space - redir);
		ft_memmove(redir, redir + (space - redir), ft_strlen(redir));
	}
	else
	{
		f->filename = ft_strdup(redir);
		ft_memmove(redir, redir + ft_strlen(redir), ft_strlen(redir));
	}
	return (f);
}


char	**ft_parse_redirect(char** str, t_memory *mem)
{
	//t_list	*files;
	//t_list	*file_to_read;
	t_file	*f;
	int		i;
	char	**cmd;
	int		orig_out;
	//int		orig_in;

	i = 0;
	orig_out = dup(1);
	//orig_in = dup(0);
	//files = NULL;
	f = NULL;
	while (str[0][i])
	{
		if (str[0][i] == ' ' && (str[0][i + 1] == '>' || str[0][i + 1] == '<'))
			ft_memmove((*str) + i, (*str) + i + 1, ft_strlen(str[0] + i));
		if (str[0][i] == '>' && str[0][i + 1] == '>')
			f = ft_parse_redir(str[0] + i, 1089, '>');
			//ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 1089, '>'));
		else if (str[0][i] == '>')
			f = ft_parse_redir(str[0] + i, 577, '>');
			//ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 577, '>'));
		if (str[0][i] == '<')
			f = ft_parse_redir(str[0] + i, 0, '<');
			//ft_lstadd_back(&files, ft_parse_redir(str[0] + i, 0, '<'));
		if (f)
			f = ft_redirect(f);
		i++;
	}
	cmd = ft_parse_strings(str[0]);
	if (f && f->type == '>')
	{
		ft_start_commands(cmd, mem);
		dup2(orig_out, 1);
		i = 0;
		while (cmd[i])
				free(cmd[i++]);
			cmd[0] = ft_strdup("echo");
			cmd[1] = ft_strdup("-n");
			cmd[2] = NULL;
	}
	else if (f && f->type == '<')
	{
		//ft_start_commands(cmd, mem);
		//close(fd);
		//dup2(orig_in, 0);
		i = 0;
		while (cmd[i])
				free(cmd[i++]);
			cmd[0] = ft_strdup("echo");
			cmd[1] = ft_strdup("-n");
			cmd[2] = NULL;
	}

	return (cmd);
}

char	*ft_read_file(int fd)
{
	int		ret;
	char	*line;
	char	*text;
	char	*tmp;


	ret = get_next_line(fd, &text);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strjoin(text, line);
		free(line);
		free(text);
		text = tmp;
	}
	return (text);
}

t_file	*ft_redirect(t_file *file)
{
	//int		original_out;
	//char	*filename;
	// int		i;
	//char	*text;
	//char	*new_line;
	//char	*tmp;
	pid_t	pid;
	pid_t	status;
	int		fd;

	// i = 0;
	//original_out = dup(1);

	fd = open(file->filename, file->mode, 0755);

	if (file->type == '>')
		dup2(fd,1);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			// aur_cmd = ft_find_aur_command(a_cmd[i].cmd[0]);
			// if (!aur_cmd)
			// 	cmd = ft_find_command(a_cmd[i].cmd[0], ft_split(getenv("PATH"), ':'));
			dup2(fd,0);
			close(fd);
			char *newenviron[0]; //todo изменить
			newenviron[0] = NULL;
			char *str[2];
			str[0]= "/bin/cat";
			str[1] = NULL;
			char **strs = str;
			execve(strs[0], strs, newenviron);
			exit(0);
		}
		//close(fd);
		waitpid(pid, &status, 0);
		//close(fd);
		// text = ft_read_file(*fd);
		// new_line = ft_substr(cmd[0], 0, i);
		// tmp = ft_strjoin(new_line, " ");
		// free(new_line);
		// new_line = tmp;
		// tmp = ft_strjoin(new_line, text);
		// free(new_line);
		// free(text);
		// new_line = ft_strjoin(tmp, cmd[0] + i);
		// free(cmd[0]);
		// cmd[0] = new_line;
	}

	//close(*fd);
	//ft_free_file(file); // Сделать
	//file = NULL;
	return (file);


	//ft_start_commands(cmd, mem);

	//close (fd);
	//dup2(original_out, 1);
}
