/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:50:04 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 12:37:50 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

size_t	look_for_index(char *str, char c)
{
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return ((size_t)(ch - str));
}

int	help_gett_env(char *env, int *i, int *size, int choice)
{
	if (choice == 1)
	{
		if ((!env) || (env[0] == 0))
			return (-1);
		*i = 0;
		*size = (int)ft_strlen(env);
		return (0);
	}
	return (0);
}

int	help_gett_env2(int *i_str, int *i, t_command *command)
{
	if (*i_str == (-1))
		*i_str = (int)ft_strlen(command->env[*i]);
	return (0);
}

char	*help_gett_env3(char *env, int *i, t_command *command)
{
	return (ft_substr(command->env[*i],
			(int)ft_strlen(env) + 1, (int)ft_strlen(command->env[*i])));
}

char	*gett_env(char *env, t_command *command)
{
	int		size;
	int		i;
	char	*duplicate;
	int		i_str;

	if (help_gett_env(env, &i, &size, 1) == -1)
		return (NULL);
	duplicate = NULL;
	while (command->env[i])
	{
		i_str = look_for_index(command->env[i], '=');
		help_gett_env2(&i_str, &i, command);
		duplicate = ft_substr(command->env[i], 0, i_str);
		if (duplicate)
		{
			if (ft_strequ(duplicate, env))
			{
				free(duplicate);
				return (help_gett_env3(env, &i, command));
			}
			free(duplicate);
		}
		i++;
	}
	return (NULL);
}
