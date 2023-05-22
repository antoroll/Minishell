/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:21:04 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

static void	init_redirection(t_command *command)
{
	command->redir_charout = NULL;
	command->redir_charin = NULL;
	command->redir_charerr = NULL;
	command->redir_in = 1;
	command->redir_out = 1;
	command->redir_end = 0;
	command->redir_outerror = 2;
	command->redir_varenv_content = NULL;
	command->redir_varenv_name = NULL;
	command->varenv_content = NULL;
	command->varenv_name = NULL;
	command->stop = 0;
	command->here_doc = 0;
	command->spe_doll = 0;
	command->redirection_error = 0;
	command->redir_size_cmd = 0;
	command->max_echo = 0;
	command->no_free = 0;
}

char	*i(char **pipe, t_info *info, t_data *data, t_command *command)
{
	int	i;

	info->flag_quote = 0;
	command->env = NULL;
	command->args = NULL;
	command->cmd = NULL;
	command->stop = 0;
	command->file = 0;
	command->last_heredoc = 0;
	command->flag_here_doc = 0;
	i = 0;
	command->index_struct = 0;
	command->nb_pipe = info->nbr_pipe;
	command->buildin = 0;
	command->cmd = *pipe;
	command->ir = 0;
	command->env = data->env;
	command->cmd_c = malloc(sizeof(char) * (int)ft_strlen(command->cmd) + 1);
	if (command->cmd_c == NULL)
		return (NULL);
	init_redirection(command);
	command->cmd_c[0] = 0;
	return ("good");
}
