/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:10:36 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:47:43 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_entry(t_info *data, t_cmd *tmp, int i, int red_final)
{
	close(data->pipe_fd[i][0]);
	pipe_close_maza_faka(data, i, tmp);
	if (tmp->redir[red_final].outfile == 1)
		if (dup2(data->pipe_fd[i][1], 1) == -1)
			ft_perror_exit_child("Inside child dup error", 1);
	close(data->pipe_fd[i][1]);
}

void	last_entry(t_info *data, t_cmd *tmp, int i, int red_final)
{
	close(data->pipe_fd[i - 1][1]);
	pipe_close_maza_faka(data, i, tmp);
	if (tmp->redir[red_final].infile == 0)
		if (dup2(data->pipe_fd[i - 1][0], 0) == -1)
			ft_perror_exit_child("Inside child dup error", 1);
	close(data->pipe_fd[i - 1][0]);
}

void	routine(t_info *data, t_cmd *tmp, int i, int red_final)
{
	close(data->pipe_fd[i - 1][1]);
	close(data->pipe_fd[i][0]);
	pipe_close_maza_faka(data, i, tmp);
	if (tmp->redir[red_final].infile == 0)
		if (dup2(data->pipe_fd[i - 1][0], 0) == -1)
			ft_perror_exit_child("Inside child dup error", 1);
	if (tmp->redir[red_final].outfile == 1)
		if (dup2(data->pipe_fd[i][1], 1) == -1)
			ft_perror_exit_child("Inside child dup error", 1);
	close(data->pipe_fd[i - 1][0]);
	close(data->pipe_fd[i][1]);
}

void	do_stroka(t_info *data, t_cmd *tmp)
{
	int	p;

	p = 0;
	if (data->stroka)
	{
		while (data->stroka[p])
		{
			free(data->stroka[p]);
			p++;
		}
		free(data->stroka);
		data->stroka = NULL;
	}
	data->stroka = ft_split(tmp->cmd, '/');
}

void	close_pipe(t_pipe *pip, t_cmd *tmp, t_info *data)
{
	int	i;
	int	status;

	i = 0;
	while (pip->counter != 0)
	{
		close(data->pipe_fd[i][0]);
		close(data->pipe_fd[i][1]);
		free_group(tmp);
		tmp = tmp->next;
		i++;
		pip->counter--;
	}
	status = 0;
	while (data->num_elems-- >= 0)
		waitpid(-1, &status, 0);
	free(pip);
}
