/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udr_redirection_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:29:33 by flmastor          #+#    #+#             */
/*   Updated: 2021/12/23 12:30:21 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	help_file_creation(t_command *command)
{
	g_exit_status = -1;
	command->stop = 1;
}

int	file_creation1(t_command *command)
{
	if (!command->redir_charout[0])
	{
		help_file_creation(command);
		return (-1);
	}
	if (command->redir_end == 1)
		command->redir_out = open(command->redir_charout,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		command->redir_out = open(command->redir_charout,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (command->redir_out == -1)
	{
		ft_putstr_fd("minishell", 1);
		if (command->redir_charout)
			ft_putstr_fd(command->redir_charout, 1);
		perror(" ");
		help_file_creation(command);
		return (-1);
	}
	return (0);
}

int	simpleq_redirection1(t_command *command, char *str)
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

int	help_double_q_redirection1(t_command *command, int *j, int choice)
{
	if (choice == 1)
	{
		*j = 0;
		if (command->cmd[command->i] == '$' && (command->i == 0))
		{
			redirection_env(command, 1, 0);
			if (command->cmd[command->i] == '"')
				return (-1);
		}
	}
	if (choice == 2)
	{
		command->i++;
		if (command->cmd[command->i] != ' ')
			return (1);
		return (-1);
	}
	return (0);
}

void	help_doublq_redirection(t_command *command, int *j)
{
	*j = 0;
	if (command->cmd[command->i] == '$')
	{
		*j = redirection_env(command, 1, 0);
		if (*j == -2)
		{
			command->i--;
			*j = 1;
		}
	}
}
