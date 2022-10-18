/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:54:26 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/22 17:18:07 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_last_pipe(t_info *shell)
{
	char	*temp;
	char	*line;
	int		flag;

	flag = 0;
	while (search_pipe(shell->cmd_line, &flag))
	{
		temp = ft_strdup(shell->cmd_line);
		free(shell->cmd_line);
		line = readline(">");
		if (line && *line)
			add_history(line);
		shell->cmd_line = ft_strjoin(temp, line);
		if (!ft_strncmp(line, "|", 1))
		{
			free(line);
			free(temp);
			break ;
		}
		free(temp);
		free(line);
	}
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

	i = -1;
	if (cmd == NULL)
		return (NULL);
	cmd->cmd = free_single((void **)&(cmd->cmd));
	cmd->path = free_single((void **)&(cmd->path));
	cmd->redir = free_redir(&(cmd->redir));
	while (cmd->arg && cmd->arg[++i])
		cmd->arg[i] = free_single((void **)&(cmd->arg[i]));
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

int	minishell(t_info *shell)
{
	int	pars_res;

	if (syntax_check(shell, shell->cmd_line) == -1)
		return (0);
	if (!check_first_pipe(shell))
		return (0);
	check_last_pipe(shell);
	pars_res = parser(shell);
	if (pars_res != 0)
		return (0);
	check_all_quotes(shell->cmd, shell);
	executor(shell);
	shell->cmd_line = free_single((void **)&(shell->cmd_line));
	ft_free_cmd(shell->cmd, shell);
	return (0);
}
