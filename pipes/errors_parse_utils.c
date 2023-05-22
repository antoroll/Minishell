/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:31:50 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 22:59:23 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		write(2, cmd, ft_strlen(cmd));
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	check_builtin(t_info *info, char *cmd, t_builtin *builtin, char **paths)
{
	int	ret;

	ret = is_builtin(cmd, builtin);
	if (ret < 0 && info->flag_quote != 1 && paths != NULL)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
}

void	check_quotes(char *cmd, t_info *info)
{
	if (cmd[0] == '\0' && info->nbr_pipe >= 1)
	{
		info->flag_quote = 1;
		ft_putstr_fd("Command not found\n", 2);
	}
}
