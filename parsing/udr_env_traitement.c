/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udr_env_traitement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:59:22 by flmastor          #+#    #+#             */
/*   Updated: 2021/12/23 13:02:26 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*realoc_env(t_command *command, char *content, char *str)
{
	char	*str_n;
	int		j;

	j = -1;
	str_n = NULL;
	str[command->j + 1] = 0;
	str_n = ft_strjoin(str, content);
	if (str)
		free(str);
	command->j = -1;
	str = malloc(sizeof(char) * (ft_strlen(str_n)
				+ ft_strlen(command->cmd) + 1));
	if (!str)
		return (NULL);
	while (str_n[++j])
		str[++command->j] = str_n[j];
	if (str_n)
		free(str_n);
	return (str);
}

int	case_check_dolls(t_command *command, int arg, int line)
{
	int	j;

	j = 0;
	while (command->cmd[command->i] && command->cmd[command->i] == '$'
		&& (command->cmd[command->i + 1] == '\0'
			|| command->cmd[command->i + 1] == '$'
			|| (command->i > 0 && command->cmd[command->i - 1] == '$')))
	{
		if (arg == 0)
			command->cmd_c[++command->j] = command->cmd[command->i];
		if (arg == 1)
			command->args[line][++command->j] = command->cmd[command->i];
		command->i++;
		if (ft_strlen(command->cmd) == 1 && command->cmd[0] == '$')
			return (1);
		j++;
	}
	if (j > 0)
	{
		command->i--;
		return (1);
	}
	return (0);
}

int	udr_env(t_command *command, char *content)
{
	if (!content && (command->cmd[command->i] == '"'
			|| command->cmd[command->i] == '\''
			|| command->cmd[command->i] == '|'))
	{
		command->i--;
	}
	if (!content && command->cmd[command->i] == ' ')
		return (-2);
	if ((!content) && command->cmd[command->i] == '$')
		command->i--;
	if (!content)
		return (1);
	else
		return (0);
}

int	gett_name_varenv(t_command *command, char **var_name)
{
	int		count;
	int		i;

	i = 0;
	count = -1;
	if (i == 0)
		command->i++;
	if (i == 0 && (command->cmd[command->i] == '\''
			|| command->cmd[command->i] == '"'))
	{
		command->i--;
		return (0);
	}
	while (command->cmd[command->i] && command->cmd[command->i] != '$'
		&& command->cmd[command->i] != ' ' && command->cmd[command->i] != '|'
		&& command->cmd[command->i] != '"' && command->cmd[command->i] != '\'')
	{
		if ((command->cmd[command->i] == '\''
				|| command->cmd[command->i] == '"') && i == 0)
			return (0);
		(*var_name)[++count] = command->cmd[command->i];
		command->i++;
	}
	(*var_name)[count + 1] = '\0';
	return (1);
}
