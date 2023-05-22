/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_env_from_redirection2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:28:19 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:28:44 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	help_get_name_varenv(int count, t_command *command)
{
	command->redir_varenv_name[count + 1] = '\0';
	return (1);
}

int	get_name_varenv(t_command *command, char *var_name)
{
	int	count;
	int	i;

	i = 1;
	(void)var_name;
	count = -1;
	if (i == 0)
		command->i++;
	if (i == 0 && (command->cmd[command->i] == '\''
			|| command->cmd[command->i] == '"'))
	{
		command->i--;
		return (0);
	}
	while (command->cmd[command->i] && command->cmd[command->i] != ' '
		&& command->cmd[command->i] != '$' && command->cmd[command->i] != '|'
		&& command->cmd[command->i] != '"' && command->cmd[command->i] != '\'')
	{
		if ((command->cmd[command->i] == '\''
				|| command->cmd[command->i] == '"') && i == 0)
			return (0);
		command->redir_varenv_name[++count] = command->cmd[command->i];
		command->i++;
	}
	return (help_get_name_varenv(count, command));
}

int	redirection_env_preparation(t_command *command, int *ret)
{
	command->redir_varenv_name[0] = 0;
	command->i++;
	if (command->cmd[command->i] == '\'' || command->cmd[command->i] == '"')
	{
		free(command->redir_varenv_name);
		*ret = 1;
		return (1);
	}
	return (0);
}

int	help_redirection_env(t_command *command, int sortie, int ret)
{
	if (ret == 1)
		return (1);
	if (sortie == 0)
		command->redir_charin = redirection_realoc(command,
				command->redir_varenv_content, command->redir_charin);
	if (sortie == 1)
	{
		command->redir_charout = redirection_realoc(command,
				command->redir_varenv_content, command->redir_charout);
	}
	if (sortie == 2)
		command->redir_charerr = redirection_realoc(command,
				command->redir_varenv_content, command->redir_charerr);
	free(command->redir_varenv_content);
	command->i--;
	return (1);
}

void	udr_redirection_env(t_command *command)
{
	command->redirection_error = 1;
	command->redir_varenv_content = NULL;
	command->redir_varenv_name = NULL;
}
