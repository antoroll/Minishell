/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:56:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/27 15:16:10 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTION_H

# define MINISHELL_EXECUTION_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <curses.h>
# include <signal.h>

extern int	g_exit_status;

typedef struct s_pipes {
	int		i;
	int		j;
	int		k;
	int		o;
	int		g;
	int		b;
	int		in;
	int		out;
	int		flag;
	int		flag2;
	int		flag3;
	int		size;
	int		pid;
	int		outfile;
	int		infile;
	char	*heredoc;
	char	**arr;
	char	**args;
	char	*paths;
	char	*path_parsing;
	int		*pids;
	int		**pipes;
	int		flag_pipe;
	int		heredoc_flag;
	char	*limiter;
	int		status;
}	t_pipes;

typedef struct s_data {
	char	**env;
	char	**env_refresh;
	char	**env_doublon;
	char	**unset_doublon;
	char	*path;
	char	*pwd;
	char	*cmd;
	int		nbr_pipe;
	int		check;
	char	**tab;
	int		flag;
	int		ret;
	char	**arr;
	int		count;
	int		tmp;
	char	*path_cd;
	char	*pathing;
	char	*path2;
	int		i;
	char	*line;
	t_pipes	*pipes;
}	t_data;

typedef struct s_info
{
	char	**av;
	char	**cmd;
	char	*input;
	int		error_quote;
	int		nbr_pipe;
	int		flag_quote;
	int		last_here_doc;
	int		size_total;
	int		i;
	char	*final_path;
	char	*half_path;
	char	*cmd_bis;
	int		k;
	int		j;
	char	*line;
}	t_info;

typedef struct s_command
{
	int					i;
	int					j;
	char				*cmd;
	char				*cmd_c;
	char				**env;
	char				**args;
	char				*arg;
	int					buildin;
	int					nb_pipe;	
	int					redir_in;
	char				*redir_charin;
	int					redir_out;
	char				*redir_charout;
	int					redir_outerror;
	char				*redir_charerr;
	int					redir_end;
	int					ir;
	char				*redir_varenv_name;
	char				*redir_varenv_content;
	char				*varenv_name;
	char				*varenv_content;
	int					stop;
	int					flag_null;
	int					here_doc;
	t_pipes				*pipes;
	int					spe_echo;
	int					spe_doll;
	int					redirection_error;
	int					redir_size_cmd;
	int					file;
	int					last_heredoc;
	int					flag_here_doc;
	int					index_struct;
	int					ii;
	int					max_echo;
	int					no_free;
	struct s_builtin	*builtin;
}		t_command;

typedef struct s_builtin{
	char	*cmd;
	int		(*func)(t_data *, t_info *, t_command *, t_pipes *pipes);
}	t_builtin;

