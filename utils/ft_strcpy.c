/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:24:00 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:50:59 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*ft_strcpy(char *dest, char *src)
{
	int		i;
	char	*tab;

	(void)dest;
	i = 0;
	while (src[i])
		i++;
	tab = malloc(sizeof(char) * i + 1);
	i = -1;
	while (src[++i])
		tab[i] = src[i];
	tab[i] = '\0';
	return (tab);
}
