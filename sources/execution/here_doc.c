#include "minishell.h"

extern int	g_status;

void	fill_here_doc(t_command command)
{
	int		here_doc_index;
	char	*str;

	here_doc_index = 0;
	while (command.heredoc_limit[here_doc_index])
	{
		printf("here_doc >");
		str = get_next_line(0);
		if (str && !command.heredoc_limit[here_doc_index + 1] && strncmp(str, command.heredoc_limit[here_doc_index], ft_strlen(command.heredoc_limit[here_doc_index] + 1)))
		{
			if (write(command.input_file, str, ft_strlen(command.heredoc_limit[here_doc_index])) == -1)
				(g_status = errno, perror("minishell: here_doc:"));
		}
		else if (str && !strncmp(str, command.heredoc_limit[here_doc_index], ft_strlen(command.heredoc_limit[here_doc_index] + 1)))
			here_doc_index++;
		free(str);
	}
}

void	check_here_doc(t_pipeline *pipelines)
{
	int	i;
	int	j;

	i = 0;
	while (pipelines[i].commands)
	{
		j = 0;
		while (pipelines[i].commands[j].is_end)
		{
			if (pipelines[i].commands[j].heredoc_limit && *(pipelines[i].commands[j].heredoc_limit))
				fill_here_doc(pipelines[i].commands[j]);
			j++;
		}
		i++;
	}
}