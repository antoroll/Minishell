/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:43:51 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 19:00:11 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	ft_unset(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes)
{
	char	**arr;
	int		ret;

	arr = NULL;
	ret = 0;
	arr = remove_equals(data->env);
	if (info->nbr_pipe > 1)
	{
		ret = display_errors(cmd[pipes->i].args);
		data->unset_doublon = get_env_unset(data->env, cmd[pipes->i].args, arr);
		if (data->env)
			free_tab(data->env);
		data->env = get_env(data->unset_doublon);
		free_tab(data->unset_doublon);
		free_unset(cmd, info);
		free_tab(data->env);
		exit(g_exit_status);
	}
	under_unset(info, data, cmd, arr);
	return (g_exit_status);
}

void	under_unset(t_info *info, t_data *data, t_command *cmd, char **arr)
{
	int	ret;

	ret = 0;
	if (info->nbr_pipe == 1)
	{
		ret = display_errors(cmd[0].args);
		data->unset_doublon = get_env_unset(data->env, cmd[0].args, arr);
		if (data->env)
			free_tab(data->env);
		data->env = get_env(data->unset_doublon);
		free_tab(data->unset_doublon);
	}
}

int	display_errors(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			return (g_exit_status);
		}
	}
	g_exit_status = 0;
	return (g_exit_status);
}

char	**remove_equals(char **arr)
{
	char	**tab;
	int		i;
	int		*count;

	i = 0;
	while (arr[i])
		i++;
	count = malloc(sizeof(int) * i);
	if (!count)
		return (NULL);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	tab = under_rm_equals(arr, count, tab);
	free(count);
	return (tab);
}

void	free_unset(t_command *cmd, t_info *info)
{
	free(info->cmd);
	free_midway(cmd);
	free_all(cmd, info);
	free(cmd->builtin);
	rl_clear_history();
}
