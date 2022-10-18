/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:52:15 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:20:06 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(const char *set, char c)
{
	int	a;

	a = 0;
	while (set[a])
	{
		if (set[a] == c)
			return (1);
		else
			a++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;
	size_t	e;
	char	*p;

	if (!s1 || !set)
		return (0);
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	e = ft_strlen(s1) - 1;
	a = 0;
	while (s1[a] && ft_compare(set, s1[a]))
		a++;
	if (a == ft_strlen(s1))
		return (ft_calloc(1, sizeof(char)));
	while (ft_compare(set, s1[e]))
		e--;
	p = (char *)malloc((e + 2 - a) * sizeof(char));
	if (p == 0)
		return (0);
	b = 0;
	while (a <= e)
		p[b++] = s1[a++];
	p[b] = '\0';
	return (p);
}
