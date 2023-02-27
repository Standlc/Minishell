/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:52:38 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/27 12:53:10 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	
	prompt = readline(NULL);
	// printf("%s\n", line);
	free(prompt);
	return (0);
}
