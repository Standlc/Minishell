#include "minishell.h"

extern int	g_status;

void	close_file_pipe(t_command *command)
{
	if (command->file_close != -1)
		if (close(command->file_close) == -1)
			perror("minishell: close");
}

void	duplicate_for_streams(t_command *command)
{
	if (dup2(command->input_file, 0) == -1
		|| dup2(command->output_file, 1) == -1)
		perror("minishell: dup2");
	close_file_pipe(command);
}

int	valide_argument_for_path(char *argument)
{
	if (argument[0] == '/' ||
		(argument[0] == '.' && argument[1] == '/')
		|| (argument[0] == '.' && argument[1] == '.'
		&& argument[1] == '/'))
			return (1);
	return (0);
}

void	another_command(t_command *command)
{
	char	*path;
	char	**env;

	env = *(environnement(NULL));
	if (valide_argument_for_path(command->arguments[0]))
			path = command->arguments[0];
	else
		path = path_for_execve(env, command->arguments[0]);
	if (!path)
		(ft_putstr_fd("command not found\n", 2), g_status = 127, exit(g_status));
	duplicate_for_streams(command);
	if (execve(path, command->arguments, env) == -1)
		(ft_putstr_fd("execve failed\n", 2), exit(errno));
}
