/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:55:18 by lbrianna          #+#    #+#             */
/*   Updated: 2022/08/19 11:46:25 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_2(char **str, int i)
{
	char	c;
	char	*s1;
	char	*s2;

	c = (*str)[i];
	(*str)[i] = '\0';
	s1 = ft_strdup((*str));
	(*str)[i] = c;
	s2 = ft_strjoin(s1, &((*str)[i + 1]));
	*str = free_single((void **)str);
	*str = s2;
}

int	erase_quotes(char **str)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	if (!(*str))
		return (1);
	while ((*str)[++i])
	{
		quotes(&flag, (*str)[i]);
		if (flag == 2 && (*str)[i] == '\'')
			continue ;
		else if (flag == 1 && (*str)[i] == '\"')
			continue ;
		else if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			erase_2(str, i);
			i--;
		}
	}
	return (1);
}

int	check_redir_quotes(t_redir *red, t_info *shell)
{
	int	i;

	i = -1;
	if (!red)
		return (1);
	while (red[++i].type)
	{
		if (ft_strncmp(red[i].type, "<<", 3) == 0)
			continue ;
		check_command(&(red[i].type), shell);
		check_command(&(red[i].file), shell);
		erase_quotes(&(red[i].type));
		erase_quotes(&(red[i].file));
	}
	return (1);
}

int	check_argument(char **arg, t_info *shell)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		check_command(&(arg[i]), shell);
		erase_quotes(&(arg[i]));
	}
	return (1);
}

int	check_all_quotes(t_cmd *cmd, t_info *shell)
{
	if (cmd->cmd)
	{
		check_command(&cmd->cmd, shell);
		erase_quotes(&cmd->cmd);
	}
	if (!cmd->path)
	{
		cmd->path = free_single((void **)&(cmd->path));
		cmd->path = make_path(&cmd->cmd);
		erase_quotes(&cmd->path);
	}
	if (cmd->arg)
		check_argument(cmd->arg, shell);
	if (cmd->redir)
		check_redir_quotes(cmd->redir, shell);
	return (0);
}
