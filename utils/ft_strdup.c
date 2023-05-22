/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:24:00 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 11:04:29 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*ft_strdup(char *s1)
{
	char	*dst;
	size_t	i;

	dst = NULL;
	i = 0;
	if (!s1)
		return (NULL);
	dst = ft_calloc(sizeof(char), (ft_strlen(s1) + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
