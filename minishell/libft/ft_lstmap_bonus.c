/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:31:38 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:15:35 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*a;

	if (!f)
		return (0);
	p = 0;
	while (lst)
	{
		a = ft_lstnew((*f)(lst->content));
		if (!a)
		{
			ft_lstclear(&p, del);
			return (0);
		}
		ft_lstadd_back(&p, a);
		lst = lst->next;
	}
	return (p);
}
