/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:00:38 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:20:30 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sub(char *p)
{
	p = (char *)malloc(sizeof(char) * 1);
	if (p == 0)
		return (0);
	p[0] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	a;

	if (!s)
		return (0);
	a = ft_strlen(s);
	p = NULL;
	if (a < start)
	{
		p = ft_sub(p);
		return (p);
	}
	if (start + len > a)
		len = a - start;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	a = 0;
	while (a < len && s[start + a])
	{
		p[a] = s[start + a];
		a++;
	}
	p[a] = '\0';
	return (p);
}
