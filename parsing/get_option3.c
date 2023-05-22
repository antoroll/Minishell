/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:36:40 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:36:52 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	help_load_args(t_command *command, int *ret, int line, int choice)
{
	if (choice == 1)
	{
		*ret = 0;
		command->j = (-1);
		command->args[line] = NULL;
		command->args[line] = malloc(sizeof(char)
				* ((ft_strlen(command->cmd) + 1)));
		return (0);
	}
	if (choice == 2)
	{
		if ((command->cmd[command->i] == ' ' && (command->args[line][0]
				|| (!command->args[line][0]
				&& (command->cmd [command->i - 1] == '"'
					|| command->cmd[command->i - 1] == '\'')
				&& (command->cmd[command->i - 2] == '"'
					|| command->cmd [command->i - 2] == '\''
					|| *ret == 1)))))
			return (1);
	}
	return (0);
}

char	*load_args(t_command *command, int line, int ret)
{
	help_load_args(command, &ret, line, 1);
	if (!(command->args[line]))
		return (NULL);
	command->args[line][0] = 0;
	while (command->cmd[(command->i)] && command->cmd[(command->i)] == ' ')
		command->i++;
	command->i--;
	while (command->cmd[(command->i)] && (command->cmd[(++command->i)] != ' ' ))
	{
		ret = 0;
		under_load_args(command, &line, &ret, 1);
		if (help_load_args(command, &ret, line, 2) == 1)
			break ;
		if (under_load_args(command, &line, &ret, 2) == 1)
			command->args[line][++(command->j)] = command->cmd[command->i];
	}	
	command->args[line][(command->j) + 1] = 0;
	return (command->args[line]);
}

int	last_check(t_command *command, char *arg, int line)
{
	int	ii;

	(void)line;
	ii = (command->i) - 1;
	if (!arg[0] && ii >= 2 && (command->cmd[command->i - 1] == '"'
			|| command->cmd[(command->i) - 1] == '\'')
		&& (command->cmd[(command->i) - 2] == '"'
			|| command->cmd[command->i - 2] == '\'')
		&& !command->cmd[command->i])
	{
		while (ii >= 2 && (command->cmd[ii] == '"' || command->cmd[ii] == '\''))
		{
			if (command->cmd[ii - 1] != command->cmd[ii])
			{
				return (0);
			}
			ii = ii - 2;
		}
		if (command->cmd[ii] != ' ')
			return (0);
		return (1);
	}
	return (0);
}

int	help_udr_get_option(t_command *command)
{
	free(command->arg);
	return (-1);
}

int	under_get_option(t_command *command, int *line, int *line_tmp, int choice)
{
	int	i;

	i = 0;
	if (choice == 1)
	{
		command->args = malloc(sizeof(char *) * (*line + 2));
		if (!command->args)
			return (-1);
		*line_tmp = *line;
	}
	if (choice == 2)
	{
		command->args[*line + 1] = NULL;
		return (-1);
	}
	if (choice == 3)
	{
		if (!command->arg || ((!command->arg[0]) && !command->cmd[command->i]))
			return (help_udr_get_option(command));
		(*line)++;
		return (0);
	}
	return (0);
}
