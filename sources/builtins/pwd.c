#include "minishell.h"

extern int	g_status;

void	pwd_ms(t_command *command)
{
	char	*str;

	str = getcwd(NULL, 1024);
	g_status = errno;
	if (!str)
	{
		if (errno == ERANGE)
			ft_putstr_fd("Path exceeds max buffer lenght.\n", 2);
		else if (errno == ENOMEM)
			ft_putstr_fd("Memory cannot be allocated for path\n", 2);
	}
	else
		ft_putstr_fd(str, command->output_file);
	free(str);
	close_files(command->output_file);
}
