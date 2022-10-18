/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:50:52 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/11 23:50:52 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*build_redirect(t_redir **temp, char *redir, char *file)
{
	int		i;
	t_redir	*res;

	i = size_redir(*temp);
	res = malloc(sizeof(t_redir) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while ((*temp) && (*temp)[i].type)
	{
		res[i].type = (*temp)[i].type;
		res[i].file = (*temp)[i].file;
		i++;
	}
	res[i].file = ft_strdup(file);
	res[i].type = ft_strdup(redir);
	i++;
	res[i].file = NULL;
	res[i].type = NULL;
	free_single((void **)temp);
	return (res);
}

char	*get_elem(char **cmd, int *i)
{
	int		flag;
	char	*str;

	flag = 0;
	str = NULL;
	while (space((*cmd)[*i]) == 1)
		(*i)++;
	while ((*cmd)[*i])
	{
		quotes(&flag, (*cmd)[*i]);
		if (!(*cmd)[*i] || (flag == 0 && (space((*cmd)[*i]) == 1
			|| get_redir_type(&(*cmd)[*i]) > 0)))
			return (str);
		else
		{
			str = join_symbol(&str, (*cmd)[*i]);
			(*cmd)[*i] = ' ';
		}
		(*i)++;
	}
	return (str);
}

int	make_redir_2(t_redir **temp, char **cmd, int *i)
{
	int		redirect_type;
	char	*redir;
	char	*file;

	redirect_type = get_redir_type(&(*cmd)[*i]);
	if (redirect_type < 3)
		return (-1);
	redir = take_redirect(redirect_type, i, cmd);
	file = get_elem(cmd, i);
	*temp = build_redirect(temp, redir, file);
	free_single((void **)&redir);
	free_single((void **)&file);
	return (1);
}

t_redir	*make_redir(char **cmd)
{
	int		i;
	int		flag;
	t_redir	*temp;

	i = -1;
	flag = 0;
	temp = NULL;
	while ((*cmd)[++i])
	{
		quotes(&flag, (*cmd)[i]);
		if (flag == 0)
		{
			if (make_redir_2(&temp, cmd, &i) == -1)
				continue ;
			if (!(*cmd)[i])
				break ;
		}
	}
	return (temp);
}
