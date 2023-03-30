#include "minishell.h"

int	is_standard(int fd)
{
	if (fd == 0 || fd == 1 || fd == 2)
		return (1);
	return (0);
}

void	set_files(t_command *command, int link[2], int fd)
{
	if (command->input_file == 0)
		command->input_file = fd;
	if (command->output_file == 1)
		command->output_file = link[1];
	command->file_close = link[0];
}
