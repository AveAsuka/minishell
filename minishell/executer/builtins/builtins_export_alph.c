/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_alph.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:55:23 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 17:34:09 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_alph_print(t_env *ex_l)
{
	t_env	*head;
	int		j;

	head = ex_l;
	j = ft_lstsize_mod(ex_l);
	while (j > 0)
	{
		while (ex_l)
		{
			if (j == ex_l->num)
			{
				if (ex_l->value == NULL)
					printf ("declare -x %s\n", ex_l->key);
				else
					printf ("declare -x %s=\"%s\"\n", ex_l->key, ex_l->value);
				j--;
			}
			ex_l = ex_l->next;
		}
		ex_l = head;
	}
}

t_env	*export_norme_2(t_env *ex_l, t_env *current)
{
	while (ex_l)
	{
		if (ex_l->num == 0)
		{
			current = ex_l;
			break ;
		}
		ex_l = ex_l->next;
	}
	return (current);
}

void	export_norme(t_env *ex_l, t_env *current, int num, t_env *head)
{
	int		j;

	j = ft_lstsize_mod(ex_l);
	while (j > 0)
	{
		while (ex_l)
		{
			if (ex_l->key[0] > current->key[0] \
					&& ex_l->num == 0 && current->num == 0)
				current = ex_l;
			ex_l = ex_l->next;
		}
		current->num = num;
		num++;
		j--;
		ex_l = head;
		current = export_norme_2(ex_l, current);
	}
}

void	export_alph_find(t_env *ex_l)
{
	t_env	*head;
	t_env	*current;

	head = ex_l;
	current = ex_l;
	while (ex_l)
	{
		ex_l->num = 0;
		ex_l = ex_l->next;
	}
	ex_l = head;
	export_norme(ex_l, current, 1, head);
	ex_l = head;
	export_alph_print(ex_l);
}

// void	export_norme(int j, t_env *ex_l, t_env *current, t_env *head)
// {
// 	while (j > 0)
// 	{
// 		while (ex_l)
// 		{
// 			if (ex_l->key[0] > current->key[0] 
// 					&& ex_l->num == 0 && current->num == 0)
// 				current = ex_l;
// 			ex_l = ex_l->next;
// 		}
// 		current->num = num;
// 		num++;
// 		j--;
// 		ex_l = head;
// 		while (ex_l)
// 		{
// 			if (ex_l->num == 0)
// 			{
// 				current = ex_l;
// 				break ;
// 			}
// 			ex_l = ex_l->next;
// 		}
// 	}
// }

// void	export_alph_find(t_env *ex_l)
// {
// 	int		num;
// 	t_env	*head;
// 	t_env	*current;
// 	int		j;

// 	num = 1;
// 	head = ex_l;
// 	current = ex_l;
// 	j = ft_lstsize_mod(ex_l);
// 	while (ex_l)
// 	{
// 		ex_l->num = 0;
// 		ex_l = ex_l->next;
// 	}
// 	ex_l = head;
// 	// export_norme(j , ex_l, current, 1, head);
// 	while (j > 0)
// 	{
// 		while (ex_l)
// 		{
// 			if (ex_l->key[0] > current->key[0] 
// 					&& ex_l->num == 0 && current->num == 0)
// 				current = ex_l;
// 			ex_l = ex_l->next;
// 		}
// 		current->num = num; // 25 line
// 		num++;
// 		j--;
// 		ex_l = head;
// 		while (ex_l)
// 		{
// 			if (ex_l->num == 0)
// 			{
// 				current = ex_l;
// 				break ;
// 			}
// 			ex_l = ex_l->next;
// 		}
// 	}
// 	ex_l = head;
// 	export_alph_print(ex_l);
// }