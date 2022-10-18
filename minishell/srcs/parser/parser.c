/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:03:47 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:12:37 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(t_info *shell)
{
	int	i;

	i = 0;
	while (space(shell->cmd_line[i]) == 1)
		i++;
	if (!shell->cmd_line[i])
		return (-1);
	return (1);
}

int	check_unclosed_quotes(char *line, t_info *shell)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && quote == 0)
			quote = 1;
		else if (line[i] == '\"' && quote == 0)
			quote = 2;
		else if (line[i] == '\'' && quote == 1)
			quote = 0;
		else if (line[i] == '\"' && quote == 2)
			quote = 0;
		i++;
	}
	if (quote != 0)
		print_error(4, NULL, 258, shell);
	return (quote);
}

int	check_wrong_redirect(char *line, int *redir)
{
	int	i;
	int	flag;
	int	num;

	i = 0;
	num = 0;
	flag = 0;
	while (line[i])
	{
		quotes(&flag, line[i]);
		if (check_redirect(line[i], flag) < 0)
		{
			num++;
			if (line[i] == '>')
				*redir = 3;
			else if (line[i] == '<')
				*redir = 4;
		}
		else
			num = 0;
		if (num == 3)
			return (-1);
		i++;
	}
	return (1);
}

int	first_check(t_info *shell)
{
	int	is_quote;
	int	redir;

	is_quote = 0;
	is_quote = check_unclosed_quotes(shell->cmd_line, shell);
	if (is_quote != 0)
		return (-1);
	if (check_wrong_redirect(shell->cmd_line, &redir) == -1)
	{
		if (redir == 3)
			print_error(7, NULL, 258, shell);
		else if (redir == 4)
			if (redir_check(shell, shell->cmd_line) == 0)
				return (0);
		return (-1);
	}
	return (0);
}

int	parser(t_info *shell)
{
	char	**cmd;

	cmd = NULL;
	if (is_space(shell) == -1)
		return (-1);
	if (first_check(shell) == -1)
		return (3);
	if (find_double_pipe(shell) == -1)
		return (4);
	cmd = create_command(shell->cmd_line);
	if (!cmd)
	{
		free_double((void **)cmd);
		return (-1);
	}
	if (build_cmd(cmd, shell) == -1)
	{
		free_double((void **)cmd);
		return (-1);
	}
	free_double((void **)cmd);
	return (0);
}
