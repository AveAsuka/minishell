/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:10:10 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 19:12:17 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_action_many_cmd(t_info *struktura, t_cmd *tmp)
{
	char	*ex;

	env_reverse_convert(struktura);
	if (struktura->cmd->path == NULL)
		ex = ft_strdup(tmp->cmd);
	else
		ex = ft_strjoin(tmp->path, tmp->cmd);
	struktura->command_result = execve(ex, tmp->arg, struktura->envp);
	struktura->command_result = 0;
	ft_perror_cmd_nf(1, struktura);
}

void	execve_action(t_info *st)
{
	char	*ex;

	env_reverse_convert(st);
	if (st->cmd->path == NULL)
		ex = ft_strdup(st->cmd->cmd);
	else
		ex = ft_strjoin(st->cmd->path, st->cmd->cmd);
	st->command_result = execve(ex, st->cmd->arg, st->envp);
	st->command_result = 0;
	ft_perror_cmd_nf(1, st);
}
