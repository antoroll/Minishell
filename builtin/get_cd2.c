/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:10:56 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 15:11:35 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	mini_norme(t_data *data)
{
	free(data->pathing);
	data->tmp = chdir(data->path2);
}

char	**get_env_refresh(t_data *data, char **envp, char *oldpwd, char *pwd)
{
	char	*oldpwd2;
	char	*pwd2;
	int		i;

	oldpwd2 = NULL;
	pwd2 = NULL;
	i = 0;
	while (envp[i])
		i++;
	data->tab = malloc(sizeof(char *) * (i + 1));
	if (!data->tab)
		return (NULL);
	under_env_refresh(data, envp, pwd, oldpwd);
	data->tab[i] = 0;
	return (data->tab);
}

void	under_env_refresh(t_data *data, char **envp, char *pwd, char *oldpwd)
{
	int		i;
	char	*oldpwd2;
	char	*pwd2;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			oldpwd2 = ft_strjoin("OLDPWD=", oldpwd);
			data->tab[i] = ft_strcpy(data->tab[i], oldpwd2);
		}
		else if (ft_strncmp(envp[i], "PWD=", ft_strlen("PWD=")) == 0)
		{
			pwd2 = ft_strjoin("PWD=", pwd);
			data->tab[i] = ft_strcpy(data->tab[i], pwd2);
		}
		else
			data->tab[i] = ft_strcpy(data->tab[i], envp[i]);
	}
	free_tab(envp);
	if (oldpwd2)
		free(oldpwd2);
	if (pwd2)
		free(pwd2);
}
