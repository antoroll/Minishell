/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:22:59 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 18:54:05 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	display_pwd(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes)
{
	char	*arr;

	(void) data;
	(void) info;
	(void) cmd;
	(void) pipes;
	g_exit_status = 0;
	arr = getcwd(NULL, 0);
	write(1, arr, ft_strlen(arr));
	write(1, "\n", 1);
	g_exit_status = 0;
	if (info->nbr_pipe > 1)
	{
		free(info->cmd);
		free_midway(cmd);
		free_tab(data->env);
		free_all(cmd, info);
		free(cmd->builtin);
		rl_clear_history();
		free(arr);
		exit(g_exit_status);
	}
	free(arr);
	return (g_exit_status);
}
