/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:59:18 by lbrianna          #+#    #+#             */
/*   Updated: 2022/08/19 10:59:18 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_type(char *line)
{
	if (line[0] == '>' && line[1] == '>')
		return (5);
	else if (line[0] == '<' && line[1] == '<')
		return (6);
	else if (line[0] == '|')
		return (1);
	else if (line[0] == ';')
		return (2);
	else if (line[0] == '>')
		return (3);
	else if (line[0] == '<')
		return (4);
	return (0);
}

char	*take_redirect(int type, int *i, char **cmd)
{
	if (type == 5 || type == 6)
	{
		(*cmd)[(*i)++] = ' ';
		(*cmd)[(*i)++] = ' ';
	}
	else
		(*cmd)[(*i)++] = ' ';
	if (type == 5)
		return (ft_strdup(">>"));
	else if (type == 6)
		return (ft_strdup("<<"));
	else if (type == 3)
		return (ft_strdup(">"));
	else if (type == 4)
		return (ft_strdup("<"));
	else if (type == 1)
		return (ft_strdup("|"));
	else if (type == 2)
		return (ft_strdup(";"));
	return (0);
}

int	size_redir(t_redir *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	else
	{
		while (str[i].type != NULL)
			i++;
	}
	return (i);
}
