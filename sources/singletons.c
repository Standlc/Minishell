/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:46:40 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:47:16 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc_data	get_heredoc_data(t_heredoc_data *curr)
{
	static t_heredoc_data	data;

	if (curr)
		data = *curr;
	return (data);
}