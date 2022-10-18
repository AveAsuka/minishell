/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:35:55 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 15:36:54 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ex_arg(char *stroka)
{
	int	res;
	int	i;

	i = 0;
	res = 1;
	if (stroka[i] == '-' || stroka[i] == '+')
		i++;
	while (stroka[i])
	{
		if (!ft_isdigit(stroka[i]))
			res = -1;
		i++;
	}
	if (i == 20)
		res = -1;
	return (res);
}

void	exit_norme_1(t_info *struktura)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(struktura->cmd->arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	struktura->command_result = 1;
	exit(255);
}

void	exit_norme_2(t_info *struktura)
{
	int		i;
	char	c;

	i = ft_atoi(struktura->cmd->arg[1]);
	c = i;
	ft_putstr_fd("exit\n", 1);
	struktura->command_result = 0;
	exit(c);
}

void	built_exit(t_info *struktura)
{
	int		n;

	n = 0;
	while (struktura->cmd->arg[n])
		n++;
	if (struktura->cmd->arg[1] != NULL)
	{
		if (check_ex_arg(struktura->cmd->arg[1]) == -1)
			exit_norme_1(struktura);
		if (n < 3)
			exit_norme_2(struktura);
		else
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else if (struktura->cmd->arg[1] == NULL)
	{
		struktura->command_result = 0;
		exit(struktura->command_result);
	}
}
