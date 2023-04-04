#include "minishell.h"

extern int	g_status;

int	skip_pipeline(char **line, t_pipeline *pipeline, t_heredoc_fds **heredoc_fds)
{
	pipeline->parenthesis = 0;
	handle_parenthesis(line, pipeline, '(');
	while (**line && !is_operator(*line))
	{
		if (is_quote(**line))
			check_quotes(line);
		else if (is_heredoc(*line))
		{
			close((**heredoc_fds).fds[0]);
			(**heredoc_fds).fds[0] = 0;
			*heredoc_fds += 1;
			skip_special_symbol(line);
		}
		if (is_parenthesis(*line))
			handle_parenthesis(line, pipeline, ')');
		else
			*line += 1;
	}
	get_operator(line, pipeline);
	return (0);
}

void	skip_pipeline_group(char **line, t_heredoc_fds *heredoc_fds)
{
	t_pipeline	curr;
	int			parenthesis;

	parenthesis = 0;
	while (**line)
	{
		if (skip_pipeline(line, &curr, &heredoc_fds))
			continue ;
		if (parenthesis == 0 && curr.parenthesis < 0)
			return ;
		parenthesis += curr.parenthesis;
		if (!parenthesis)
			return ;
	}
}

void	skip_pipelines_to_not_execute(char **line, t_pipeline last, t_heredoc_fds *heredoc_fds)
{
	if (last.operator == AND && g_status)
			skip_pipeline_group(line, heredoc_fds);
	else if (last.operator == OR && !g_status)
			skip_pipeline_group(line, heredoc_fds);
}
