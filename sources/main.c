/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:52:38 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/27 14:59:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	get_commands(char *prompt)
// {
// 	int	i;

// 	i = 0;
// 	while (prompt[i])
// 	{
// 		i++;
// 	}
// }

int	main()
{
	t_data	data;
	char	*prompt;

	(void)data;
	prompt = readline(NULL);
	// printf("%s\n", line);
	free(prompt);
	return (0);
}
