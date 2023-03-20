#include "minishell.h"

extern int	g_status;

int	is_builtin(t_command *command)
{
	printf("test\n");
	printf(" %s\n", command->name);
	printf("test\n");
	if (!command->name)
		return (1);
	if (!strncmp(command->name, "echo", 5))
		return (echo_ms(command), 1);
	if (!strncmp(command->name, "cd", 3))
		return (cd_ms(command), 1);
	if (!strncmp(command->name, "pwd", 4))
		return (pwd_ms(command), 1);
	if (!strncmp(command->name, "export", 7) && command->arguments[0])
		return (export_ms(command), 1);
	if (!strncmp(command->name, "unset", 6))
		return (unset_ms(command), 1);
	if (!strncmp(command->name, "env", 4))
		return (env_ms(command), 1);
	if (!strncmp(command->name, "exit", 5))
		return (exit_ms(command), 1);
	return (0);
}

void	execution_command(t_command *command)
{
	if (is_builtin(command))
	{
		;
	}
	//else
	//	another_command(command);
}

void	execution_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (pipeline->commands[i].name)
	{
		execution_command(&(pipeline->commands[i]));
		i++;
	}
}

int	check_last_status(t_pipeline last)
{
	if (last.operator == AND)
	{
		if (g_status)
			return (1);
		if (!g_status)
			return (0);
	}
	if (last.operator == OR)
	{
		if (g_status)
			return (0);
		if (!g_status)
			return (1);
	}
	return (-1);
}

void	execution_global(t_pipeline *pipelines)
{
	int	i;

	i = 0;
	while (pipelines[i].commands)
	{
		if (i == 0 || (i != 0 && !check_last_status(pipelines[i])))
			execution_pipeline(&pipelines[i]);
		else if (pipelines[i + 1].commands && pipelines[i + 1].start_priority)
		{
			
			parenthesis(&pipelines[i], &i);
			i++;
		}
		i++;
		
	}
}
