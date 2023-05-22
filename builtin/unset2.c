/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:14:02 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 15:15:13 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	**under_rm_equals(char **arr, int *count, char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j] != '=' && arr[i][j])
			j++;
		count[i] = j;
	}
	i = -1;
	while (arr[++i])
	{
		tab[i] = malloc(sizeof(char) * (count[i] + 1));
		j = -1;
		while (arr[i][++j] != '=' && arr[i][j])
			tab[i][j] = arr[i][j];
		tab[i][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}

char	**get_env_unset(char **envp, char **args, char **arr)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 3));
	if (!tab)
		return (NULL);
	error_unset(args);
	under_get_env_unset(envp, args, arr);
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (envp[i][0] != ' ')
		{
			tab[j] = ft_strcpy(tab[i], envp[i]);
			j++;
		}
	}
	tab[j] = 0;
	free_tab(arr);
	return (tab);
}

void	error_unset(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		if (args[i][0] == '\0')
			write(2, "unset: `': not a valid identifier\n", 34);
}

void	under_get_env_unset(char **envp, char **args, char **arr)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (envp[++i])
	{
		count = 0;
		while (envp[i][count] != '=')
			count++;
		j = -1;
		while (args[++j])
		{
			if (ft_strcmp(arr[i], args[j]) == 0)
				envp[i][0] = ' ';
		}
	}
}
