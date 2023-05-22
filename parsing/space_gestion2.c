/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_gestion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:33:21 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 13:59:13 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	follow_env(int i, char *cmd_full)
{
	i--;
	while (cmd_full[i] && cmd_full[i] != ' ')
	{
		if (cmd_full[i] == '$')
			return (1);
		i--;
	}
	return (0);
}

int	add_space_before_condition(char *cmd_full, int i)
{
	if (follow_env(i, cmd_full)
		|| cmd_full[i - 1] == '"'
		|| cmd_full [i - 1] == '\'')
		return (1);
	return (0);
}

int	add_space_before_util(char *cmd_full, int i, char *tmp)
{
	if (cmd_full[i + 1] == ' ' && just_spaces(tmp))
		return (-1);
	while (cmd_full[i] && cmd_full[i] != '$')
		i--;
	if (cmd_full[i - 1] == ' ' && just_spaces(tmp))
		return (-1);
	return (i);
}

int	add(char *cmd_full, char *copy, char **new, int i)
{
	int	j;

	j = 0;
	if (i == -1)
	{
		if (copy)
			free(copy);
		return (-1);
	}
	if (add_space_before_condition(cmd_full, i) == 1)
	{
		while (copy[j])
		{
			(*new)[0] = ' ';
			(*new)[j + 1] = copy[j];
			j++;
		}
		(*new)[j + 1] = '\0';
	}
	return (1);
}

int	add_space_before(char *tmp, char *cmd_full, int k, char **new)
{
	int		i;
	char	*copy;

	i = 0;
	copy = NULL;
	copy = ft_strdup(*new);
	k--;
	if (tmp[i] == ' ')
	{
		k = add_space_before_util(cmd_full, k, tmp);
		if (add(cmd_full, copy, new, k) == -1)
			return (-1);
	}
	if (copy)
		free(copy);
	return (1);
}
