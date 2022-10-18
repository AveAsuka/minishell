/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:09:21 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:20:18 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_info *shell, char **envp, int i)
{
	signal(SIGINT, handler_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	shell->exit_f = 0;
	shell->envp_f = 1;
	shell->command_result = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
			exit(2);
		i++;
	}
	shell->envp[i] = NULL;
	shell->envp_list = NULL;
	if (get_envp_list(shell) != 0)
		return (-1);
	return (0);
}

char	*ft_readline(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

void	ctrl_d(t_info *shell)
{
	free(shell->cmd_line);
	write(1, "exit\n", 5);
	rl_clear_history();
	exit(32);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	shell;

	if (init(&shell, envp, 0) != 0)
		exit(0);
	find_current_shlvl(&shell);
	env_reverse_convert(&shell);
	(void)argc;
	(void)argv;
	while (shell.exit_f == 0)
	{
		shell.cmd_line = ft_readline("minishell>> ");
		if (shell.cmd_line == NULL)
			ctrl_d(&shell);
		if (shell.cmd_line[0])
		{
			if (minishell(&shell) != 0)
				exit(2);
		}
		else
			free(shell.cmd_line);
	}
	return (0);
}
