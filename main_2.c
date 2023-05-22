/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:15:42 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 23:16:32 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	udr_through_pipes(t_data *d, t_command *cmd, t_info *info, t_builtin *b)
{
	d->i--;
	while (d->i >= 0)
	{
		free_midway(&cmd[d->i]);
		d->i--;
	}
	free(info->cmd);
	free(cmd);
	free(b);
}

int	check_pipe(t_info *info, t_data *data)
{
	info->error_quote = 0;
	info->input = data->line;
	info->cmd = NULL;
	ft_split_mini(data->line, '|', info);
	if (info->error_quote == -1)
		return (-1);
	else
		through_pipe(info, data, data->env);
	return (0);
}

int	msg_error(char c, int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
	}
	if (choice == 2)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline", 2);
		ft_putchar_fd('\n', 2);
	}
	return (0);
}

int	check_white_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!(line[i] == ' ' || line[i] == '\n' || line[i] == '\t'
				|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r'))
			return (-1);
	}
	return (0);
}
