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

	i = -1;
	if (command->arguments[0] && directory_exist(command->arguments[0]))
		return (ft_putstr_fd("Permission denied\n", 2), g_status = 126, (void)0);
	if (command->arguments[0])
		return (ft_putstr_fd("No such directory\n", 2), g_status = 127, (void)0);
	new_env = *(environnement(NULL));
	if (!new_env)
		return ;
	while (new_env[++i])
	{
		ft_putstr_fd(new_env[i], command->output_file);
		ft_putchar_fd('\n', command->output_file);
	}
	close_files(command->output_file);
}
