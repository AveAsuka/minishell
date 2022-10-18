/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:15:05 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:09:40 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_new_norme(t_env *tmp, char *a, int l, int i)
{
	int	r;
	int	j;

	j = 0;
	r = 0;
	while (l > j)
	{
		if (j > i)
		{
			tmp->value[r] = a[j];
			r++;
		}
		j++;
	}
}

int	duplicate_norme(t_env *tmp, char *a, int k, char *str)
{
	int	j;
	int	i;

	i = ft_strlen(a);
	j = 0;
	while (tmp)
	{
		if (ft_strncmp_mod(a, tmp->key, i) && k == 1)
		{
			edit_value(tmp, str);
			j = j + 2;
			break ;
		}
		tmp = tmp->next;
	}
	return (j);
}

int	analiz_norme(int flag, char *str, int i, int find_equally)
{
	if (flag == 15)
	{
		if ((str[i] >= '!' && str[i] <= '-') || \
					(str[i] >= ';' && str[i] <= '<') || \
						(str[i] >= '>' && str[i] <= '@') || \
							(str[i] >= '[' && str[i] <= '^') || \
								(str[i] >= '{' && str[i] <= '~'))
			return (2);
		return (0);
	}
	else if (flag == 10)
	{
		if (i == 2 && find_equally == 1)
			return (3);
		if (i != 0 && find_equally == 1)
			return (4);
		if (i == 0 && find_equally == 1)
			return (1);
		return (0);
	}
	return (0);
}

void	built_export(t_info *struktura, char **stroka)
{
	if (stroka[0] && !stroka[1])
		export_alph_find(struktura->export_list_head);
	else
		export_analiz(struktura, stroka);
	struktura->command_result = 0;
}
