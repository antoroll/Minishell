/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:41:51 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:42:02 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	create_file2(t_command *command)
{
	if (!command->redir_charerr[0])
	{
		g_exit_status = -1;
		command->stop = 1;
		return (-1);
	}
	if (command->redir_end == 1)
		command->redir_out = open(command->redir_charerr, O_CREAT
				| O_RDWR | O_APPEND, 0644);
	else
		command->redir_out = open(command->redir_charerr, O_CREAT
				| O_RDWR | O_TRUNC, 0644);
	if (command->redir_out == -1)
	{
		return (-1);
	}
	return (0);
}

int	simpleq_redirection2(t_command *command, char *str)
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

int	help_dr2(t_command *command, char *str, int j)
{
	while (command->cmd[command->i] && command->cmd[++command->i] != '"')
	{
		j = 0;
		if (command->cmd[command->i] == '$' && (command->i == 0))
		{
			redirection_env(command, 2, 0);
			if (j == -2)
			{
				command->i--;
				j = 1;
			}
			if (command->cmd[command->i] == '"')
				break ;
		}
		if (j != 1)
			str[++command->ir] = command->cmd[command->i];
	}
	return (j);
}
