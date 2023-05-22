/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:34:06 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	doubleq_redirection1(t_command *command, char *str)
{
	int	i;
	int	j;

	i = 0;
	if ((command->cmd[command->i + 1] && command->cmd[command->i + 1] == '"'
			&& command->cmd[command->i + 2] == ' ') && !str)
	{
		return (help_doublq_redirection1(command, str));
	}
	j = 0;
	while (command->cmd[command->i] && command->cmd[++command->i] != '"')
	{
		j = 0;
		if (command->cmd[command->i] == '$')
		{
			help_doublq_redirection(command, &j);
			if (command->cmd[command->i] == '"')
				break ;
		}
		if (j != 1)
			str[++command->ir] = command->cmd[command->i];
	}
	return (help_double_q_redirection1(command, &j, 2));
}

int	redirection_q1(t_command *command, char *file)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (command->cmd[command->i] == '$')
		redirection_env(command, i, j);
	while (command->cmd[command->i] == '\'' || command->cmd[command->i] == '"')
	{
		while (command->cmd[command->i] == '"')
		{
			if ((doubleq_redirection1(command, file)) == -1)
				if (file_creation1(command) == -1)
					return (-1);
			return (2);
		}
		while (command->cmd[command->i] == '\'')
		{
			if ((simpleq_redirection1(command, file)) == -1)
				if (file_creation1(command) == -1)
					return (-1);
			return (2);
		}
	}
	return (0);
}

int	under_redirection_out(t_command *command, int *i)
{
	*i = redirection_q1(command, command->redir_charout);
	if (command->i == (int)ft_strlen(command->cmd))
		return (-1);
	if (*i != 0)
	{
		return (*i);
	}
	if ((command->cmd[command->i] == '<' || command->cmd[command->i] == '>'))
	{
		command->i--;
		return (-1);
	}
	command->redir_charout[++command->ir] = command->cmd[command->i];
	command->i++;
	return (0);
}

void	help_redirection_out(t_command *command)
{
	if (command->redir_charout)
		free(command->redir_charout);
	command->redir_charout = malloc(sizeof(char) * ft_strlen(command->cmd) + 1);
}

int	redirection_out(t_command *command, int i)
{
	help_redirection_out(command);
	if (!command->redir_charout)
		return (-1);
	while (command->cmd[command->i] && command->cmd[command->i] == ' ')
		command->i++;
	while (command->cmd[command->i] && command->cmd[command->i] != ' ')
	{
		i = redirection_q1(command, command->redir_charout);
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
		command->redir_charout[++command->ir] = command->cmd[command->i];
		command->i++;
	}
	command->redir_charout[command->ir + 1] = '\0';
	if (file_creation1(command) == -1)
		return (-1);
	return (1);
}
