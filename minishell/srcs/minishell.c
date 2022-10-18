/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:54:26 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:47:31 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_current_shlvl(t_info *struktura)
{
	t_env	*head;
	int		i;

	head = struktura->envp_list;
	while (head)
	{
		i = ft_strlen(head->key);
		if (ft_strncmp_mod("SHLVL", head->key, i))
		{
			free(head->value);
			head->value = ft_itoa(ft_atoi(head->value) + 1);
			break ;
		}
		head = head->next;
	}
}

int	search_pipe(char *str, int *f)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (*f == 0)
	{
		while (str[i] != '\0')
		{
			if (str[i] == '|')
				flag = 1;
			else if (str[i] != ' ')
				flag = 0;
			i++;
		}
	}
	*f = 1;
	return (flag);
}

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
