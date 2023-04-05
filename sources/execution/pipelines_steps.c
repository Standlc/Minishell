#include "minishell.h"

extern int	g_status;

int	is_child(t_command command)
{
	if (!command.arguments || !command.arguments[0] || !command.arguments[0][0])
		return (1);
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
		commands->close_pipe[0] = -1;
		commands->close_pipe[1] = -1;
	}
}

int	fork_command(t_command *command, int i)
{
	if (i != 0 || command[1].is_end || is_child(command[0]))
	{
		command->pid = fork();
		if (command->pid == -1)
			return (g_status = errno, perror("minishell: fork"), 1);
		if (command->pid == 0)
		{
			child_signals();
			execution_command(command);
			close_file(command->output_file);
			close_file(command->input_file);
			close_file(command->close_pipe[0]);
			close_file(command->close_pipe[1]);
			return (2);
		}
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
		(perror("minishell: close"), g_status = errno);
	if (commands[i].position == 0)
		i = multi_pipes(commands, &fd[0]);
	return (i);
}

void	end_of_pipeline(t_command *commands, int fd[2], int end)
{
	int	i;
	int	status_w;

	i = -1;
	status_w = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (commands[1].is_end && close(fd[0]) == -1)
		(perror("minishell: close"), g_status = errno);
	while (commands[++i].is_end && i < end)
	{
		if (i != 0 || commands[i + 1].is_end || is_child(commands[i]))
		{
			if (waitpid(commands[i].pid, &status_w, 0) == -1)
				(perror("minishell: waitpid"), g_status = errno);
			if (WIFEXITED(status_w))
				g_status = WEXITSTATUS(status_w);
			if (WIFSIGNALED(status_w))
			{
				g_status = 128 + WTERMSIG(status_w);
				commands[i].signal_stop = 1;
				if (WTERMSIG(status_w) == 2)
					write(1, "\n", 2);
				if (WTERMSIG(status_w) == 3)
					write(2, "Quit (core dumped)\n", 20);
			}
		}
	}
}
