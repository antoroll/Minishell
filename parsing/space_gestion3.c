/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_gestion3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:33:58 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 12:34:08 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*space_gestion(char *str, char *cmd_full, int i)
{
	char	*new;
	char	*tmp;
	int		len;

	tmp = NULL;
	tmp = ft_strdup(str);
	len = size_cleaned_space(str);
	new = (char *)malloc(sizeof(char) * (len + 3));
	if (!(new))
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	udr_spc_gestion(new, str);
	if (add_space_before(tmp, cmd_full, i, &new) == -1)
	{
		if (tmp)
			free(tmp);
		return (new);
	}
	add_space_after(tmp, cmd_full, i, &new);
	if (tmp)
		free(tmp);
	return (new);
}
