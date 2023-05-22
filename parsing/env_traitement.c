/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_traitement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:50:04 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 12:59:52 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	udr_eprevious_command_status(t_command *command)
{
	command->i++;
	return (1);
}

int	eprevious_command_status(t_command *command, int sortie, int line)
{
	char	*value;
	int		ii;

	(void)line;
	value = NULL;
	ii = command->i;
	if (sortie >= 2 && (ii != ft_strlen(command->cmd)))
		ii = command->i + 1;
	if (command->cmd[ii] && (ii < (int)ft_strlen(command->cmd))
		&& command->cmd[ii] == '$' && command->cmd[ii + 1] == '?')
	{
		if (ii == 0 || (ii > 0 && command->cmd[ii - 1] != '$'))
		{
			value = ft_itoa(g_exit_status);
			if (sortie == 0)
				command->cmd_c = realoc_env(command, value, command->cmd_c);
			if (sortie == 1)
				command->args[line] = realoc_env(command, value,
						command->args[line]);
			if (value)
				free(value);
			return (udr_eprevious_command_status(command));
		}
	}
	return (0);
}

int	help_check_env(t_command *command, int *ret, int no_q, int choice)
{
	if (choice == 1)
		free(command->varenv_content);
	if (choice == 2)
	{
		command->varenv_content = gett_env(command->varenv_name, command);
		free(command->varenv_name);
		command->varenv_name = NULL;
		if (no_q == 1 && command->varenv_content)
			command->varenv_content = space_gestion(command->varenv_content,
					command->cmd, command->i);
		*ret = udr_env(command, command->varenv_content);
	}
	if (choice == 3)
	{
		if (command->varenv_content)
			free(command->varenv_content);
		return (*ret);
	}
	if (choice == 4)
	{
		free(command->varenv_content);
		command->varenv_content = NULL;
		command->i--;
	}
	return (0);
}

int	help_check_env0(t_command *command)
{
	int	size;

	size = (int)ft_strlen(command->cmd) + 1;
	command->varenv_content = NULL;
	command->varenv_name = NULL;
	command->varenv_name = malloc(sizeof(char) * ft_strlen(command->cmd) + 1);
	command->redir_size_cmd = size;
	return (0);
}

int	check_env(t_command *command, int line, int i, int no_q)
{
	int	ret;

	ret = 0;
	if (case_check_dolls(command, line, i) != 0)
		return (1);
	ret = eprevious_command_status(command, line, i);
	if (ret == 1)
		return (1);
	help_check_env0(command);
	if (!(command->varenv_name))
		return (-1);
	ret = gett_name_varenv(command, &command->varenv_name);
	if (ret != 1)
		return (help_check_env(command, &ret, no_q, 1));
	help_check_env(command, &ret, no_q, 2);
	if (ret != 0 && !command->varenv_content)
		return (help_check_env(command, &ret, no_q, 3));
	if (line == 0)
		command->cmd_c = realoc_env(command,
				command->varenv_content, command->cmd_c);
	if (line == 1)
		command->args[i] = realoc_env(command,
				command->varenv_content, command->args[i]);
	help_check_env(command, &ret, no_q, 4);
	return (1);
}
