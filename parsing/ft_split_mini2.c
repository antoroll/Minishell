/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:19:23 by flmastor          #+#    #+#             */
/*   Updated: 2021/12/27 15:19:51 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	assist_check_closed(t_info *info)
{
	int	i;
	int	quote1;
	int	quote2;

	i = 0;
	quote1 = 0;
	quote2 = 0;
	while (info->line[i])
	{
		if (info->line[i] == '\'' && quote1 == 0)
			quote1 = 1;
		else if (info->line[i] == '\'' && quote1 == 1)
			quote1 = 0;
		if (info->line[i] == '"' && quote2 == 0)
			quote2 = 1;
		else if (info->line[i] == '"' && quote2 == 1)
			quote2 = 0;
		i++;
	}
	return (quote1 + quote2);
}

int	is_closed(t_info *info, int *i, char c)
{
	(*i) += 1;
	while (info->line[*i] && info->line[*i] != c)
		(*i)++;
	if (*i == (int)ft_strlen(info->line) && assist_check_closed(info) != 0)
		return (-1);
	(*i)++;
	return (*i);
}

int	ahead_is_closed(t_info *info, int *i, char c)
{
	(void)c;
	while ((info->line[*i]) && (info->line[*i] == '\''
			|| info->line[*i] == '"'))
	{
		while (info->line[*i] && info->line[*i] == '"')
		{
			*i = is_closed(info, i, '"');
			if (*i == (-1))
				return (-1);
		}
		while (info->line[*i] && info->line[*i] == '\'')
		{
			*i = is_closed(info, i, '\'');
			if (*i == (-1))
				return (-1);
		}
	}
	return (0);
}

void	assignation_get_p(int *i, int *nb_word, int *error)
{
	*i = -1;
	*nb_word = 0;
	*error = 0;
}

int	get_pipe(t_info *info, char c)
{
	int	i;
	int	j;
	int	size;
	int	nb_word;
	int	error;

	assignation_get_p(&i, &nb_word, &error);
	size = ft_strlen(info->line);
	while (info->line[++i])
	{
		if (ahead_is_closed(info, &i, c) == -1)
			return (-1);
		if (info->line[i] && info->line[i] == c && info->line[i + 1] != c)
		{
			j = 1 + i;
			while (info->line[j] && info->line[j] == ' ')
				j++;
			if (i != size)
				nb_word = nb_word + 1;
		}
		if (i == size)
			break ;
	}
	nb_word += 1;
	return (nb_word);
}
