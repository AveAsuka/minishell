/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:41 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 17:45:46 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_norme(char *limiter)
{
	int		t_outfile;
	char	*buff;
	char	*tmp;

	t_outfile = 1;
	buff = NULL;
	tmp = NULL;
	t_outfile = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (t_outfile == -1)
		printf("Error!\n");
	tmp = readline("> ");
	while (tmp && ft_strncmp(tmp, limiter, ft_strlen(limiter)))
	{
		buff = ft_strjoin(tmp, "\n\0");
		write(t_outfile, buff, ft_strlen(buff));
		free(buff);
		free(tmp);
		tmp = readline("> ");
	}
	free(tmp);
	close(t_outfile);
}

void	one_cmd_norme(t_info *data)
{
	data->group_head = (t_cmd *)malloc(sizeof(t_cmd));
	if (data->group_head == NULL)
		ft_error("malloc error\n", data);
	signal(SIGINT, handler_two);
	signal(3, SIG_IGN);
	data->command_result = 0;
	data->group_head->pid = fork();
	if (data->group_head->pid == -1)
		ft_perror_exit_child("", 1);
	if (data->group_head->pid == 0)
	{
		signal(2, SIG_DFL);
		signal(3, SIG_DFL);
		if (check_builtins(data, data->cmd->arg) == 100)
			execve_action(data);
	}
}
