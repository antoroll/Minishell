/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:12:45 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 21:41:58 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	**get_env_doublon(char **envp)
{
	char	**tab;
	int		i;
	int		flag;

	flag = 0;
	tab = NULL;
	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == ' ')
			flag++;
		i++;
	}
	i = i - flag;
	tab = under_env_doublon(tab, i, envp);
	return (tab);
}

char	**under_env_doublon(char **tab, int i, char **envp)
{
	int	j;

	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (envp[i][0] != ' ')
		{
			tab[j] = ft_strrcpy(tab[i], envp[i]);
			if (!tab[j])
				return (ft_free_lol(tab));
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}

char	**check_doublon(char **envp, char **export, t_data *data)
{
	int		i;
	char	**env;

	env = NULL;
	i = 1;
	while (export[i])
		i++;
	data->tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (export[++i])
	{	
		if (export[i][0] == '=' && export[i + 1] == NULL)
		{
			data->check = 1;
			free(data->tab);
			return (envp);
		}
	}
	check_doublon_tab(export, data->flag, data);
	under_check_doublon(export, data, data->flag);
	under_doublon_bis(data, envp);
	free_tab(data->tab);
	env = get_env_doublon(envp);
	return (env);
}

void	check_doublon_tab(char **export, int flag, t_data *data)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = -1;
	while (export[++i])
	{
		if (export[i][0] == '=' && export[i + 1])
		{
			flag = i;
			continue ;
		}
		j = 0;
		while (export[i][j] != '=' && export[i][j])
			j++;
		data->tab[++k] = malloc(sizeof(char) * (j + 1));
	}
}

void	under_check_doublon(char **export, t_data *data, int flag)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (export[++i])
	{
		if (flag == i)
			continue ;
		j = -1;
		while (export[i][++j] != '=' && export[i][j])
		{
			data->tab[k][j] = export[i][j];
		}
		data->tab[k][j] = '\0';
		k++;
	}
	data->tab[k] = 0;
}
