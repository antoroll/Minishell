/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:43:57 by arolland          #+#    #+#             */
/*   Updated: 2021/12/15 17:47:31 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	get_path(t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) == 0)
			data->path = ft_strdup(envp[i]);
		i++;
	}
}
