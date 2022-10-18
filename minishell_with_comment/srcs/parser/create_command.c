/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:37:58 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/09 23:37:58 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**d_duplicate(char **line)
{
	char	**str;
	int		i;

	i = 0;
	str = NULL;
	if (!line)
		return (NULL);
	while (line && line[i])
		i++;
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		str[i] = ft_strdup(line[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	*join_symbol(char **line, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	if ((*line))
		len = ft_strlen((*line));
	else
		len = 0;
	str = malloc(sizeof(char) * len + 2);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = (*line)[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = '\0';
	*line = free_single((void **)line);
	return (str);
}

int	create_command_3(char	**line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if (space((*line)[i]) == 1)
			break ;
		i++;
	}
	if (!(*line)[i] || (*line)[i] == ';'
		|| (*line)[i] == '|')
		return (-1);
	return (1);
}

char	*create_command_2(char **line, int *flag)
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		quotes(flag, *(*line));
		cmd = join_symbol(&cmd, *(*line));
		if ((*flag == 0 && ((*(*line) == '|' && *((*line) + 1) != '|')))
			|| *(*line) == '\0')
			return (cmd);
		(*line)++;
	}
	return (cmd);
}

char	**create_command(char *line)
{
	int		i;
	int		flag;
	char	**cmd;
	char	*temp;
	char	**arr;

	i = -1;
	cmd = NULL;
	flag = 0;
	while (*line)
	{
		temp = create_command_2(&line, &flag);
		arr = d_duplicate(cmd);
		cmd = free_double((void **)cmd);
		cmd = join_double(arr, temp);
		temp = free_single((void **)&temp);
		arr = free_double((void **)arr);
		if (!(*line))
			break ;
		line++;
	}
	while (cmd[++i])
		if (create_command_3(&(cmd[i])) == -1 && cmd[i + 1] != NULL)
			return (free_double((void **)cmd));
	return (cmd);
}
