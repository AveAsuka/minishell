/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:07:14 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:14:06 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	a;

	a = 0;
	if (n < 0)
	{
		a++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		a++;
	}
	if (!a)
		return (1);
	return (a);
}

char	*ft_itoa(int n)
{
	int		a;
	char	*p;

	a = ft_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	p = (char *)malloc((a + 1) * sizeof(char));
	if (p == 0)
		return (0);
	if (n < 0)
	{
		p[0] = '-';
		n = -n;
	}
	if (!n)
		p[0] = '0';
	p[a--] = '\0';
	while (n != 0)
	{
		p[a] = n % 10 + '0';
		a--;
		n = n / 10;
	}
	return (p);
}
