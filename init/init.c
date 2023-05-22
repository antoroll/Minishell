/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:51:42 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 19:42:15 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	check_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
	{
		if (data->cmd[i] == '|')
			return (1);
	}
	return (0);
}

void	init_builtin(t_builtin *builtin)
{
	builtin[0].cmd = "echo";
	builtin[0].func = echo_command;
	builtin[1].cmd = "cd";
	builtin[1].func = get_cd;
	builtin[2].cmd = "pwd";
	builtin[2].func = display_pwd;
	builtin[3].cmd = "export";
	builtin[3].func = ft_export;
	builtin[4].cmd = "unset";
	builtin[4].func = ft_unset;
	builtin[5].cmd = "env";
	builtin[5].func = ft_env;
	builtin[6].cmd = "exit";
	builtin[6].func = exit_prompt;
	builtin[7].cmd = NULL;
	builtin[7].func = NULL;
}

void	init_vars(t_data *data, t_info *info)
{
	data->path = NULL;
	data->pwd = NULL;
	data->cmd = NULL;
	data->env_refresh = NULL;
	data->env_doublon = NULL;
	data->unset_doublon = NULL;
	data->check = 0;
	data->tab = NULL;
	data->flag = 0;
	data->ret = 0;
	data->arr = NULL;
	data->count = 0;
	data->tmp = 0;
	data->path_cd = NULL;
	data->pathing = NULL;
	data->path2 = NULL;
	data->line = NULL;
	data->i = -1;
	info->i = 0;
	info->final_path = NULL;
	info->half_path = NULL;
	info->cmd_bis = NULL;
}
