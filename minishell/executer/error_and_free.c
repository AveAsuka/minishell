/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:09:13 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:12:12 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_new_start(t_info *data)
{
	int	i;

	i = 0;
	if (data->stroka)
	{
		while (data->stroka[i])
		{
			free(data->stroka[i]);
			i++;
		}
		free(data->stroka);
		data->stroka = NULL;
	}
	unlink(".here_doc");
}

void	ft_error(char *error_message, t_info *data)
{
	ft_putstr_fd(error_message, 2);
	data->command_result = 1;
	exit(0);
}

void	ft_perror_exit_child(char *str, int error)
{
	if (str != NULL)
		perror(str);
	exit(error);
}

void	ft_perror_cmd_nf(int error, t_info *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*(data->cmd->arg), 2);
	ft_putstr_fd(": command not found\n`", 2);
	exit(error);
}
