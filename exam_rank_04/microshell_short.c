#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int putstr(char const *str, char const *arg)
{
	int i = 0;
	while (str[i])
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			write(STDERR_FILENO, &arg[i], 1);
			i++;
		}
	}
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int execute_cmd(char **argv, int i, int tmp_fd, char **env)
{
	argv[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(argv[0], argv, env);
	return(putstr("error: cannot execute ", argv[0]));
}

int main(int argc, char **argv, char **env)
{
	int i = 0;
	int pid = 0;
	int fd[2];
	int tmp_fd;
	(void)argc;

	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if(i != 2)
				putstr("error: cd bad arguments", NULL);
			else if (chdir(argv[1]) != 0)
				putstr("error: cd: cannot change directory to ", argv[1]);
		}
		else if(i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			pid = fork();
			if (pid == 0)
			{
				if (execute_cmd(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1);
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (i != 0 && strcmp(argv[i], "|") == 0)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (execute_cmd(argv, i, tmp_fd, env))
					return(1);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}
