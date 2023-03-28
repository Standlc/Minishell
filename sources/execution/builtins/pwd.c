#include "minishell.h"

extern int	g_status;

void	pwd_ms(t_command *command)
{
	char	*str;

	close_file_pipe(command);
	g_status = 0;
	str = getcwd(NULL, 1024);
	if (!str)
	{
		if (errno == ERANGE)
			perror("minishell: pwd");
		else if (errno == ENOMEM)
			ft_putstr_fd(MEM, 2);
	}
	else
		ft_putstr_fd(str, command->output_file);
	ft_putchar_fd('\n', command->output_file);
	free(str);
	close_files(command->output_file);
	exit(g_status);
}