char	**ft_split(const char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putstr_fd(char const *s, int fd);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_exit(t_pipes *pipes, char *str, int file, char *tab);
void	ft_exit_bonus(t_command *cmd, char *str, int file, t_info *info);
void	free_arr(char **str);
void	free_tab(char **str);
char	*path(t_pipes *pipes, char **envp, char **cmd);
void	child_process(t_pipes *pipes, char **argv, char **envp, char **cmd);
void	parent_process(t_pipes *pipes, int *pid);
void	exec_mandatory(t_pipes *pipes, char **argv, char **envp);
int		get_next_line(int fd, char **line, int ret);
void	get_next_line_heredoc(char **line, int *i);
void	invalid_command(t_pipes *pipes, char **cmd);
void	invalid_command_bonus(t_pipes *pipes, t_command *cmd, t_info *info);
void	open_pipes(t_command *cmd, t_info *info);
void	parent_bonus(t_command *cmd, t_info *info);
void	init_vars_pipes(t_command *cmd, t_info *info);
void	error_args(t_command *cmd, t_info *info);
void	here_doc_parent(t_pipes *pipes, int *end, char **argv, char **envp);
void	here_doc_child(t_pipes *pipes, int *end, char **argv, char **envp);
void	check_heredoc(t_pipes *pipes, char *cmd);
void	exec_heredoc_bonus(t_pipes *pipes, char **argv, char **envp);
void	do_fork(t_command *cmd, t_info *info);
void	free_all(t_command *cmd, t_info *info);
void	free_mandatory(t_pipes *pipes, char **cmd, char *str);
void	free_cmd(t_command *cmd, char **args, t_info *info);
void	free_paths(t_command *cmd, char *paths, char **args, t_info *info);
char	*path_parsing(char **envp, char **cmd, t_builtin *b, t_info *i);
void	parsing_errors(t_data *d, t_command *cmd, t_info *i, t_builtin *b);
void	close_pipes(t_command *cmd, t_info *info);
int		execve_child(t_pipes *p, t_data *d, t_command *cmd, t_info *i);
int		is_builtin(char *line, t_builtin *builtin);
void	exec_multipipes(t_info *i, t_data *d, t_builtin *b, t_command *cmd);
void	here_doc_parse(t_command *cmd);
char	**get_env(char **envp);
char	**get_env_refresh(t_data *data, char **envp, char *oldpwd, char *pwd);
char	*ft_strcpy(char *dest, char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
void	get_path(t_data *data, char **envp);
int		display_pwd(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes);
void	ft_putchar_fd(char c, int fd);
int		get_cd(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes);
void	free_tab(char **tab);
void	init_vars(t_data *data, t_info *info);
char	**ft_free_lol(char **envp);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrcpy(char *dest, char *src);
int		ft_export(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes);
int		display_export(t_data *data);
char	**get_env_unset(char **envp, char **args, char **arr);
char	*ft_strchr(const char *s, int c);
int		ft_unset(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes);
char	**split_export(t_data *data, char **envp);
char	**ft_split(const char *s, char c);
char	**remove_equals(char **arr);
int		display_errors(char **args);
int		exit_prompt(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes);
int		ft_env(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes);
void	init_builtin(t_builtin *builtin);
int		check_pipes(t_data *data);
void	first_command(t_command *cmd, t_info *info);
void	last_command(t_command *cmd, t_info *info);
void	middle_command(t_command *cmd, t_info *info);
int		here_doc(t_pipes *pipes, t_command *cmd);
void	handle_sigusr1(int signum);
void	handle_exit_status(int status);
void	multipipes_signal_handling(int status);
int		ft_atoi(const char *str);
void	here_doc_parse(t_command *cmd);
int		ft_isalpha(int c);
void	ft_putnbr_fd(int nb, int fd);
void	free_builtin(t_info *info, t_pipes *pipes);
void	under_exit_prompt(t_info *info, t_command *cmd, t_data *data);
void	under_unset(t_info *info, t_data *data, t_command *cmd, char **arr);
char	**under_rm_equals(char **arr, int *count, char **tab);
void	error_unset(char **args);
void	under_get_env_unset(char **envp, char **args, char **arr);
void	under_export(t_data *data, t_info *info, t_command *cmd);
char	**under_env_doublon(char **tab, int i, char **envp);
void	udr_export(char **export, int i, t_data *data, char **envp);
void	under_env_refresh_export_suite(char **export, int i, t_data *data);
void	check_doublon_tab(char **export, int flag, t_data *data);
void	under_check_doublon(char **export, t_data *data, int flag);
void	under_doublon_bis(t_data *data, char **envp);
void	under_middle_command(t_command *cmd);
void	exec_builtin(t_command *cmd, t_data *d, t_builtin *b, t_info *i);
void	under_exec_builtin(t_command *cmd);
void	under_exec(t_command *cmd, t_builtin *b, t_data *d, t_info *i);
void	execve_dot(t_command *cmd, t_info *info, t_data *data);
void	execve_double_dot(t_command *cmd, t_info *info, t_data *data);
void	udr_exit(t_info *info, t_command *cmd, t_data *data, int exitt);
void	udr_exit_bis(t_info *info, t_command *cmd, t_data *data, int exitt);
void	check_quotes(char *cmd, t_info *info);
void	check_builtin(t_info *i, char *c, t_builtin *bu, char **p);
void	check_cmd(char *cmd);
void	under_env_refresh(t_data *data, char **envp, char *pwd, char *oldpwd);
void	under_get_cd(t_command *cmd, t_data *data, t_info *info);
void	udr_get_cd(t_command *cmd, t_data *data, t_info *info);
void	mini_get_cd(t_data *data);
void	udr_exit_pipe(t_info *info, t_command *cmd, t_data *data, int exitt);
void	mini_norme(t_data *data);
char	**get_env_refresh_export(char **envp, char **export, t_data *data);
char	**check_doublon(char **envp, char **export, t_data *data);
void	free_export(t_data *data, t_command *cmd, t_info *info);
void	free_unset(t_command *cmd, t_info *info);
void	udr_through_pipes(t_data *d, t_command *c, t_info *i, t_builtin *b);
int		check_pipe(t_info *info, t_data *data);
void	under_mini_loop(t_info *info, t_data *data);
void	udr_mini_loop(t_data *data);
int		check_white_space(char *line);
void	through_pipe(t_info *info, t_data *data, char **envp);
void	error_export(void);
void	free_cmd_export(t_data *data);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *b, size_t n);
char	**get_env(char **envp);
char	*ft_strcpy(char *dest, char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	get_path(t_data *data, char **envp);
void	display_prompt(t_info *info, t_data *data);
void	ft_split_mini( char *line, char c, t_info *info);
void	ft_putchar_fd(char c, int fd);
int		echo_command(t_data *d, t_info *i, t_command *cmd, t_pipes *p);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	init_info(t_info *info);
void	display_struct(t_command *command);
int		double_quote(t_command *command, int *i, int *j, int k);
int		command_q(t_command *command, int *i, int *j, int k);
int		get_option(t_command *command, int line, int line_tmp, int assist);
int		check_env(t_command *command, int line, int i, int no_q);
void	env_copy(t_command *command, int arg, int i, char *value);
char	*gett_env(char *env, t_command *command);
void	display1(t_command *command);
int		redirection(t_command *command);
void	ft_putstr(char *str);
void	free_midway(t_command *command);
void	free_info(t_info *info);
int		cmd_extract(t_command *command, int *i, int *j);
int		redirection_out_error(t_command *command);
int		redirection_arg(t_command *command);
int		redirection_cmd(t_command *command);
int		redirection_in(t_command *command, int i);
int		redirection_out(t_command *command, int i);
int		create_file_in(t_command *command);
int		create_file(t_command *command, int type);
int		redirection_env(t_command *command, int sortie, int espace);
int		error_file_management(char *str, char *msg);
int		parser(char *pipe, t_command *command, t_info *info, int ii);
char	*i(char **pipe, t_info *info, t_data *data, t_command *command);
int		redirection_args(t_command *command);
char	*redirection_realoc(t_command *command, char *content, char *str);
int		just_spaces(char *str);
char	*ft_itoa(int nb);
int		spaces_middle(char *str);
char	*gett_env(char *env, t_command *command);
int		previous_command_status(t_command *command, int sortie, int line);
int		get_name_varenv(t_command *command, char *var_name);
int		check_env_command(t_command *command, int line, int no_q);
int		check_env_option(t_command *command, int i, int no_q);
char	*space_gestion(char *str, char *full_cmd, int v);
void	free_info(t_info *info);
void	help_syntax_g(char c, int *d_q, int *s_q, int choice);
int		syntax_check(char *str);
int		msg_errorr(char c, int choice);
void	udr_echo_command2(t_command *command, t_info *info, t_data *data);
void	udr_echo_command(t_command *command);
void	help_file_creation(t_command *command);
int		file_creation1(t_command *command);
int		simpleq_redirection1(t_command *command, char *str);
int		help_double_q_redirection1(t_command *command, int *j, int choice);
void	help_doublq_redirection(t_command *command, int *j);
int		help_doublq_redirection1(t_command *command, char *str);
int		simple_quote_cmd(t_command *command, int *i, int *j, int error);
char	*load_args(t_command *command, int line, int ret);
int		under_get_option(t_command *cmd, int *line, int *l, int c);
int		last_check(t_command *command, char *arg, int line);
int		help_dr2(t_command *command, char *str, int j);
int		simpleq_redirection2(t_command *command, char *str);
int		create_file2(t_command *command);
int		simpleq_redirection0(t_command *command, char *str);
int		file_creation0(t_command *command);
char	*ft_0(char *dest);
int		len(long nb);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strequ(const char *s1, const char *s2);
int		redirection_env_preparation(t_command *command, int *ret);
int		help_redirection_env(t_command *command, int sortie, int ret);
int		env_redir_ambig(t_command *command, int into_q);
void	h_prev_command_status(t_command *command, int sortie, char *value);
void	udr_redirection_env(t_command *command);
int		case_check_dolls(t_command *command, int arg, int line);
char	*realoc_env(t_command *command, char *content, char *str);
int		gett_name_varenv(t_command *command, char **var_name);
int		udr_env(t_command *command, char *content);
int		follow_env(int i, char *cmd_full);
int		add_space_before_condition(char *cmd_full, int i);
int		add_space_before_util(char *cmd_full, int i, char *tmp);
int		add(char *cmd_full, char *copy, char **new, int i);
int		add_space_before(char *tmp, char *cmd_full, int k, char **new);
void	add_space_after(char *tmp, char *cmd_full, int k, char **new);
void	copy(char **new, char *str, int i);
int		size_cleaned_space(char *str);
int		ft_space(char c);
void	udr_spc_gestion( char *new, char *str);
int		under_load_args(t_command *command, int *line, int *ret, int choice);
int		udr_final(void);
int		only_c(char *str, char c);
int		ft_is_space(char c);
int		mem_allocation_free2(t_info *info, int *i, int *k);
void	udr_mem_allocation(t_info *info, int *guil, int *j);
void	mem_allocation_free(t_info *info, int *j);
int		assist_check_closed(t_info *info);
int		is_closed(t_info *info, int *i, char c);
int		ahead_is_closed(t_info *info, int *i, char c);
void	assignation_get_p(int *i, int *nb_word, int *error);
int		get_pipe(t_info *info, char c);

#endif