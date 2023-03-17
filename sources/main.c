#include "minishell.h"

int	g_status;

void	for_env(t_pipeline *pipelines, char **env)
{
	static int call = 0;
	char	**env_dup;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (call != 0)
		return ;
	call++;
	env_dup = 
	while (env[i])
	{

	}
	while (pipelines[i].commands)
	{
		while (pipelines[i].commands[j].name)
			pipelines[i].commands[j].env = env;
	}
}

int	get_line(t_pipeline *pipelines, char **env)
{
	char	*line;

	line = readline(PROMPT);
	env = duplicate_env(env);
	while (line)
	{
		if (*line)
			add_history(line);
		parse_line(pipelines, line);
		for_env(pipelines, env);
		execution(pipelines);
		free_pipelines(pipelines);
		free(line);
		line = readline(PROMPT);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	g_status = 0;
	hook_signals();
	get_line(&pipelines, env);
	printf("Exit\n");
	rl_clear_history();
	return (0);
}
