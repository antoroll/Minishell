/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:40:14 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	help_dr(t_command *command, char *str)
{
	int	j;

	while (command->cmd[command->i] && command->cmd[++command->i] != '"')
	{
		j = 0;
		if (command->cmd[command->i] == '$' && (command->i == 0))
		{
			redirection_env(command, 0, 0);
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

int	doubleq_redirection0(t_command *command, char *str)
{
	int	i;

	i = 0;
	if ((command->cmd[command->i + 1] && command->cmd[command->i + 1] == '"'
			&& command->cmd[command->i + 2] == ' ') && !str)
	{
		str[command->ir] = ' ';
		str[command->ir + 1] = 0;
		command->i = command->i + 2;
		return (-1);
	}
	if (help_dr(command, str) != 0)
		return (-1);
	str[command->ir + 1] = 0;
	command->i++;
	if (command->cmd[command->i] != ' ')
		return (1);
	return (-1);
}

int	redirection_quoting0(t_command *command, char *file)
{
	int	i;

	i = 0;
	if (command->cmd[command->i] == '$')
		redirection_env(command, i, 1);
	while (command->cmd[command->i] == '\'' || command->cmd[command->i] == '"')
	{
		while (command->cmd[command->i] == '"')
		{
			if ((doubleq_redirection0(command, file)) == -1)
				if (file_creation0(command) == -1)
					return (-1);
			return (1);
		}
		while (command->cmd[command->i] == '\'')
		{
			if ((simpleq_redirection0(command, file)) == -1)
				if (file_creation0(command) == -1)
					return (-1);
			return (1);
		}
	}
	return (0);
}

int	help_redirection_in(t_command *command)
{
	command->i++;
	if (command->redir_charin)
		free(command->redir_charin);
	command->redir_charin = malloc(sizeof(char) * ft_strlen(command->cmd) + 1);
	if (!command->redir_charin)
		return (-1);
	while (command->cmd[command->i] && command->cmd[command->i] == ' ')
		command->i++;
	return (0);
}

int	redirection_in(t_command *command, int i)
{
	if (help_redirection_in(command) == -1)
		return (-1);
	while (command->cmd[command->i] && command->cmd[command->i] != ' ')
	{
		i = redirection_quoting0(command, command->redir_charin);
		if (command->i == (int)ft_strlen(command->cmd))
			break ;
		if (i != 0)
			return (i);
		if ((command->cmd[command->i] == '<'
				|| command->cmd[command->i] == '>'))
		{
			command->i--;
			break ;
		}
		command->redir_charin[++command->ir] = command->cmd[command->i];
		command->i++;
	}
	command->redir_charin[command->ir + 1] = '\0';
	if (file_creation0(command) == -1)
		return (-1);
	return (1);
}
