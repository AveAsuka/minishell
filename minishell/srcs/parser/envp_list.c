/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:06:09 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/19 17:41:23 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Чутка переписала либовские функции под новый список.
Можно будет переместить в envp.c
*/

t_env	*list_last(t_env *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	list_add_front(t_env **lst, t_env *new)
{
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	list_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new != NULL)
	{
		last = list_last(*lst);
		if (last == NULL)
			list_add_front(lst, new);
		else
			last->next = new;
	}
}
