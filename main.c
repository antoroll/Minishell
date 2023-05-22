/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:21:33 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

int	g_exit_status = 0;

void	through_pipe(t_info *info, t_data *data, char **envp)
{
	t_command	*command;
	t_pipes		pipes[1];
	t_builtin	*builtin;

	(void)envp;
	builtin = malloc(sizeof(t_builtin) * 8);
	command = malloc(sizeof(t_command) * info->nbr_pipe);
	init_builtin(builtin);
	command->pipes = pipes;
	command->builtin = builtin;
	data->i = -1;
	info->last_here_doc = 0;
	while (info->cmd[++data->i])
	{
		if (i(&info->cmd[data->i], info,
				data, &command[data->i]) != NULL)
			parser(info->cmd[data->i], &command[data->i], info, data->i);
		data->nbr_pipe = data->i;
	}
	exec_multipipes(info, data, builtin, command);
	data->check = 0;
	udr_through_pipes(data, command, info, builtin);
}

void	mini_loop(t_info *info, t_data *data)
{
	int	check;

	check = 0;
	info->error_quote = 0;
	signal(SIGINT, handle_sigusr1);
	signal(SIGQUIT, handle_sigusr1);
	signal(SIGTSTP, handle_sigusr1);
	while (1)
	{
		data->line = readline("bash-3.2$ ");
		add_history(data->line);
		if (!data->line)
		{
			free(data->line);
			break ;
		}
		if (data->line[0] == '\0' || ft_strcmp(data->line, "minishell") == 0
			|| check_white_space(data->line) == 0)
		{
			free(data->line);
			continue ;
		}
		under_mini_loop(info, data);
		udr_mini_loop(data);
	}
}

void	under_mini_loop(t_info *info, t_data *data)
{
	int		syntax;
	int		error;
	char	*test;

	error = 0;
	syntax = syntax_check(data->line);
	if (info->error_quote == 0 && syntax != (-1))
		error = check_pipe(info, data);
	while (error != 0 && syntax != (-1))
	{
		if (info->error_quote == -1)
		{
			info->input = ft_strdup(data->line);
			free(data->line);
			test = readline("quote > ");
			data->line = ft_strjoin(info->input, test);
			free(info->input);
			info->error_quote = 0;
		}
		if (info->error_quote == 0)
		{
			free(test);
			error = check_pipe(info, data);
		}
	}
}

void	udr_mini_loop(t_data *data)
{
	int	stdin;
	int	stdout;

	stdin = dup(0);
	stdout = dup(1);
	dup2(stdin, 0);
	dup2(stdout, 1);
	close(stdout);
	close(stdin);
	close(stdout);
	close(stdin);
	if (data->line)
		free(data->line);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data[1];
	t_info	info[1];

	(void)av;
	init_vars(data, info);
	if (ac == 1)
	{
		if (envp[0] == NULL)
			return (1);
		if (envp)
		{
			data->env = get_env(envp);
		}
		mini_loop(info, data);
		rl_clear_history();
		printf(" exit\n");
		free_tab(data->env);
	}
	return (0);
}
