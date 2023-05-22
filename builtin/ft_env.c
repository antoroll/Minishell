/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:44:41 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 18:52:02 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	ft_env(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes)
{
	int	i;

	(void) pipes;
	(void) cmd;
	i = -1;
	while (data->env[++i])
		printf("%s\n", data->env[i]);
	g_exit_status = 0;
	if ((info->nbr_pipe) > 1)
	{
		free_midway(cmd);
		free_tab(data->env);
		free(info->cmd);
		free_all(cmd, info);
		free(cmd->builtin);
		rl_clear_history();
		exit(g_exit_status);
	}
	return (g_exit_status);
}
