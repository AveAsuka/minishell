/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:51:25 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 18:45:07 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_old_pwd(t_env *pwd_v, t_env *old_pwd)
{
	free(old_pwd->value);
	old_pwd->value = copy_char(pwd_v->value);
}

void	ft_cd_error(char *arr)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arr, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	find_norme_3(t_info *st, t_env *previous, t_env *env_current, int j)
{
	if (j == 0)
	{
		st->envp_list = delete_knot(env_current);
		env_current = st->envp_list;
	}
	else
		env_current = delete_knot(env_current);
	previous->next = env_current;
	st->envp_f = 0;
}

void	find_norme(t_env *env_current, char *stroka, int i, t_info *st)
{
	int		j;
	t_env	*previous;

	j = 0;
	previous = st->envp_list;
	while (env_current)
	{
		if (ft_strncmp_mod(stroka, env_current->key, i))
			find_norme_3(st, previous, env_current, j);
		else
		{
			previous = env_current;
			env_current = env_current->next;
			j++;
		}
	}
}

void	find_norme_2(t_env *ex_l_current, char *stroka, int i, t_info *st)
{
	t_env	*previous;
	int		j;

	j = 0;
	previous = st->export_list_head;
	while (ex_l_current)
	{
		if (ft_strncmp_mod(stroka, ex_l_current->key, i))
		{
			if (j == 0)
			{
				st->export_list_head = delete_knot(ex_l_current);
				ex_l_current = st->export_list_head;
			}
			else
				ex_l_current = delete_knot(ex_l_current);
			previous->next = ex_l_current;
		}
		else
		{
			previous = ex_l_current;
			ex_l_current = ex_l_current->next;
			j++;
		}
	}
}
