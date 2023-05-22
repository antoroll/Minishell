/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:20:30 by flmastor          #+#    #+#             */
/*   Updated: 2021/12/27 15:20:39 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	udr_mem_allocation(t_info *info, int *guil, int *j)
{
	if (info->line[*j] == '"' && *guil == 1)
		guil = 0;
	else if (info->line[*j] == '"' && *guil == 0)
		*guil = 1;
}

void	mem_allocation_free(t_info *info, int *j)
{
	while (info->line[*j] && info->line[*j] == '|')
	{
		(*j)++;
	}
	*j = (*j) - 1;
}
