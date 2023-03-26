#include "minishell.h"

extern int	g_status;

int	directory_exist(char *dir)
{
	DIR	*dirp;

	dirp = opendir(dir);
	if (dirp)
		return (closedir(dirp), 1);
	return (0);
}

void	env_ms(t_command *command)
{
	int		i;
	char	**new_env;

	g_status = 0;
	i = -1;
	if (command->arguments[1] && directory_exist(command->arguments[1]))
		return (ft_putstr_fd("Permission denied\n", 2), g_status = 126, exit(g_status));
	if (command->arguments[1])
		return (ft_putstr_fd("No such directory\n", 2), g_status = 127, exit(g_status));
	new_env = *(environnement(NULL));
	if (!new_env)
		return (exit(g_status));
	while (new_env[++i])
	{
		ft_putstr_fd(new_env[i], command->output_file);
		ft_putchar_fd('\n', command->output_file);
	}
	close_files(command->output_file);
	exit(g_status);
}
