/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:19:28 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 13:25:26 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	under_get_option2(t_command *command, int *line, int *line_tmp)
{
	command->arg = load_args(command, *line, 0);
	command->max_echo = *line;
	if (command->stop == 1)
		return (under_get_option(command, line, line_tmp, 2));
	if (last_check(command, command->arg, *line) == 1)
		command->arg = load_args(command, ++(*line), 0);
	if (under_get_option(command, line, line_tmp, 3) == -1)
		return (-1);
	return (0);
}

int	init_get_option(t_command *command, int *line, int *line_tmp, int *assist)
{
	int	i;

	i = 0;
	if (command->args)
	{
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
		command->args = NULL;
	}
	command->args = (char **) malloc(sizeof(char *) * 1);
	if (command->args == NULL)
		return (-1);
	*line = 1;
	*line_tmp = 0;
	*assist = 0;
	if (!command->cmd_c)
		return (-1);
	command->args[0] = ft_strdup(command->cmd_c);
	free(command->cmd_c);
	command->arg = NULL;
	return (0);
}

int	ret_get_option(t_command *command, int line)
{
	command->args[line] = NULL;
	return (0);
}

int	get_option(t_command *command, int line, int line_tmp, int assist)
{
	char	**add_new;
	int		i;

	i = 0;
	add_new = NULL;
	if (init_get_option(command, &line, &line_tmp, &assist) == -1)
		return (-1);
	while (command->i)
	{
		add_new = command->args;
		if (under_get_option(command, &line, &line_tmp, 1) == -1)
			return (-1);
		assist = line_tmp;
		while (assist)
		{
			command->args[assist - 1] = ft_strdup(add_new[assist - 1]);
			if (add_new[assist - 1])
				free(add_new[assist - 1]);
			assist--;
		}
		free(add_new);
		if (under_get_option2(command, &line, &line_tmp) == (-1))
			break ;
	}
	return (ret_get_option(command, line));
}
