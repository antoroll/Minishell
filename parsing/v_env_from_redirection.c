/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_env_from_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:50:04 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 12:29:34 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	previous_command_status(t_command *command, int sortie, int line)
{
	char	*value;
	int		ii;

	(void) line;
	value = NULL;
	ii = command->i;
	if (sortie >= 2 && (ii != ft_strlen(command->cmd)))
		ii = command->i + 1;
	if (command->cmd[ii] && (ii < (int)ft_strlen(command->cmd))
		&& command->cmd[ii] == '$' && command->cmd[ii + 1] == '?')
	{
		if (ii == 0 || (ii > 0 && command->cmd[ii - 1] != '$'))
		{
			free(command->args[line]);
			value = ft_itoa(g_exit_status);
			h_prev_command_status(command, sortie, value);
			command->i++;
			return (1);
		}
	}
	return (0);
}

int	redirection_env(t_command *command, int sortie, int into_q)
{
	int	ret;
	int	size;

	size = (int)ft_strlen(command->cmd) + 1;
	ret = 0;
	udr_redirection_env(command);
	command->redir_varenv_name = malloc(sizeof(char) * size);
	if (!command->redir_varenv_name)
		return (-1);
	ret = redirection_env_preparation(command, &ret);
	if (ret == 1)
		return (0);
	ret = previous_command_status(command, sortie, 0);
	if (ret == 1)
		return (1);
	get_name_varenv(command, command->redir_varenv_name);
	ret = env_redir_ambig(command, into_q);
	if (ret != 0)
	{
		free(command->redir_varenv_name);
		return (ret);
	}
	return (help_redirection_env(command, sortie, ret));
}
