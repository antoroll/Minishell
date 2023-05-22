/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:58:19 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 15:31:09 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	ft_exit_bonus(t_command *cmd, char *str, int file, t_info *info)
{
	if (ft_strncmp(str, "infile", 6) == 0)
	{
		if (file == -1)
		{
			ft_putstr_fd("Invalid infile.\n", 2);
			free_all(cmd, info);
			exit(EXIT_FAILURE);
		}
	}
	if (ft_strncmp(str, "outfile", 7) == 0)
	{
		if (file == -1)
		{
			ft_putstr_fd("Invalid outfile\n", 2);
			free_all(cmd, info);
			exit(EXIT_FAILURE);
		}
	}
}

void	invalid_command_bonus(t_pipes *pipes, t_command *cmd, t_info *info)
{
	if (info->nbr_pipe > 1)
	{
		if (cmd[pipes->i].args[0][0] == '\0')
			ft_putstr_fd("Command not found : « »\n", 2);
	}
	else if (info->nbr_pipe == 1)
	{
		if (cmd[0].args[0][0] == '\0')
			ft_putstr_fd("Command not found : « »\n", 2);
	}
}

void	error_args(t_command *cmd, t_info *info)
{	
	ft_putstr_fd("Error\nUsage1 : ./pipesx here_doc"
		" LIMITER cmd1 cmd2 outfile\n", 2);
	ft_putstr_fd("Usage2 : ./pipesx infile cmd1 "
		"cmd2... cmd n outfile\nInfile must have READ rights\n", 2);
	free_all(cmd, info);
	exit(EXIT_FAILURE);
}
