#include "minishell.h"

extern int	g_status;

void	exit_process(t_pipeline pipeline, t_blocks *blocks)
{
	char	**env;

	free_pipeline(pipeline);
	env = *(environnement(NULL));
	free_str_arr(env);
	rl_clear_history();
	free(blocks->line_ptr);
	close_heredoc_fds_ins(blocks->heredoc_ptr);
	free(blocks->heredoc_ptr);
	exit(g_status);
}
