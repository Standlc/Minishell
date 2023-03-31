#include "minishell.h"

extern int	g_status;

void	exit_pipeline(t_pipeline *pipelines, int i)
{
	t_command	*command;
	char		**env;

	env = *(environnement(NULL));
	command = pipelines[i].commands;
	command->position = 2;
	ft_putstr_fd("exit\n", 1);
	free_dup(env);
	free_pipelines(pipelines);
	// rl_clear_history();
	exit(g_status);
}