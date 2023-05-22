/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:55:07 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 14:14:03 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*ft_strrcpy(char *dest, char *src)
{
	int		i;
	char	*tab;

	(void) dest;
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

char	**ft_free_lol(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

char	**get_env(char **envp)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	while (envp[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tab[i] = ft_strrcpy(tab[i], envp[i]);
		if (!tab[i])
			return (ft_free_lol(tab));
		i++;
	}
	tab[i] = 0;
	return (tab);
}
