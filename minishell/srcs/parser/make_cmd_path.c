/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:24:54 by lbrianna          #+#    #+#             */
/*   Updated: 2022/08/19 11:24:54 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_info *shell)
{
	char	**path;
	t_env	*temp;

	temp = shell->envp_list;
	if (!(shell->envp))
		return (NULL);
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->key, "PATH=", ft_strlen(temp->key)) == 0)
		{
			path = ft_split(temp->value, ':');
			break ;
		}
		temp = temp->next;
	}
	if (temp->next == NULL)
		return (NULL);
	return (path);
}

char	*make_env_path(char *cmd, t_info *shell)
{
	int		i;
	char	**path;
	char	*s1;
	char	*s2;

	path = get_path(shell);
	i = -1;
	while (cmd && path && path[++i])
	{
		s1 = ft_strjoin(path[i], "/");
		s2 = ft_strjoin(s1, cmd);
		if (access(s2, F_OK) == 0)
		{
			free_single((void **)&s2);
			break ;
		}
		free_single((void **)&s1);
		free_single((void **)&s2);
	}
	free_double((void **)path);
	if (path == NULL)
		return (NULL);
	return (s1);
}

char	*make_path(char **cmd)
{
	int		i;
	char	*res;
	char	*str;
	char	c;

	i = ft_strlen(*cmd);
	res = NULL;
	while (--i >= 0)
		if ((*cmd)[i] == '/')
			break ;
	if (i >= 0)
	{
		c = (*cmd)[i + 1];
		(*cmd)[i + 1] = '\0';
		res = ft_strdup(*cmd);
		(*cmd)[i + 1] = c;
		str = ft_strdup(&((*cmd)[i + 1]));
		(*cmd) = free_single((void **)cmd);
		(*cmd) = str;
	}
	return (res);
}

char	*make_cmd(char **cmd)
{
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	while ((*cmd)[++i])
	{
		if (space((*cmd)[i]) == 1)
			continue ;
		line = get_elem(cmd, &i);
		break ;
	}
	return (line);
}
