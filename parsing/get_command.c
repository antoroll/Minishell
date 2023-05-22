/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:53:13 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	double_quote_cmd(t_command *command, int *i, int *j, int error)
{
	command->i = *i;
	command->j = *j;
	while (command->cmd[command->i] && (command->cmd[++command->i] != '"'))
	{
		error = 0;
		if (command->cmd[command->i] == '$')
		{
			error = check_env(command, 0, 0, 0);
		}
		if (error != 1)
		{
			command->cmd_c[++command->j] = command->cmd[command->i];
		}
	}
	*i = command->i;
	*j = command->j;
	if (command->cmd[*i] == '"' && (command->cmd[(*i) + 1] == ' '
			|| command->cmd[(*i) + 1] == '\0') && !command->cmd_c[0])
		command->cmd_c[0] = '\0';
	(*i)++;
	if (command->cmd_c[0] == '\0' && (command->cmd[*i] == ' '
			|| command->cmd[*i] == '\0'))
		return (1);
	return (-2);
}

int	cmd_helper(t_command *command, int *i, int *j, int *error)
{
	*error = -2;
	while (command->cmd[*i] == '\'' || command->cmd[*i] == '"')
	{
		while (command->cmd[*i] == '"')
		{
			*error = double_quote_cmd(command, i, j, *error);
			if (*error == -1)
				break ;
		}
		while (command->cmd[*i] == '\'')
		{
			*error = simple_quote_cmd(command, i, j, *error);
			if (*error == -1)
				break ;
		}
	}
	command->i = *i;
	command->j = *j;
	if (command->cmd[*i] && command->cmd[*i] == '$')
		*error = check_env(command, 0, 0, 1);
	if (command->cmd[*i] == '<' || command->cmd[*i] == '>')
		*error = redirection_cmd(command);
	*i = command->i;
	*j = command->j;
	return (*error);
}

int	udr_cmd_extract1(t_command *command, int *error)
{
	if ((command->cmd[command->i] == ' '
			&& command->cmd[command->i - 1] != '\\')
		&& (command->cmd_c[0] || (!command->cmd_c[0]
				&& (command->cmd[command->i - 1] == '"'
					|| command->cmd[command->i - 1] == '\'')
				&& (command->cmd [command->i - 2] == '"'
					|| command->cmd[command->i - 2] == '\''
					|| *error == 1))))
	{
		return (-1);
	}
	if ((command->cmd[command->i] == ' '
			&& command->cmd[command->i - 1] != '\\')
		&& (command->cmd_c[0] || (!command->cmd_c[0]
				&& (command->cmd[command->i - 1] == '"'
					|| command->cmd[command->i - 1] == '\'')
				&& (command->cmd [command->i - 2] == '"'
					|| command->cmd[command->i - 2] == '\'' || *error == 1))))
	{
		return (-1);
	}
	return (0);
}

int	udr_cmd_extract2(t_command *command, int *error, int *i)
{
	if ((*i) > 1)
		if (!command->cmd_c[0]
			&& (command->cmd[(*i) - 1] == '"') && (*error == 1))
			return (-1);
	if ((*i) > 2)
		if (!command->cmd_c[0] && (command->cmd[(*i) - 1] == '"')
			&& (command->cmd [(*i) - 2] == '"' || *error == 1))
			return (-1);
	if ((*i) > 2)
	{
		if (!command->cmd_c[0] && (command->cmd[(*i) - 1] == '\'')
			&& *error == 1)
			return (-1);
	}
	if ((*i) > 2)
		if (!command->cmd_c[0] && (command->cmd[(*i) - 1] == '\'')
			&& (command->cmd[(*i) - 2] == '\'' || *error == 1))
			return (-1);
	return (0);
}

int	cmd_extract(t_command *command, int *i, int *j)
{
	int	error;

	error = 0;
	while (command->cmd[*i] && command->cmd[*i] != ' ')
	{
		cmd_helper(command, i, j, &error);
		if (udr_cmd_extract1(command, &error) == -1)
			break ;
		if (udr_cmd_extract2(command, &error, i) == -1)
			break ;
		if (*i < (int)ft_strlen(command->cmd)
			&& ((command->cmd[(*i)] == '$' && ((*i) == 0))
				|| (command->cmd[(*i)] != '$' && error == -2)))
			command->cmd_c[++(*j)] = command->cmd[*i];
		if (*i < ft_strlen(command->cmd))
			(*i)++;
	}
	command->cmd_c[(*j) + 1] = '\0';
	return (0);
}
