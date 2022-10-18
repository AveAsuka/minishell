/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:38:14 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:16:30 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int	a;

	if (n == 0 || src == dst)
		return (dst);
	if (dst > src)
	{
		a = (int)n - 1;
		while (a >= 0)
		{
			*(char *)(dst + a) = *(char *)(src + a);
			a--;
		}
	}
	else
	{
		a = 0;
		while (a < (int)n)
		{
			*(char *)(dst + a) = *(char *)(src + a);
			a++;
		}
	}
	return (dst);
}
