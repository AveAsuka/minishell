/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:34:20 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/10 23:34:20 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(char c)
{
	if (c == '\n' || c == '\t'\
	|| c == '\v' || c == '\f' \
	|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	check_first_pipe(t_info *shell)
{
	int	i;

	i = 0;
	while (shell->cmd_line[i] != '\0')
	{
		if (shell->cmd_line[i] == ';')
		{
			print_error(2, NULL, 258, shell);
			return (0);
		}
		i++;
	}
	i = 0;
	while (shell->cmd_line[i] != '\0' && shell->cmd_line[i] == ' ')
		i++;
	if (shell->cmd_line[i] == '|')
	{
		print_error(1, NULL, 258, shell);
		return (0);
	}
	else
		return (1);
}

int	find_double_pipe(t_info *shell)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (shell->cmd_line[i] != '\0')
	{
		if (shell->cmd_line[i] == '|')
		{
			flag = 1;
			i++;
		}
		while (flag == 1 && shell->cmd_line[i] == ' ')
			i++;
		if (shell->cmd_line[i] == '|' && flag == 1)
		{
			print_error(1, NULL, 258, shell);
			return (-1);
		}
		else
			flag = 0;
		i++;
	}
	return (0);
}

void	print_error(int flag, char *cmd, int code, t_info *shell)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
		ft_putstr_fd(cmd, 2);
	if (flag == 1)
		ft_putstr_fd("syntax error near unexpected token `|'", 2);
	if (flag == 2)
		ft_putstr_fd("syntax error near unexpected token `;'", 2);
	if (flag == 3)
		ft_putstr_fd("Command not found", 2);
	if (flag == 4)
		ft_putstr_fd("syntax error near unexpected token `quote'", 2);
	if (flag == 5)
		ft_putstr_fd("syntax error near unexpected token `newline'", 2);
	if (flag == 6)
		ft_putstr_fd("syntax error near unexpected token `<'", 2);
	if (flag == 7)
		ft_putstr_fd("syntax error near unexpected token `>'", 2);
	if (flag == 8)
		ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	shell->command_result = code;
}
