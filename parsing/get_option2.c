/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:35:59 by arolland          #+#    #+#             */
/*   Updated: 2021/12/27 16:02:06 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	simple_quote_args(t_command *command, int line)
{
	if (command->cmd[command->i + 1] == '\''
		&& (command->cmd[command->i + 2] == ' '
			|| command->cmd[command->i + 2] == '\0'))
		command->args[line][++(command->j)] = '\0';
	while (command->cmd[command->i] && command->cmd[++(command->i)] != '\'')
		command->args[line][++(command->j)] = command->cmd[command->i];
	(command->i)++;
	return (0);
}

int	double_quote_args(t_command *command, int line, int ret)
{
	while (command->cmd[command->i] && (command->cmd[++command->i] != '"' ))
	{
		ret = 0;
		if (command->cmd[command->i] == '$')
		{
			ret = check_env(command, 1, line, 0);
		}
		if (ret != (1))
			command->args[line][++command->j] = command->cmd[command->i];
	}
	if (command->cmd[command->i] == '"'
		&& (command->cmd[command->i + 1] == ' '
			|| command->cmd[command->i + 1] == '\0') && !command->args[line][0])
		command->args[line][0] = '\0';
	(command->i)++;
	if (command->args[line][0] == '\0'
		&& (command->cmd[command->i] == ' '
			|| command->cmd[command->i]) == '\0')
		return (1);
	return (0);
}

int	cleaning_quoting_args(t_command *command, int line, int ret)
{
	if (command->i > 0 && command->cmd[command->i]
		&& command->i - 1 > 0 && command->cmd[command->i - 1]
		&& command->i + 1 > 0 && command->cmd[command->i + 1])
	{
		if (command->cmd[command->i + 1] == '>'
			&& command->cmd[command->i - 1] == ' '
			&& (command->cmd[command->i] == '1'
				|| command->cmd[command->i] == '2'))
			command->i++;
	}
	while (command->cmd[command->i] == '\'' || command->cmd[command->i] == '"')
	{
		while (command->cmd[command->i] == '"')
		{
			ret = double_quote_args(command, line, ret);
			if (ret == -1)
				return (-1);
		}
		while (command->cmd[command->i] == '\'')
			ret = simple_quote_args(command, line);
	}
	return (ret);
}

int	env_redirection_args(t_command *command, int line, int ret)
{
	if (command->cmd[command->i] && command->cmd[command->i] == '$')
	{
		ret = check_env(command, 1, line, 1);
	}
	if (command->cmd[command->i] == '>' || command->cmd[command->i] == '<')
	{
		ret = redirection_args(command);
	}
	return (ret);
}

int	under_load_args(t_command *command, int *line, int *ret, int choice)
{
	if (choice == 1)
	{
		*ret = 0;
		*ret = cleaning_quoting_args(command, *line, *ret);
		*ret = env_redirection_args(command, *line, *ret);
		return (0);
	}
	if (choice == 2)
	{
		if (command->cmd[command->i]
			&& (command->cmd[command->i] != ' ' )
			&& *ret != 1 && *ret != 4
			&& (command->cmd[command->i] != '$'))
		{
			return (1);
		}
	}
	return (0);
}
