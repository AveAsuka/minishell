/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:32:24 by lbrianna          #+#    #+#             */
/*   Updated: 2022/05/16 12:19:25 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*string;

	i = 0;
	if (!s)
		return (0);
	string = ft_strdup(s);
	if (!string)
		return (0);
	while (string[i])
	{
		string[i] = (*f)(i, string[i]);
		i++;
	}
	return (string);
}
