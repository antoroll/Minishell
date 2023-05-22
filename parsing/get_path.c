/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florianmastorakis <florianmastorakis@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:43:57 by arolland          #+#    #+#             */
/*   Updated: 2021/11/25 14:35:13 by florianmast      ###   ########.fr       */
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
