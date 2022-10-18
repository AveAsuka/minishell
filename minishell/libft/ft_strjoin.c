/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:30:15 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:18:47 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	char	*p;

	if (!s1)
		return (0);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	p = (char *)malloc((a + b + 1) * sizeof(char));
	if (p == 0)
		return (0);
	a = 0;
	b = 0;
	while (s1[a])
	{
		p[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		p[a + b] = s2[b];
		b++;
	}
	p[a + b] = '\0';
	return (p);
}
