#include "minishell.h"

void	pwd_ms(t_command *command)
{
	char	*str;
	int		fd_out;

	open_files(command, &fd_out);
	str = getcwd(NULL, 1024);
	status = errno;
	if (!str)
	{
		if (errno == ERANGE)
			ft_putstr_fd("Path exceeds max buffer lenght.\n", 2);
		else if (errno == ENOMEM)
			ft_putstr_fd("Memory cannot be allocated for path\n", 2);
	}
	else
		ft_putstr_fd(str, fd_out);
	free(str);
	close_files(&fd_out);
}
