/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:44:19 by florianma         #+#    #+#             */
/*   Updated: 2021/12/22 19:09:09 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	parser(char *pipe, t_command *command, t_info *info, int ii)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!(pipe))
		return (-1);
	while (command->cmd[i] && command->cmd[i] == ' ')
		i++;
	if (cmd_extract(command, &i, &j) == -1)
		return (-1);
	command->index_struct = ii;
	command->i = i;
	command->j = j;
	if (get_option(command, 1, 0, 0) == -1)
		return (-1);
	if (command->flag_here_doc == 1)
		info->last_here_doc = ii;
	return (0);
}
