/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:22:10 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 15:23:18 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	here_doc_parse(t_command *cmd)
{
	char	*line;

	line = NULL;
	cmd[cmd->index_struct].file = open("heredoc",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(STDOUT_FILENO, "> ", 2);
	while (get_next_line(0, &line, 1) != 0)
	{
		if (ft_strcmp(line, cmd->redir_charin) == 0)
		{
			free(line);
			close(cmd[cmd->index_struct].file);
			break ;
		}
		write(STDOUT_FILENO, "> ", 2);
		write(cmd[cmd->index_struct].file, line, ft_strlen(line));
		write(cmd[cmd->index_struct].file, "\n", 1);
		free(line);
	}
}

void	first_command(t_command *cmd, t_info *info)
{
	if (cmd->pipes->i == 0)
	{
		if (cmd[cmd->pipes->i].file > 0)
		{
			cmd[cmd->pipes->i].file = open("heredoc", O_RDONLY, 0644);
			dup2(cmd[cmd->pipes->i].file, 0);
			close(cmd[cmd->pipes->i].file);
		}
		if (cmd[cmd->pipes->i].redir_in > 1)
		{
			dup2(cmd[cmd->pipes->i].redir_in, 0);
			close(cmd[cmd->pipes->i].redir_in);
		}
		if (cmd[cmd->pipes->i].redir_out > 1)
		{	
			dup2(cmd[cmd->pipes->i].redir_out, 1);
			close(cmd[cmd->pipes->i].redir_out);
		}
		else if (info->nbr_pipe > 1)
		{
			dup2(cmd->pipes->pipes[cmd->pipes->i + 1][1], 1);
			close(cmd->pipes->pipes[cmd->pipes->i + 1][1]);
		}
	}
}

void	last_command(t_command *cmd, t_info *info)
{
	if ((cmd->pipes->i == info->nbr_pipe - 1) && info->nbr_pipe > 1)
	{
		if (cmd[cmd->pipes->i].file > 0)
		{
			cmd[cmd->pipes->i].file = open("heredoc", O_RDONLY, 0644);
			dup2(cmd[cmd->pipes->i].file, 0);
			close(cmd[cmd->pipes->i].file);
		}
		if (cmd[cmd->pipes->i].redir_in > 1)
		{
			dup2(cmd[cmd->pipes->i].redir_in, 0);
			close(cmd[cmd->pipes->i].redir_in);
		}
		else
		{
			dup2(cmd->pipes->pipes[cmd->pipes->i][0], 0);
			close(cmd->pipes->pipes[cmd->pipes->i][0]);
		}
		if (cmd[cmd->pipes->i].redir_out > 1)
		{
			dup2(cmd[cmd->pipes->i].redir_out, 1);
			close(cmd[cmd->pipes->i].redir_out);
		}
	}
}

void	middle_command(t_command *cmd, t_info *info)
{
	if (cmd->pipes->i != 0 && (cmd->pipes->i != (info->nbr_pipe - 1)))
	{
		if (cmd[cmd->pipes->i].file > 0)
		{
			cmd[cmd->pipes->i].file = open("heredoc", O_RDONLY, 0644);
			dup2(cmd[cmd->pipes->i].file, 0);
			close(cmd[cmd->pipes->i].file);
		}
		if (cmd[cmd->pipes->i].redir_in > 1)
		{
			dup2(cmd[cmd->pipes->i].redir_in, 0);
			close(cmd[cmd->pipes->i].redir_in);
		}
		else
		{
			dup2(cmd->pipes->pipes[cmd->pipes->i][0], 0);
			close(cmd->pipes->pipes[cmd->pipes->i][0]);
		}
		under_middle_command(cmd);
	}
}

void	under_middle_command(t_command *cmd)
{
	if (cmd[cmd->pipes->i].redir_out > 1)
	{
		dup2(cmd[cmd->pipes->i].redir_out, 1);
		close(cmd[cmd->pipes->i].redir_out);
	}
	else
	{
		dup2(cmd->pipes->pipes[cmd->pipes->i + 1][1], 1);
		close(cmd->pipes->pipes[cmd->pipes->i + 1][1]);
	}
}
