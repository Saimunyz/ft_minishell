//todo удалить перед сдачей.
//это файл пример работы пайпов

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIDE_OUT	0
#define SIDE_IN		1

#define STDIN		0
#define STDOUT		1

typedef struct s_args
{
	int is_pipe;
	int is_break;

}				t_args;


void read_arg(int argc, char *argv)
{


}

void ft_exec(const char *cmd, char **newargv, char **env)
{
	pid_t	pid;
	int		status;

//	char *newargv[] = { cmd };
//	char *newenviron[] = { NULL };

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, newargv, env);
	}

	waitpid(pid, &status, 0);
}

int main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char *a = "/bin/echo";
	char *b = "/bin/grep";

	pipe(fd);

	int fd0 = fd[0];
	int fd1 = fd[1];

	char *newargv[] = {a, "abc asdf asdf", NULL };
	char *newargv1[] = {b, "abc", NULL };

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execve(a, newargv, env);
	}
	waitpid(pid, &status, 0);

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		execve(b, newargv1, env);
	}

	close(fd1);
	close(fd0); //не понятно, надо ли этот закрывать или нет
	waitpid(pid, &status, 0);
	return (0);
}