/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_redirection2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:31:26 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:32:05 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	ft_taille(int nbr)
{
	int	compteur;

	compteur = 0;
	if (nbr < 0)
	{
		compteur++;
		nbr *= (-1);
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		compteur++;
	}
	return (compteur);
}

char	*ft_0(char *dest)
{
	dest = malloc (2 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = '0';
	dest[1] = '\0';
	return (dest);
}

int	len(long nb)
{
	int		size;

	size = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		size++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}
