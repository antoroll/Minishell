/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:00:40 by arolland          #+#    #+#             */
/*   Updated: 2021/11/12 14:28:25 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

/*void	here_doc_parse(t_pipes *pipes)
{
	char	*line;

	line = NULL;
	pipes->heredoc = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!pipes->heredoc)
	{
		free_all(pipes);
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, "pipes heredoc> ", 14);
	while (get_next_line(0, &line, 1) != 0)
	{
		if (ft_strcmp(line, pipes->limiter) == 0)
		{
			free(line);
			close(pipes->heredoc);
			break ;
		}
		write(STDOUT_FILENO, "pipes heredoc> ", 14);
		write(pipes->heredoc, line, ft_strlen(line));
		write(pipes->heredoc, "\n", 1);
		free(line);
	}
}

void	here_doc_child(t_pipes *pipes, int *end, char **argv, char **envp)
{
	char	**cmd1;
	char	*paths;

	cmd1 = NULL;
	pipes->heredoc = open("heredoc", O_RDONLY, 0644);
	dup2(pipes->heredoc, STDIN_FILENO);
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	cmd1 = ft_split(argv[3], ' ');
	free_cmd(pipes, cmd1);
	paths = path(pipes, envp, cmd1);
	if (paths == NULL)
		free_paths(pipes, paths, cmd1);
	if (execve(paths, cmd1, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd1[0], 2);
		free_tab(cmd1);
		exit(EXIT_FAILURE);
	}
}

void	here_doc_parent(t_pipes *pipes, int *end, char **argv, char **envp)
{
	char	**cmd;
	char	*paths;

	cmd = NULL;
	pipes->outfile = open(argv[5], O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_exit_bonus(pipes, "outfile", pipes->outfile);
	waitpid(pipes->pid, 0, 0);
	unlink("heredoc");
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(pipes->outfile, STDOUT_FILENO);
	close(pipes->outfile);
	cmd = ft_split(argv[4], ' ');
	free_cmd(pipes, cmd);
	paths = path(pipes, envp, cmd);
	if (paths == NULL)
		free_paths(pipes, paths, cmd);
	if (execve(paths, cmd, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free_tab(cmd);
		exit(EXIT_FAILURE);
	}
}*/

/*void	exec_heredoc_bonus(t_pipes *pipes, char **argv, char **env)
{
	int	end[2];

	pipes(end);
	here_doc_parse(pipes, argv);
	pipes->pid = fork();
	if (pipes->pid < 0)
		ft_putstr_fd("Error\nFork failed\n", 2);
	else if (pipes->pid == 0)
		here_doc_child(pipes, end, argv, env);
	else if (pipes->pid > 0)
		here_doc_parent(pipes, end, argv, env);
}*/
