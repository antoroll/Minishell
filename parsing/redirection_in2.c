/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:40:22 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:40:33 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	file_creation0(t_command *command)
{
	command->redir_in = open(command->redir_charin, O_RDONLY);
	if (!command->redir_charin[0] || command->redir_in == -1)
	{
		ft_putstr_fd(command->redir_charin, 1);
		g_exit_status = -1;
		command->stop = 1;
		return (-1);
	}
	return (0);
}

int	simpleq_redirection0(t_command *command, char *str)
{
	if ((command->cmd[command->i + 1] == '\''
			&& command->cmd[command->i + 2] == ' ') && !str)
	{
		str[command->ir] = ' ';
		str[command->ir + 1] = 0;
		command->i = command->i + 2;
		return (-1);
	}
	while (command->cmd[command->i] && command->cmd[++command->i] != '\'')
		str[++command->ir] = command->cmd[command->i];
	str[command->ir + 1] = 0;
	command->i++;
	if (command->cmd[command->i] != ' ')
		return (1);
	return (-1);
}
