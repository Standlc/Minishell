#include "minishell.h"

extern int	g_status;

void	duplicate_for_streams(t_command *command)
{
	if (dup2(command->input_file, 0) == -1
		|| dup2(command->output_file, 1) == -1)
		ft_putstr_fd("duplicate files failed\n", 2);
	if (command->file_close != -1)
		if (close(command->file_close) == -1)
			ft_putstr_fd("error close\n", 2);
}

void	another_command(t_command *command)
{
	char	*path;
	char	**env;

	env = *(environnement(NULL));
	if (command->arguments[0][0] == '/' ||
		(command->arguments[0][0] == '.' && command->arguments[0][1] == '/'))
			path = command->arguments[0];
	else
		path = path_for_execve(env, command->arguments[0]);
	if (!path)
		(ft_putstr_fd("command not found\n", 2), g_status = 127, exit(g_status));
	duplicate_for_streams(command);
	if (execve(path, command->arguments, env) == -1)
		(ft_putstr_fd("execve failed\n", 2), exit(errno));
}
