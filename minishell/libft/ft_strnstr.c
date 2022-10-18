/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:01:57 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:19:45 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char	*s2, size_t	n)
{
	size_t	i;
	size_t	q;

	i = 0;
	if (ft_strlen(s2) == 0)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		q = 0;
		while (s1[i + q] == s2[q] && s1[i + q] && s2[q] && i + q < n)
		{
			if (s2[q + 1] == '\0')
				return ((char *)s1 + i);
			q++;
		}
		i++;
	}
	return (0);
}
