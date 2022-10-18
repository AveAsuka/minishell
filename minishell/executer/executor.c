/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:27:01 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 17:51:11 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_info *data, char **stroka)
{
	if (ft_strncmp_mod("echo", stroka[0], 4) \
		|| ft_strncmp_mod("ECHO", stroka[0], 4))
		built_echo(data, data->cmd->arg);
	else if (ft_strncmp_mod("pwd", stroka[0], 3) \
		|| ft_strncmp_mod("PWD", stroka[0], 3))
		built_pwd(data);
	else if (ft_strncmp_mod("env", stroka[0], 3) \
		|| ft_strncmp_mod("ENV", stroka[0], 3))
		built_env(data);
	else
		return (100);
	return (1);
}

int	only_parent(t_info *data)
{
	if (ft_strncmp_mod("export", data->stroka[0], 6)
		|| ft_strncmp_mod("EXPORT", data->stroka[0], 6))
		built_export(data, data->cmd->arg);
	else if (ft_strncmp_mod("unset", data->stroka[0], 5) \
		|| ft_strncmp_mod("UNSET", data->stroka[0], 5))
		data = built_unset(data, data->cmd->arg);
	else if (ft_strncmp_mod("cd", data->stroka[0], 2) \
		|| ft_strncmp_mod("CD", data->stroka[0], 2))
		built_cd(data, data->cmd->arg);
	else if (ft_strncmp_mod("exit", data->stroka[0], 4) \
		|| ft_strncmp_mod("EXIT", data->stroka[0], 4))
		built_exit(data);
	else
		return (0);
	return (1);
}

void	check_sig(int status, t_info *data)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			data->command_result = 131;
			ft_putstr_fd("Quit: 3\n", 1);
		}
		else if (WTERMSIG(status) == 2)
		{
			data->command_result = 132;
			ft_putstr_fd("\n", 1);
		}
	}
}

void	one_cmd(t_info	*data)
{
	int	tmpin;
	int	tmpout;
	int	check;
	int	status;

	tmpin = dup(0);
	tmpout = dup(1);
	redirect_enumeration(data->cmd, tmpin);
	check = only_parent(data);
	if (check == 0)
		one_cmd_norme(data);
	if (dup2 (tmpin, 0) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
	if (dup2 (tmpout, 1) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
	close (tmpin);
	close (tmpout);
	if (check == 0 && waitpid (-1, &status, 0) == -1)
	{
		printf("waitpid error\n");
		ft_perror_exit_child("", 1);
	}
	check_sig(status, data);
}

void	executor(t_info *data)
{
	copy_in_export(data, data->envp_list);
	data->stroka = ft_split(data->cmd->cmd, '/');
	if (data->cmd->pipe)
		pipe_action(data);
	else
		one_cmd(data);
	free_and_new_start(data);
}
