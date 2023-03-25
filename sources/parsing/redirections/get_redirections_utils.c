#include "minishell.h"

int	handle_simple_left_redirection(t_command *command, char *file)
{
	if (command->input_file)
		close(command->input_file);
	command->input_file = open(file, O_WRONLY | O_TRUNC, 0644);
	if (command->input_file == -1)
		print_error("no such file or directory: ", file);
	return (command->input_file);
}

int	handle_simple_right_redirection(t_command *command, char *file)
{
	if (command->output_file)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_file == -1)
		print_error("could not open file: ", file);
	return (command->output_file);
}

int	handle_double_right_redirection(t_command *command, char *file)
{
	if (command->output_file)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_CREAT, 0644);
	if (command->output_file == -1)
		print_error("could not open file: ", file);
	return (command->output_file);
}
