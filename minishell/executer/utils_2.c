/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:09:57 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 13:20:04 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_char(char *a)
{
	char	*b;
	int		i;

	i = ft_strlen(a);
	b = malloc(sizeof(char) * (i + 1));
	if (b == NULL)
		return (NULL);
	i = 0;
	while (a[i])
	{
		b[i] = a[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}

int	ft_strncmp_mod(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (0);
		i++;
	}
	i = ft_strlen(s2);
	if (n != i)
		return (0);
	return (1);
}

char	*copy_char_two(char *a, int j)
{
	char	*b;
	int		i;

	if (j == 0)
		i = ft_strlen(a);
	else
		i = j;
	b = malloc(sizeof(char) * (i + 1));
	if (b == NULL)
		return (NULL);
	j = 0;
	while (i > j)
	{
		b[j] = a[j];
		j++;
	}
	b[i] = '\0';
	return (b);
}
