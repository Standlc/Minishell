#include "minishell.h"

extern int	g_status;

void	env_ms(t_command *command)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = *(environnement());
	if (!new_env)
		return ;
	while (new_env[++i])
		ft_putstr_fd(new_env[i], command->output_file);
	close_files(command->output_file);
}
