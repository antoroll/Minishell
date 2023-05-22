/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udr_get_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:52:47 by flmastor          #+#    #+#             */
/*   Updated: 2021/12/23 13:02:32 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	simple_quote_cmd(t_command *command, int *i, int *j, int error)
{
	(void)error;
	if ((command->cmd[*i + 2] == ' ' || command->cmd[*i + 2] == '\0')
		&& command->cmd[*i + 1] == '\'')
		command->cmd_c[++(*j)] = '\0';
	while (command->cmd[*i] && command->cmd[++(*i)] != '\'')
	{
		command->cmd_c[++(*j)] = command->cmd[*i];
	}
	(*i)++;
	return (-2);
}
