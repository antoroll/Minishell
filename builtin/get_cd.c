/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:35:34 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 18:56:31 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*get_user_var(t_data *data)
{
	int		i;
	int		j;
	char	*user;

	i = -1;
	user = NULL;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
		{
			user = malloc(sizeof(char) * ft_strlen(data->env[i] + 1));
			j = -1;
			while (data->env[i][++j + 5])
				user[j] = data->env[i][j + 5];
			user[j] = '\0';
		}
	}
	return (user);
}

int	get_cd(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes)
{
	char	*oldpwd;
	char	*pwd;

	(void) pipes;
	g_exit_status = 0;
	oldpwd = getcwd(NULL, 0);
	data->tmp = 0;
	data->count = 0;
	under_get_cd(cmd, data, info);
	mini_get_cd(data);
	pwd = getcwd(NULL, 0);
	data->env_refresh = get_env_refresh(data, data->env, oldpwd, pwd);
	data->env = get_env(data->env_refresh);
	free(pwd);
	free(oldpwd);
	if (info->nbr_pipe > 1)
	{
		free_tab(data->env);
		free_export(data, cmd, info);
		exit(g_exit_status);
	}
	free_tab(data->env_refresh);
	return (g_exit_status);
}

void	mini_get_cd(t_data *data)
{
	if (data->count > 2)
	{
		g_exit_status = 1;
		ft_putstr_fd("cd: too many arguments\n", 2);
	}
	if (data->path_cd)
		free(data->path_cd);
	if (data->path2)
		free(data->path2);
}

void	under_get_cd(t_command *cmd, t_data *data, t_info *info)
{
	while (cmd[0].args[data->count])
		data->count++;
	if (info->nbr_pipe == 1 && data->count <= 2)
	{
		if (cmd[0].args[1] == NULL)
		{
			data->path_cd = get_user_var(data);
			data->tmp = chdir(data->path_cd);
		}
		else if (cmd[0].args[1][0] == '~'
			|| ft_strcmp(cmd[0].args[1], "-") == 0
			|| ft_strcmp(cmd[0].args[1], "--") == 0)
			udr_get_cd(cmd, data, info);
		else
			data->tmp = chdir(cmd[0].args[1]);
		if (data->tmp < 0)
		{
			g_exit_status = 1;
			perror("cd");
		}
	}
}

void	udr_get_cd(t_command *cmd, t_data *data, t_info *info)
{
	int	i;
	int	ret;

	{
		if (ft_strcmp(cmd[0].args[1], "~") == 0
			|| ft_strcmp(cmd[0].args[1], "-") == 0
			|| ft_strcmp(cmd[0].args[1], "--") == 0)
		{
			data->path_cd = get_user_var(data);
			data->tmp = chdir(data->path_cd);
		}
		if (ft_strcmp(cmd[0].args[1], "-") == 0)
			ret = display_pwd(data, info, cmd, cmd->pipes);
		if (ft_strncmp(cmd[0].args[1], "/", 1))
		{
			data->pathing = malloc(sizeof(char) * ft_strlen(cmd[0].args[1]));
			data->path_cd = get_user_var(data);
			i = -1;
			while (cmd[0].args[1][++i + 1])
				data->pathing[i] = cmd[0].args[1][i + 1];
			data->pathing[i] = '\0';
			data->path2 = ft_strjoin(data->path_cd, data->pathing);
			mini_norme(data);
		}
	}
}
