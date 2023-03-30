#include "minishell.h"

extern int	g_status;

int	is_child(t_command command)
{
	if (!command.arguments[0])
		return (0);
	if (!strncmp(command.arguments[0], "cd", 3))
		return (0);
	if (!strncmp(command.arguments[0], "export", 7))
		return (0);
	if (!strncmp(command.arguments[0], "unset", 6))
		return (0);
	return (1);
}

void	pipeline_start(t_command *commands, int fd[2])
{
	if (commands[1].is_end)
		set_pipe(commands, fd);
	else
	{
		commands->position = 2;
		commands->file_close = -1;
	}
}

int	fork_command(t_command *command, int i)
{
	pid_t	pid;

	if ((i != 0 || command[i + 1].is_end) || is_child(command[i]))
	{
		pid = fork();
		if (pid == -1)
			return (g_status = errno, perror("minishell: fork"), 1);
		if (pid == 0)
			return (execution_command(command), 2);
	}
	else
		execution_env(command);
	return (0);
}

int	until_last_command(t_command *commands, int fd[2])
{
	int	i;

	i = 1;
	if (close(fd[1]) == -1)
		(g_status = errno, perror("minishell: close"));
	if (commands[i].position == 0)
		i = multi_pipes(commands, &fd[0]);
	return (i);
}

void	end_of_pipeline(t_command *commands, int fd[2], int end)
{
	int	i;

	i = -1;
	if (commands[1].is_end && close(fd[0]) == -1)
		(g_status = errno, perror("minishell: close"));
	while (commands[++i].is_end && i < end)
	{
		if ((i != 0 || commands[i + 1].is_end) || is_child(commands[i]))
		{
			if (waitpid(-1, &g_status, 0) == -1)
				(g_status = errno, perror("minishell: waitpid"));
			else if (WIFEXITED(g_status))
				g_status = WEXITSTATUS(g_status);
		}
	}
}