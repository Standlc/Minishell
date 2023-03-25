#include "minishell.h"

char	**duplicate_for_execve(t_command *command)
{
	char	**cmd;
	int		i;

	i = 1;
	cmd = malloc(sizeof(char *) * (bigarray_len(command->arguments) + 2));
	if (!cmd)
		(ft_putstr_fd("Cannot allocate memory\n", 2), exit(errno));
	cmd[0] = ft_strdup(command->name);
	while (command->arguments[i - 1])
	{
		cmd[i] = ft_strdup(command->arguments[i - 1]);
		if (!cmd[i])
			(free_dup(cmd), ft_putstr_fd("Cannot allocate memory\n", 2), exit(errno));
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

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
	char	**cmd;

	cmd = duplicate_for_execve(command);
	if (!cmd)
		return ;
	env = *(environnement(NULL));
	if (command->name[0] == '/')
		path = command->name;  // check if name is valid ?
	else
		path = path_for_execve(env, command->name);
	if (!path)
		return ;
	duplicate_for_streams(command, pipes);
	if (execve(path, cmd, env) == -1)
		(ft_putstr_fd("execve failed\n", 2), exit(errno));
}