/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_env_from_redirection3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:28:56 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:29:52 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	display_ambiguous(void)
{
	g_exit_status = (-1);
}

int	udr_env_redir_ambig(t_command *command)
{
	if (command->cmd[command->i] == '"'
		|| command->cmd[command->i] == '\''
		|| command->cmd[command->i] == '|')
		command->i--;
	if (command->cmd[command->i] == ' ')
		return (-2);
	if (command->cmd[command->i] == '$')
	{
		command->i--;
	}
	if (command->redir_varenv_content)
		free(command->redir_varenv_content);
	return (1);
}

void	udr_env_redir_ambig1(t_command *command, int into_q)
{
	if (into_q == 1 && command->redir_varenv_content)
		command->redir_varenv_content = space_gestion(
				command->redir_varenv_content, command->cmd, command->i);
	if (command->redir_varenv_content && into_q == 1
		&& command->cmd[command->i] != '$'
		&& just_spaces(command->redir_varenv_content))
		display_ambiguous();
}

int	env_redir_ambig(t_command *command, int into_q)
{
	int	ret;

	ret = 0;
	command->redir_varenv_content = gett_env(command->redir_varenv_name,
			command);
	udr_env_redir_ambig1(command, into_q);
	if (!command->redir_varenv_content && into_q == 1
		&& command->cmd[command->i] != '$'
		&& spaces_middle(command->redir_varenv_content))
		display_ambiguous();
	if ((!command->redir_varenv_content) && into_q == 1
		&& command->cmd[command->i] != '$')
		display_ambiguous();
	if (command->redir_varenv_content)
	{
		command->no_free = 1;
		free(command->redir_varenv_name);
	}
	if (!command->redir_varenv_content)
	{
		ret = udr_env_redir_ambig(command);
		return (ret);
	}
	return (0);
}

void	h_prev_command_status(t_command *command, int sortie, char *value)
{
	if (sortie == 0)
		command->redir_charin = redirection_realoc(command,
				value, command->redir_charin);
	if (sortie == 1)
		command->redir_charout = redirection_realoc(command,
				value, command->redir_charout);
	if (sortie == 2)
		command->redir_charerr = redirection_realoc(command,
				value, command->redir_charerr);
	if (value)
		free(value);
}
