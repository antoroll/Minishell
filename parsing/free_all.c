/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:19:28 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 11:57:11 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	free_midway(t_command *command)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (command->cmd)
		free(command->cmd);
	if (command->args)
	{
		while (command->args[i])
		{
			free(command->args[i]);
			command->args[i] = NULL;
			i++;
		}
		free(command->args);
		command->args = NULL;
	}
	if (command->redir_charout)
		free(command->redir_charout);
	if (command->redir_charin)
		free(command->redir_charin);
}

void	free_info(t_info *info)
{
	int		i;

	i = 0;
	if (info->cmd)
	{
		while (info->cmd[i])
		{
			free(info->cmd[i]);
			info->cmd[i] = NULL;
			i++;
		}
		free(info->cmd);
		info->cmd = NULL;
	}
}
