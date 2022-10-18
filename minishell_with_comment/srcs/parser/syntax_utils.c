/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:43:21 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/07 15:26:39 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

void	norme_hack(t_info *shell, char c)
{
	if (c == '|')
		print_error(1, NULL, 258, shell);
	else if (c == '\0')
		print_error(5, NULL, 258, shell);
	else if (c == ';')
		print_error(2, NULL, 258, shell);
}

int	syntax_check(t_info *shell, char *line)
{
	int	flag;
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
			flag = 1;
		if (flag == 1)
		{
			while (space(line[i]) || is_redir(line[i]))
				i++;
			if (line[i] == '|' || line[i] == '\0' || line[i] == ';')
			{
				norme_hack(shell, line[i]);
				return (-1);
			}
			else
				flag = 0;
		}
		else
			flag = 0;
	}
	return (0);
}

void	redir_change(t_info *shell, char *line)
{
	free(shell->cmd_line);
	shell->cmd_line = ft_strdup(line);
}

int	redir_check(t_info *shell, char *line)
{
	int		i;
	int		flag;
	char	*str;

	i = -1;
	flag = 0;
	str = NULL;
	while (line[++i] != '\0')
		if (line[i] == '<')
			flag++;
	if (flag == 3)
	{
		i = -1;
		while (line[++i] != '<')
			str = join_symbol(&str, line[i]);
		i++;
		while (line[i++] != '\0')
			str = join_symbol(&str, line[i]);
		redir_change(shell, str);
		free(str);
		return (0);
	}
	else
		print_error(6, NULL, 258, shell);
	return (-1);
}
