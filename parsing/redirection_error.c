/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:41:16 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	doubleq_redirection2(t_command *command, char *str, int sortie)
{
	(void)sortie;
	if ((command->cmd[command->i + 1]
			&& command->cmd[command->i + 1] == '"'
			&& command->cmd[command->i + 2] == ' ') && !str)
	{
		str[command->ir] = ' ';
		str[command->ir + 1] = 0;
		command->i = command->i + 2;
		return (-1);
	}
	if (help_dr2(command, str, 0) != 0
		&& (command->i == (int)ft_strlen(command->cmd) - 1))
		return (-1);
	str[command->ir + 1] = 0;
	command->i++;
	if (command->cmd[command->i] != ' ')
		return (1);
	return (-1);
}

int	redirection_q2(t_command *command, int j, char *file)
{
	(void)j;
	if (command->cmd[command->i] == '$')
		redirection_env(command, 2, 1);
	while (command->cmd[command->i] == '\'' || command->cmd[command->i] == '"')
	{
		while (command->cmd[command->i] == '"')
		{
			if ((doubleq_redirection2(command, file, 2)) == -1)
			{
				if (create_file2(command) == -1)
					return (-1);
				return (4);
			}
		}
		while (command->cmd[command->i] == '\'')
		{
			if ((simpleq_redirection2(command, file)) == -1)
			{
				if (create_file2(command) == -1)
					return (-1);
				return (4);
			}
		}
	}
	return (0);
}

int	help_redirection_out_error0(t_command *command)
{
	if (command->redir_charerr)
		free(command->redir_charerr);
	command->redir_charerr = malloc(sizeof(char) * ft_strlen(command->cmd) + 1);
	if (!command->redir_charerr)
		return (-1);
	while (command->cmd[command->i] && command->cmd[command->i] == ' ')
		command->i++;
	return (0);
}

int	help_redirection_out_error1(t_command *command, int *i, int *j, int choice)
{
	if (choice == 1)
	{
		*i = redirection_q2(command, *j, command->redir_charerr);
		if (command->i == (int)ft_strlen(command->cmd))
			return (-1);
	}	
	if (choice == 2)
	{
		if ((command->cmd[command->i] == '<'
				|| command->cmd[command->i] == '>'))
		{
			command->i--;
			return (-1);
		}
		command->redir_charerr[++command->ir] = command->cmd[command->i];
		command->i++;
		return (0);
	}
	return (0);
}

int	redirection_out_error(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	if (help_redirection_out_error0(command) == (-1))
		return (-1);
	while (command->cmd[command->i] && command->cmd[command->i] != ' ')
	{
		if (help_redirection_out_error1(command, &i, &j, 1) == (-1))
			break ;
		i = redirection_q2(command, j, command->redir_charerr);
		if (command->i == (int)ft_strlen(command->cmd))
			break ;
		if (i != 0)
			return (i);
		if (help_redirection_out_error1(command, &i, &j, 2) == (-1))
			break ;
	}
	command->redir_charerr[(command->ir) + 1] = 0;
	if (create_file2(command) == -1)
		return (-1);
	return (1);
}
