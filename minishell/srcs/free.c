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

void	*free_redir(t_redir **redir)
{
	int	i;

	i = -1;
	while ((*redir) && (*redir)[++i].type)
	{
		(*redir)[i].type = free_single((void **)&((*redir)[i].type));
		(*redir)[i].file = free_single((void **)&((*redir)[i].file));
	}
	*redir = free_single((void **)&((*redir)));
	return (NULL);
}

void	*free_group(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	cmd->cmd = free_single((void **)&(cmd->cmd));
	cmd->path = free_single((void **)&(cmd->path));
	cmd->redir = free_redir(&(cmd->redir));
	while (cmd->arg && cmd->arg[i] != NULL)
	{
		cmd->arg[i] = free_single((void **)&(cmd->arg[i]));
		i++;
	}
	cmd->arg = free_single((void **)&(cmd->arg));
	cmd->pipe = free_single((void **)&(cmd->pipe));
	cmd = free_single((void **)&cmd);
	return (NULL);
}

void	*ft_free_cmd(t_cmd *cmd, t_info *shell)
{
	int		i;
	t_cmd	*temp;

	i = 1;
	if (!cmd)
		return (NULL);
	i = shell->num_elems;
	while (i > 0)
	{
		temp = cmd->next;
		cmd = free_group(cmd);
		if (temp == NULL)
			break ;
		i--;
		cmd = temp;
	}
	shell->num_elems = 0;
	shell->cmd = NULL;
	return (NULL);
}
