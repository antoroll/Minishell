/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_gest_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 20:29:26 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	help_syntax_g(char c, int *d_q, int *s_q, int choice)
{
	if (choice == 1)
	{
		if (c == '"')
			*d_q = 1;
		else if (c == '\'')
			*s_q = 1;
	}
	if (choice == 2)
	{
		if (c == '"')
			*d_q = 0;
		else if (c == '\'')
			*s_q = 0;
	}
}

int	msg_errorr(char c, int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if (choice == 2)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline", 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (0);
}
