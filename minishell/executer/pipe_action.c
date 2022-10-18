/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:13:41 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:11:19 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_close_maza_faka(t_info *data, int n_child, t_cmd *tmp)
{
	int	i;
	int	j;

	i = 0;
	(void)tmp;
	while (i != (data->num_elems - 1))
	{
		j = 0;
		while (j != 2)
		{
			if (n_child != i && n_child - 1 != i)
				close (data->pipe_fd[i][j]);
			j++;
		}
		i++;
	}
}

void	pipe_action_3(t_info *data, t_pipe *pip, t_cmd *tmp, int i)
{
	int	ret;
	int	red_final;

	ret = fork();
	if (ret == -1)
		ft_perror_exit_child("", 1);
	if (ret == 0)
	{
		red_final = redirect_enumeration(tmp, pip->tmpin);
		if (pip->num_elems_flag == pip->counter + 1)
			first_entry(data, tmp, i, red_final);
		else if (pip->num_elems_flag == 1)
			last_entry(data, tmp, i, red_final);
		else if (pip->num_elems_flag != 1)
			routine(data, tmp, i, red_final);
		if (only_parent(data) == 1)
			exit(0);
		else if (check_builtins(data, tmp->arg) == 100)
			execve_action_many_cmd(data, tmp);
	}
}

void	pipe_action_2(t_info *data, t_pipe *pip, t_cmd *tmp)
{
	int	i;

	pip->num_elems_flag = data->num_elems;
	pip->counter = data->num_elems - 1;
	i = 0;
	while (pip->num_elems_flag != 0)
	{
		do_stroka(data, tmp);
		pipe_action_3(data, pip, tmp, i);
		tmp = tmp->next;
		pip->num_elems_flag--;
		i++;
	}
	dup2(pip->tmpin, 0);
	dup2(pip->tmpout, 1);
	close(pip->tmpin);
	close(pip->tmpout);
	close_pipe(pip, tmp, data);
}

void	pipe_action(t_info *data)
{
	t_cmd	*tmp;
	t_pipe	*pip;
	int		i;

	tmp = data->cmd;
	pip = malloc(sizeof(t_pipe *));
	if (!pip)
		ft_error("Malloc error\n", data);
	pip->tmpout = dup(1);
	pip->tmpin = dup(0);
	pip->counter = data->num_elems - 1;
	i = 0;
	data->pipe_fd = malloc(sizeof(int *) * pip->counter);
	if (data->pipe_fd == NULL)
		ft_error("malloc error\n", data);
	while (pip->counter-- != 0)
	{
		data->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (data->pipe_fd[i] == NULL)
			ft_error("malloc error\n", data);
		if (pipe(data->pipe_fd[i]) == -1)
			ft_error("pipe error\n", data);
		i++;
	}
	pipe_action_2(data, pip, tmp);
}
