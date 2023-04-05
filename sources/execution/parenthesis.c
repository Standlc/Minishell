/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:19:04 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:19:04 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parenthesis(t_pipeline *pipelines, int *index)
{
	int	number;
	int	i;

	i = 0;
	number = 1;
	while (number != 0)
	{
		number += pipelines[i].parenthesis;
		i++;
	}
	i++;
	*index = i;
}
