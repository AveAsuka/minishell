/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:53:45 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/10 22:53:45 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_single(void **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	return (NULL);
}

void	*free_double(void **line)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i])
			line[i] = free_single((void **)&(line[i]));
		else
			break ;
		i++;
	}
	line = free_single((void **)&line);
	return (NULL);
}
