/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:12:34 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:12:17 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	a;

	a = 0;
	p = (void *)malloc(count * size);
	if (!p)
		return (NULL);
	while (a < count * size)
	{
		((unsigned char *)p)[a] = '\0';
		a++;
	}
	return (p);
}
