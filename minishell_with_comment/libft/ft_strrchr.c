/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:06 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:19:58 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = ft_strlen(s);
	if (c == '\0')
		return ((char *)(s + a));
	while (a != 0)
	{
		if (s[a - 1] == (char)c)
			return ((char *)(s + a - 1));
		a--;
	}
	return (NULL);
}
