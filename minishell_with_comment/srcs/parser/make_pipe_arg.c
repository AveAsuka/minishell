/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 08:09:42 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/13 17:07:51 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**concat_arg(char	**temp, char **str)
{
	int		i;
	char	**res;

	i = 0;
	while (temp && temp[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (temp && temp[i])
	{
		res[i] = ft_strdup(temp[i]);
		i++;
	}
	res[i++] = ft_strdup(*str);
	res[i] = NULL;
	temp = free_double((void **)temp);
	return (res);
}

char	**make_arg(char	**cmd, t_cmd *temp)
{
	int		i;
	char	**res;
	char	*str;

	i = -1;
	res = NULL;
	str = NULL;
	if (temp->path)
		str = ft_strjoin(temp->path, temp->cmd);
	else if (temp->cmd)
		str = ft_strdup(temp->cmd);
	res = concat_arg(res, &str);
	str = free_single((void **)&str);
	while ((*cmd)[++i])
	{
		while (space((*cmd)[i]) == 1)
			i++;
		str = get_elem(cmd, &i);
		res = concat_arg(res, &str);
		str = free_single((void **)&str);
		if (!(*cmd)[i])
			break ;
	}
	return (res);
}

char	*make_pipe(char **cmd)
{
	int		i;
	int		flag;
	char	*res;
	int		redir_type;

	i = -1;
	res = NULL;
	flag = 0;
	while ((*cmd)[++i])
	{
		quotes(&flag, (*cmd)[i]);
		if (flag != 0)
			continue ;
		redir_type = get_redir_type(&((*cmd)[i]));
		if (redir_type == 1 || redir_type == 2)
			res = take_redirect(redir_type, &i, cmd);
		if (!(*cmd)[i])
			break ;
	}
	if (!res)
		res = NULL;
	return (res);
}
