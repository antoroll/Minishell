/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:37:57 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:38:43 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	ft_str_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strequ(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if ((s1[i] - s2[i]) == 0)
		return (1);
	else
		return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	if (s == 0)
		return (0);
	if (start + len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s) - start;
	if (len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s);
	if (start >= (unsigned int)ft_strlen(s) || len <= 0)
		len = 0;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		res[0] = '\0';
		return (res);
	}
	i = -1;
	while (s[start + ++i] && i < len)
		res[i] = s[start + i];
	res[i] = '\0';
	return (res);
}
