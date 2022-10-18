/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:47:16 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 16:52:41 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_current_pwd(t_info *struktura)
{
	t_env	*head;
	int		i;

	head = struktura->envp_list;
	while (head)
	{
		i = ft_strlen(head->key);
		if (ft_strncmp_mod("PWD", head->key, i))
			return (head);
		head = head->next;
	}
	return (head);
}

t_env	*find_old_pwd(t_info *struktura)
{
	t_env	*head;
	int		i;

	head = struktura->envp_list;
	while (head)
	{
		i = ft_strlen(head->key);
		if (ft_strncmp_mod("OLDPWD", head->key, i))
			return (head);
		head = head->next;
	}
	return (head);
}

void	pwds_edit(t_env *current_pwd, t_env *old_pwd)
{
	char	tmp[1024];

	edit_old_pwd(current_pwd, old_pwd);
	free(current_pwd->value);
	getcwd(tmp, 1024);
	current_pwd->value = copy_char(tmp);
}

int	ft_without_argument(t_env *envp_l, char *path, t_info *struktura)
{
	t_env	*tmp;
	t_env	*current_pwd;

	tmp = envp_l;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->key, 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL && ft_strncmp("HOME", tmp->key, 5) == 0)
	{
		path = tmp->value;
		chdir(path);
	}
	else
		return (1);
	current_pwd = find_current_pwd(struktura);
	current_pwd->value = path;
	return (0);
}

void	built_cd(t_info *struktura, char **stroka)
{
	t_env	*current_pwd;
	t_env	*old_pwd;
	int		result;
	char	*path;

	path = NULL;
	current_pwd = find_current_pwd(struktura);
	old_pwd = find_old_pwd(struktura);
	if (stroka[1] == NULL)
		result = ft_without_argument(struktura->envp_list, path, struktura);
	else
	{
		result = chdir(stroka[1]);
		if (result == -1)
			ft_cd_error(stroka[1]);
	}
	if (result == 0)
		pwds_edit(current_pwd, old_pwd);
	struktura->command_result = 0;
}
