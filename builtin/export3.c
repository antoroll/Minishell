/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:13:12 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 10:30:11 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	under_doublon_bis(t_data *data, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (data->tab[++i])
	{
		j = -1;
		while (envp[++j])
			if (ft_strncmp(envp[j], data->tab[i], ft_strlen(data->tab[i])) == 0)
				envp[j][0] = ' ';
	}
}

char	**get_env_refresh_export(char **envp, char **export, t_data *data)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	udr_export(export, i, data, envp);
	return (data->tab);
}

void	udr_export(char **export, int i, t_data *data, char **envp)
{
	int	j;

	j = 0;
	while (export[j])
		j++;
	data->tab = malloc(sizeof(char *) * (i + j + 1));
	if (!data->tab)
		return ;
	i = -1;
	while (envp[++i])
		data->tab[i] = ft_strcpy(data->tab[i], envp[i]);
	under_env_refresh_export_suite(export, i, data);
}

void	under_env_refresh_export_suite(char **export, int i, t_data *data)
{
	int	j;

	j = 0;
	while (export[++j])
	{
		if (export[j][0] == '\0' || !ft_isalpha(export[j][0]))
		{
			ft_putstr_fd("export: \'", 2);
			write(2, export[j], ft_strlen(export[j]));
			ft_putstr_fd("\': not a valid identifier\n", 2);
			if (export[j + 1])
				continue ;
			else
				break ;
		}
		if (ft_strchr(export[j], '='))
		{
			data->tab[i] = ft_strcpy(data->tab[i], export[j]);
			i++;
		}
	}
	data->tab[i] = 0;
}

int	display_export(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->env[++i])
	{
		ft_putstr_fd("export ", 1);
		j = -1;
		while (data->env[i][++j])
		{
			if (data->env[i][j] == '=')
			{
				ft_putstr_fd("=\"", 1);
				j++;
			}
			write(1, &data->env[i][j], 1);
		}
		ft_putstr_fd("\"\n", 1);
	}
	g_exit_status = 0;
	return (g_exit_status);
}
