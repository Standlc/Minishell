#include "minishell.h"

void	duplicate_for_streams(t_command *command, t_pipe *pipes)
{
	if (command->position == -1)
	{
		if (dup2(pipes->fd[1], 1) == -1 || close(pipes->fd[0]) == -1)
			return (ft_putstr_fd("if failed\n", 2));
	}
	if (command->position == 1)
	{
		if (dup2(pipes->fd[0], 0) == -1)
			return (ft_putstr_fd("if failed\n", 2));
	}
	if (command->position == 0)
	{
		if (dup2(pipes->fd[0], 0) == -1 || dup2(pipes->link[1], 1) == -1 || close(pipes->link[0]) == -1)
			return (ft_putstr_fd("ifh failed\n", 2));
	}
}

void	another_command(t_command *command, t_pipe *pipes)
{
	char	*path;
	char	**env;

	env = *(environnement(NULL));
	if (command->arguments[0][0] == '/')
		path = command->arguments[0];  // check if name is valid ?
	else
		path = path_for_execve(env, command->arguments[0]);
	if (!path)
		return ;
	duplicate_for_streams(command, pipes);
	if (execve(path, command->arguments, env) == -1)
		(ft_putstr_fd("execve failed\n", 2), exit(errno));
}
