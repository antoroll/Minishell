/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:47:02 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 14:08:30 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	display_env_variable(char *av, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], av) == 0)
		{
			ft_putstr_fd(env[i], 1);
		}
		i++;
	}
}

void	udr_echo_command(t_command *command)
{
	int	i;
	int	go;

	i = 1;
	go = 0;
	while (i < command->max_echo)
	{
		while (command->args[i] && ft_strcmp(command->args[i], "-n") == 0)
		{
			go = 1;
			i++;
		}
		while (command->args[i])
		{
			ft_putstr_fd(command->args[i], 1);
			if (command->args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (go == 0)
		ft_putstr_fd("\n", 1);
}

void	udr_echo_command2(t_command *command, t_info *info, t_data *data)
{
	free(info->cmd);
	free_midway(command);
	free_tab(data->env);
	free_all(command, info);
	free(command->builtin);
	rl_clear_history();
	exit(g_exit_status);
}

int	echo_command(t_data *data, t_info *info, t_command *command, t_pipes *pipes)
{
	(void) data;
	(void)pipes;
	g_exit_status = 0;
	if (info->nbr_pipe == 1)
	{
		if ((only_c(&command->args[1][0], ' ') && command->max_echo == 1))
		{
			ft_putstr_fd("\n", 1);
			return (1);
		}
		udr_echo_command(command);
	}
	if (info->nbr_pipe > 1)
	{
		if ((only_c(&command[pipes->i].args[1][0], ' '))
			&& command->max_echo == 1)
			return (udr_final());
		udr_echo_command(command);
	}
	if (info->nbr_pipe > 1)
		udr_echo_command2(command, info, data);
	else
		return (g_exit_status);
	return (g_exit_status);
}

int	udr_final(void)
{
	ft_putstr_fd("\n", 1);
	return (1);
}
