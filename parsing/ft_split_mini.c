/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmastor <flmastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:50:04 by florianma         #+#    #+#             */
/*   Updated: 2021/12/27 15:20:08 by flmastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	mem_allocation_free2(t_info *info, int *i, int *k)
{
	info->cmd[*i] = (char *)malloc(sizeof(char) * ((*k) + 1));
	if (info->cmd[*i] == NULL)
	{
		while (*i != 0)
		{
			free(info->cmd[*i]);
			(*i)--;
		}
		free(info->cmd);
		return (0);
	}
	return (1);
}

int	mem_allocation(t_info *info, int counter, char c)
{
	int	i;
	int	j;
	int	k;
	int	guil;

	i = -1;
	j = -1;
	guil = 0;
	while (++i < counter)
	{
		k = 0;
		while (info->line[++j] && ((guil == 1) || ((info->line[j] != '|'
						|| (info->line[j] == c && (j == 0))))))
		{
			udr_mem_allocation(info, &guil, &j);
			k++;
			if (j == ft_strlen(info->line))
				break ;
		}
		mem_allocation_free(info, &j);
		if (mem_allocation_free2(info, &i, &k) == 0)
			return (0);
	}
	return (1);
}

void	ft_udr_fill_it(int *i, int *j, int *k, t_info *info)
{
	char	start;

	while (info->line[*j] && (info->line[*j] == '\'' || info->line[*j] == '"'))
	{
		start = info->line[*j];
		info->cmd[*i][(*k)++] = info->line[(*j)++];
		while (info->line[*j] && info->line[*j] != start)
		{
			if (*j == ft_strlen(info->line))
				return ;
			info->cmd[*i][(*k)++] = info->line[(*j)++];
		}
		if (*j == (int)ft_strlen(info->line))
			return ;
		info->cmd[*i][(*k)++] = info->line[(*j)++];
	}
}

void	ft_fill_it_up(int counter, t_info *info)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	while (info->line && info->line[j] && ++i < counter)
	{
		k = 0;
		while (info->line[j] && info->line[j] == '|')
			j++;
		while ((info->line[j] && (info->line[j] != '|' )))
		{
			ft_udr_fill_it(&i, &j, &k, info);
			if (info->line[j] && (info->line[j] == '|'
					|| info->line[j] == '\0'))
				break ;
			if (j == ft_strlen(info->line))
				break ;
			info->cmd[i][k] = info->line[j];
			j++;
			k++;
		}
		info->cmd[i][k] = '\0';
	}
}

void	ft_split_mini(char *line, char c, t_info *info)
{
	int	counter;

	counter = 0;
	info->line = NULL;
	info->line = line;
	if (!c || !info->line)
		return ;
	counter = get_pipe(info, c);
	info->size_total = counter;
	info->nbr_pipe = counter;
	if (counter == -1)
	{
		info->error_quote = -1;
		return ;
	}
	info->cmd = malloc(sizeof(char *) * (counter + 1));
	if (info->cmd == NULL)
		return ;
	if (!mem_allocation(info, counter, c))
		return ;
	ft_fill_it_up(counter, info);
	info->cmd[counter] = 0;
}
