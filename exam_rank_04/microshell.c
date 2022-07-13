#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct	s_args
{
	char	**args;
	int		is_pipe;
	int		is_semi_colon;
}				t_args;

t_args	*ft_init(void)
{
	t_args	*mini;

	mini = malloc(sizeof(t_args));
	mini->args = 0;
	mini->is_pipe = 0;
	mini->is_semi_colon = 0;
	return (mini);
}

int ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char const *str)
{
	char	*copy;
	int		i;

	if (!(copy = (char*)malloc(sizeof(*copy) * (ft_strlen(str) + 1))))
		return (0);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

void	argv_to_struct(t_args *mini, char **argv)
{
	int i;

	i = 1;
	while(argv[i])
	{
		mini->args[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	mini->args[i - 1] = 0;
}

void	parse_arg(t_args *mini)
{
	int		i;

	i = 0;
	while (mini->args[i])
	{
		if (strcmp("|", mini->args[i]) == 0)
			mini->is_pipe = 1;
		else if (strcmp(";", mini->args[i]) == 0)
			mini->is_semi_colon = 1;
		i++;
	}
	//printf("is_pipe: %d\nis_semi_colon: %d\n", mini->is_pipe, mini->is_semi_colon);
}

void	exec_cmds(t_args *mini, char **env)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (strcmp("cd", mini->args[i]) == 0)
		{
			if (chdir(mini->args[i + 1]))
			{
				if (!mini->args[i + 1])
					printf("error: cd: bad arguments\n");
				else
				{
					printf("error: cd: cannot change directory to ");
					printf("%s\n", mini->args[i + 1]);
				}
				return;
			}
		}
		else if (execve(mini->args[i], mini->args, env) < 0)
			return;
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	(void)env;
	t_args	*mini;
	int		i;

	i = 1;
	mini = ft_init();
	mini->args = (char **)malloc(sizeof(char *) * (argc));
	argv_to_struct(mini, argv);
	parse_arg(mini);
	exec_cmds(mini, env);
	// i = 0;
	// while (mini->args[i] != '\0')
	// {
	// 	printf("cadena: %s\n", mini->args[i]);
	// 	i++;
	// }
}