/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cmd_option.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 19:10:52 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	under_redirection_cmd(t_command *command, int *error, int choice)
{
	command->redir_end = 0;
	command->i++;
	if (command->cmd[command->i] == '>')
	{
		if (choice == 0)
			command->redir_end = 1;
		else
			command->redir_end = 0;
		command->i++;
	}
	if ((command->redir_end == 0
			&& (command->i == 2 || (command->i > 3
					&& command->cmd[command->i - 2] == '2'
					&& command->cmd[command->i - 3] == ' '))))
		*error = redirection_out_error(command);
	else if (command->redir_end == 1
		&& (command->i == 3 || (command->i > 4
				&& command->cmd[command->i - 3] == '2'
				&& (command->cmd[command->i - 4] == ' '))))
		*error = redirection_out_error(command);
	else
	{
		*error = redirection_out(command, 0);
	}
}

int	redirection_cmd(t_command *command)
{
	int	ret;

	ret = 0;
	command->ir = -1;
	if (command->cmd[command->i] == '<'
		&& command->cmd[command->i + 1] == '<')
	{
		ft_putstr_fd("cmd_option.c ligne 43\n", 1);
	}
	if (command->cmd[command->i] == '<')
		ret = redirection_in(command, 0);
	if (command->cmd[command->i] == '>')
		under_redirection_cmd(command, &ret, 0);
	if (command->i >= (int)ft_strlen(command->cmd))
		return (-3);
	return (ret);
}

int	redirection_her_doc(t_command *command, int *compteur, int *i)
{
	command->flag_here_doc = 1;
	command->i = command->i + 2;
	*compteur = command->i;
	while (command->cmd[command->i] == ' ')
		command->i++;
	*compteur = 0;
	*i = command->i;
	while (command->cmd[*i] && command->cmd[*i] != ' ')
	{
		(*compteur)++;
		(*i)++;
	}
	command->redir_charin = malloc(sizeof(char) * ((*compteur) + 1));
	*compteur = 0;
	while (command->cmd[command->i] && command->cmd[command->i] != ' ')
	{
		command->redir_charin[*compteur] = command->cmd[command->i];
		command->i++;
		(*compteur)++;
	}
	command->redir_charin[*compteur] = '\0';
	here_doc_parse(command);
	return (0);
}

int	redirection_args(t_command *command)
{
	int	ret;
	int	compteur;
	int	i;

	ret = 0;
	compteur = 0;
	i = 0;
	command->ir = -1;
	if (command->cmd[command->i] == '<' && command->cmd[command->i + 1] == '<')
	{
		redirection_her_doc(command, &compteur, &i);
		if (command->i >= (int)ft_strlen(command->cmd))
			return (-3);
	}
	else
	{
		if (command->cmd[command->i] == '<')
			ret = redirection_in(command, 1);
		if (command->cmd[command->i] == '>')
			under_redirection_cmd(command, &ret, 0);
		if (command->i >= (int)ft_strlen(command->cmd))
			return (-3);
	}
	return (ret);
}
