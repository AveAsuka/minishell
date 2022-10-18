/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:33:19 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:16:17 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	a;
	char	*d;
	char	*s;

	a = 0;
	if (dst == 0 && src == 0)
		return (dst);
	s = (char *)src;
	d = dst;
	while (a < n)
	{
		d[a] = s[a];
		a++;
	}
	return (d);
}
