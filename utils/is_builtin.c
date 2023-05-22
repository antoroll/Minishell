/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:17:40 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 20:17:52 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	is_builtin(char *line, t_builtin *builtin)
{
	int	i;

	i = 0;
	while (builtin[i].cmd)
	{
		if (ft_strcmp(line, builtin[i].cmd) == 0)
			return (i);
		i++;
	}
	return (-1);
}
