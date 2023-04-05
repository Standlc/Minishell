/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:35:37 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:36:59 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	has_dot_slash_prefix(char *str)
{
	skip_spaces(&str);
	return (!ft_strncmp(str, "./", 2));
}

int	has_slash_prefix(char *str)
{
	skip_spaces(&str);
	return (*str == '.' || *str == '/');
}
