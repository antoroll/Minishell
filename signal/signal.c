/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:03:43 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 10:41:53 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	signal_sigint_stdin(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	signal_singint_normal(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	signal_singint_stdin_multipipe(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 0;
}

void	multipipes_signal_handling(int status)
{
	if (WIFEXITED(status) == 0)
	{
		g_exit_status = WIFEXITED(status);
		if (status == 13)
			g_exit_status = 0;
		if (status == 131)
			g_exit_status = 131;
	}
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		if (status == 256)
			g_exit_status = 0;
	}
}

void	handle_sigusr1(int signum)
{
	if (signum == SIGINT && g_exit_status != 1234567890
		&& g_exit_status != 123456789)
		signal_singint_normal();
	else if (signum == SIGINT
		&& isatty(0) != 0 && g_exit_status != 123456789)
		signal_sigint_stdin();
	else if (signum == SIGINT && isatty(0) != 0)
		signal_singint_stdin_multipipe();
	else if ((signum == SIGQUIT && g_exit_status == 123456789)
		|| (signum == SIGQUIT && g_exit_status == 1234567890))
	{
		write(2, "\b\b  \b\b", 6);
		write(2, "Quit\n", 5);
		g_exit_status = 131;
	}
	else if (signum == SIGQUIT || signum == SIGTSTP)
	{
		write(2, "\b\b  \b\b", 6);
		g_exit_status = 131;
	}
}
