/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_lst_mod.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:12:31 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 19:13:17 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast_mod(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_env	*ft_lstnew_mod_two(char *content)
{
	t_env	*d;

	d = (t_env *)malloc(sizeof(t_env));
	if (!d)
		return (NULL);
	find_key(content, d);
	d->next = NULL;
	return (d);
}

t_env	*ft_lstnew_mod(char *content)
{
	t_env	*d;

	d = (t_env *)malloc(sizeof(t_env));
	if (!d)
		return (NULL);
	printf("Content is %s\n", content);
	find_key_value(content, d);
	d->next = NULL;
	return (d);
}

void	ft_lstadd_back_mod(t_env *lst, t_env *new)
{
	t_env	*buf;

	if (!(lst))
	{
		lst = new;
		return ;
	}
	buf = ft_lstlast_mod(lst);
	buf->next = new;
}

int	ft_lstsize_mod(t_env *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
