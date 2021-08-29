
# include "stdio.h"
# include "term.h"
# include "termios.h"
# include "errno.h"
# include "string.h"
# include "fcntl.h"
# include "signal.h"
# include "sys/stat.h"
# include "sys/wait.h"
#include <unistd.h>



int main()
{
	int pid;

	printf("erno %i \n", errno);
	pid = fork();
	printf("erno %i \n", errno);
	errno = 0;
}