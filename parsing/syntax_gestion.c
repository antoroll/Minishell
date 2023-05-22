/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:04 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 11:53:14 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	syntax_check_0(char *str, int *err, int d_q, int s_q)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'' ) && (d_q == 0 && s_q == 0))
			help_syntax_g(str[i], &d_q, &s_q, 1);
		else if ((str[i] == '"' || str[i] == '\'') && (d_q == 1 || s_q == 1))
			help_syntax_g(str[i], &d_q, &s_q, 2);
		if ((str[i] == '>' || str[i] == '<') && (s_q == 0 && d_q == 0))
		{
			*err = (*err) + 1;
			if (*err > 2)
				break ;
		}
		else if (str[i] == ' ')
			;
		else
			*err = 0;
	}
}

void	syntax_check_1(char *str, int *err)
{
	int	i;
	int	d_q;
	int	s_q;

	d_q = 0;
	s_q = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'' ) && (d_q == 0 && s_q == 0))
			help_syntax_g(str[i], &d_q, &s_q, 1);
		else if ((str[i] == '"' || str[i] == '\'') && (d_q == 1 || s_q == 1))
			help_syntax_g(str[i], &d_q, &s_q, 2);
		if (str[i] == '|' && (s_q == 0 && d_q == 0))
		{
			*err = (*err) + 1;
			if (*err > 1)
				break ;
		}
		else if (str[i] == ' ')
			;
		else
			*err = 0;
	}
}

int	syntax_check_2(char *str, int i)
{
	while (i >= 0)
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
			{
				if (str[i] == '>' || str[i] == '<' || str[i] == '|')
				{
					ft_putstr_fd("bash: error unexpected token `newline'\n", 2);
					return (-1);
				}
				i--;
			}
		}
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			return (-1);
		}
		break ;
	}
	return (0);
}

int	syntax_last_check(char *str, int i, int d_q, int s_q)
{
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'' ) && (d_q == 0 && s_q == 0))
			help_syntax_g(str[i], &d_q, &s_q, 1);
		else if ((str[i] == '"' || str[i] == '\'') && (d_q == 1 || s_q == 1))
			help_syntax_g(str[i], &d_q, &s_q, 2);
		if (str[i] && (str[i] == '<' || str[i] == '>')
			&& (d_q == 0 && s_q == 0))
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
			{
				if ((i > 1 && str[i - 1] == ' ')
					&& (str[i] == '<' || str[i] == '>'))
					return (-1);
				i++;
			}
		}
	}
	return (0);
}

int	syntax_check(char *str)
{
	int	err;

	err = 0;
	syntax_check_0(str, &err, 0, 0);
	if (err > 2)
	{
		free(str);
		return (msg_errorr(' ', 1));
	}
	err = 0;
	syntax_check_1(str, &err);
	if (err > 1)
	{	
		free(str);
		return (msg_errorr(' ', 2));
	}
	err = 0;
	if (syntax_check_2(str, (int)ft_strlen(str) -1) == -1
		|| syntax_last_check(str, (-1), 0, 0) == (-1))
	{
		free(str);
		return (msg_errorr(' ', 1));
	}
	return (0);
}
