/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:50:05 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/22 17:27:49 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_arr(char **split, int a)
{
	while (a > 0)
	{
		free(split[a]);
		a--;
	}
	free(split);
}

static void	ft_fill_array(char *split, const char *s, int beg, int end)
{
	int	a;

	a = 0;
	while (beg < end)
	{
		split[a] = s[beg];
		a++;
		beg++;
	}
	split[a] = '\0';
}

static int	ft_array(char **split, char const *s, char c)
{
	int	a;
	int	b;
	int	q;

	a = 0;
	b = 0;
	q = 0;
	while (s[a])
	{
		if (s[a] != c)
		{
			b = a;
			while (s[a] && s[a] != c)
				a++;
			split[q++] = (char *)malloc((a - b + 1) * sizeof(char));
			if (!split[q - 1])
				return (q - 1);
			ft_fill_array(split[q - 1], s, b, a);
		}
		if (s[a] != '\0')
			a++;
	}
	split[q] = NULL;
	return (1);
}

static int	ft_count(const char *s, char c)
{
	int	a;
	int	w;

	a = 0;
	w = 0;
	while (s[a])
	{
		if (s[a] != c)
		{
			w++;
			while (s[a] && s[a] != c)
				a++;
		}
		a++;
	}
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		w;
	int		res;

	w = 0;
	if (!s)
		return (0);
	w = ft_count(s, c);
	split = (char **)malloc((w + 1) * sizeof(s));
	if (split == 0)
		return (0);
	res = ft_array(split, s, c);
	if (res != 1)
		ft_free_arr(split, res);
	return (split);
}
