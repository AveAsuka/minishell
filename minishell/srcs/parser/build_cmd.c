/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:19:07 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/11 23:19:07 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_elem(char *cmd, t_info *shell)
{
	t_cmd	*temp;

	temp = malloc(sizeof(t_cmd));
	if (!temp)
		return (NULL);
	ft_bzero(temp, sizeof(t_cmd));
	temp->redir = make_redir(&cmd);
	temp->cmd = make_cmd(&cmd);
	if (temp->cmd != NULL)
	{
		temp->path = make_path(&temp->cmd);
		if (!temp->path)
			temp->path = make_env_path(temp->cmd, shell);
		temp->pipe = make_pipe(&cmd);
		temp->arg = make_arg(&cmd, temp);
	}
	if (!temp->redir)
	{
		temp->redir = (t_redir *)malloc(sizeof(t_redir) * 1);
		temp->redir->type = NULL;
		temp->redir->file = NULL;
	}
	temp->redir->infile = 0;
	temp->redir->outfile = 1;
	return (temp);
}

int	add_elem(t_cmd *cmd, t_info *shell)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	if (!cmd)
		return (-1);
	if (!shell->cmd)
	{
		shell->cmd = cmd;
		shell->cmd->next = cmd;
		shell->cmd->prev = cmd;
	}
	else
	{
		temp = shell->cmd;
		while (++i < shell->num_elems)
			shell->cmd = shell->cmd->next;
		temp->prev = cmd;
		shell->cmd->next = cmd;
		cmd->prev = shell->cmd;
		cmd->next = temp;
		shell->cmd = temp;
	}
	shell->num_elems++;
	return (1);
}

int	build_cmd(char **cmd, t_info *shell)
{
	int	i;

	i = 0;
	shell->num_elems = 0;
	shell->cmd = NULL;
	while (cmd[i])
	{
		if (add_elem(init_elem(cmd[i], shell), shell) == -1)
			return (-1);
		i++;
	}
	return (1);
}
