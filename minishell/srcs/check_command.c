/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:26:48 by lbrianna          #+#    #+#             */
/*   Updated: 2022/08/31 16:15:03 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *cmd, int *i)
{
	char	*str;

	str = NULL;
	(*i)++;
	while ((cmd[*i] >= 'A' && cmd[*i] <= 'Z')
		|| (cmd[*i] >= 'a' && cmd[*i] <= 'z')
		|| (cmd[*i] >= '0' && cmd[*i] <= '9')
		|| cmd[*i] == '_' || cmd[*i] == '?')
	{
		str = join_symbol(&str, cmd[*i]);
		(*i)++;
	}
	return (str);
}

char	*ft_dollar_zero(char *cmd)
{
	char	*str;
	int		i;

	i = 1;
	if (cmd[i] == '0')
	{
		str = ft_strdup("Minishell");
		i++;
	}
	while (cmd[i] != '\0')
	{
		str = join_symbol(&str, cmd[i]);
		i++;
	}
	return (str);
}

char	*get_new_arg(char *cmd, int i, t_info *shell)
{
	char	*res;
	char	*key;
	t_env	*temp;

	temp = shell->envp_list;
	key = get_key(cmd, &i);
	if (key[0] == '0')
		return (ft_dollar_zero(cmd));
	while (temp && temp->key)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key)) == 0)
		{
			res = ft_strdup(temp->value);
			key = free_single((void **)&key);
			return (res);
		}
		temp = temp->next;
	}
	if (key[0] == '?')
		return (question_mark(cmd, shell));
	key = free_single((void **)&key);
	return (NULL);
}

void	change_arg(char **cmd, char *arg, int i)
{
	char	*s1;
	char	*s2;

	(*cmd)[i] = '\0';
	s1 = ft_strdup(*cmd);
	(*cmd)[i] = '$';
	if (arg)
		s2 = ft_strjoin(s1, arg);
	else
		s2 = ft_strdup(s1);
	s1 = free_single((void **)&s1);
	while ((*cmd)[i] && ((*cmd)[i] == '$' || (*cmd)[i] == '_'
		|| ((*cmd)[i] >= 'a' && (*cmd)[i] <= 'z')
		|| ((*cmd)[i] >= '0' && (*cmd)[i] <= '9')
		|| ((*cmd)[i] >= 'A' && (*cmd)[i] <= 'Z')
		|| (*cmd)[i] == '?'))
		i++;
	if ((*cmd)[i])
		s1 = ft_strjoin(s2, &((*cmd)[i]));
	else
		s1 = ft_strdup(s2);
	s2 = free_single((void **)&s2);
	*cmd = free_single((void **)cmd);
	*cmd = s1;
}

int	check_command(char **cmd, t_info *shell)
{
	int		flag;
	int		i;
	char	*arg;

	i = 0;
	flag = 0;
	while ((*cmd)[i])
	{
		quotes(&flag, (*cmd)[i]);
		if ((*cmd)[i] == '$' && (flag == 0 || flag == 2))
		{
			arg = get_new_arg(*cmd, i, shell);
			change_arg(cmd, arg, i);
			arg = free_single((void **)&arg);
			if (!(*cmd)[0])
			{
				(*cmd) = free_single((void **)cmd);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}
