/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:19:51 by arolland          #+#    #+#             */
/*   Updated: 2021/11/03 15:45:10 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

/*int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		d;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i + 1 < n)
		i++;
	d = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (!d || !n)
		return (0);
	else if (d < 0)
		return (-1);
	else
		return (1);
}*/

int	get_next_line(int fd, char **line, int ret)
{
	int		i;
	char	buf;

	ret = 1;
	if (!line)
		return (-1);
	*line = malloc(1234567);
	**line = 0;
	i = 0;
	buf = 0;
	while (ret > 0)
	{
		ret = read(fd, &buf, 1);
		if (buf == '\n')
			break ;
		else if (buf == '\0')
			break ;
		(*line)[i] = buf;
		buf = 0;
		i++;
	}
	(*line)[i] = 0;
	if (ret == -1)
		**line = 0;
	return (ret);
}
