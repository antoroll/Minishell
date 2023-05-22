/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:50:04 by florianma         #+#    #+#             */
/*   Updated: 2021/12/23 12:31:18 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*redirection_realoc(t_command *command, char *content, char *str)
{
	char	*tmp;
	int		j;

	j = -1;
	tmp = NULL;
	str[command->ir + 1] = 0;
	tmp = ft_strjoin(str, content);
	if (str)
		free(str);
	str = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(command->cmd) + 1));
	if (!str)
		return (NULL);
	while (tmp[++j])
		str[j] = tmp[j];
	str[j] = 0;
	if (tmp)
		free(tmp);
	command->ir = ft_strlen(str) - 1;
	if (command->i == (int)ft_strlen(command->cmd))
		command->i++;
	return (str);
}

int	just_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	if (str)
	{
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

int	spaces_middle(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
	{
		i++;
	}
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
	{
		i++;
		if (str[i] && str[i] != ' ')
			return (1);
	}
	return (0);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	str = NULL;
	if (n == 0)
		return (ft_0(str));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}
