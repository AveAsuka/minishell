/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:43:47 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/13 17:18:20 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		a;
	int		b;

	if (!s1)
		return (NULL);
	a = ft_strlen(s1);
	b = 0;
	p = malloc((a + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	if (!p)
		return (0);
	while (s1[b])
	{
		p[b] = s1[b];
		b++;
	}
	p[b] = '\0';
	return (p);
}
