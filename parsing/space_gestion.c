/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:50:04 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 14:00:39 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	ft_space(char c)
{
	if (c == '\f' || c == '\t'
		|| c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	size_cleaned_space(char *str)
{
	int		i;
	int		len;
	char	found_space;

	len = (int)ft_strlen(str);
	if (str && (len) > 0)
		while ((len - 1) > 0 && str[len - 1] && ft_space(str[len - 1]))
			len--;
	str[len] = '\0';
	i = 0;
	while (str[i] && ft_space(str[i]))
		i++;
	len -= i;
	i--;
	found_space = 0;
	while (str[++i])
	{
		if (ft_space(str[i]) && !found_space)
			found_space = 1;
		else if (ft_space(str[i]))
			len--;
		else
			found_space = 0;
	}
	return (len);
}

void	copy(char **new, char *str, int i)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (str[i])
	{
		if ((ft_space(str[i]) && !k))
		{
			k = 1;
			(*new)[j++] = str[i];
		}
		else if (!ft_space(str[i]))
		{
			k = 0;
			(*new)[j++] = str[i];
		}
		i++;
	}
	(*new)[j] = '\0';
}

void	add_space_after(char *tmp, char *cmd_full, int k, char **new)
{
	int	i;
	int	j;

	j = (int)ft_strlen(*new);
	if (!tmp)
		return ;
	i = (int)(ft_strlen(tmp) - 1);
	if (i < 0)
		return ;
	if (tmp[i] == ' ' && follow_env(k, cmd_full) && cmd_full[k] == '$')
		return ;
	if (tmp[i] == ' '
		&& (cmd_full[k] == '"' || cmd_full[k] == '\''
			|| cmd_full[k] == '$'))
	{
		(*new)[j] = ' ';
		(*new)[j + 1] = '\0';
	}
}

void	udr_spc_gestion( char *new, char *str)
{
	int	i;
	int	j;

	j = (int)ft_strlen(str);
	if (str && (j) > 0)
		while ((j - 1) > 0 && str[j - 1] && ft_space(str[j - 1]))
			j--;
	str[j] = '\0';
	i = 0;
	while (str[i] && ft_space(str[i]))
		i++;
	copy(&new, str, i);
	free(str);
}
