/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udr_redirection_out2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:33:30 by flmastor          #+#    #+#             */
/*   Updated: 2021/12/23 12:35:26 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	help_doublq_redirection1(t_command *command, char *str)
{
	str[command->ir] = ' ';
	str[command->ir + 1] = 0;
	command->i = command->i + 2;
	return (-1);
}
