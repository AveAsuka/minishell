/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:26:17 by lbrianna          #+#    #+#             */
/*   Updated: 2022/07/09 23:26:17 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_double(char **line, char *str)
{
	char	**arr;
	int		i;

	i = 0;
	arr = NULL;
	while (line && line[i])
		i++;
	arr = malloc(sizeof(char *) * (i + 2));
	if (!arr)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		arr[i] = ft_strdup(line[i]);
		i++;
	}
	if (str)
		arr[i] = ft_strdup(str);
	i++;
	arr[i] = NULL;
	return (arr);
}

int	quotes(int *flag, char c)
{
	int	check;

	check = *flag;
	if (c == '\'' && *flag == 0)
		*flag = 1;
	else if (c == '\"' && *flag == 0)
		*flag = 2;
	else if (c == '\'' && *flag == 1)
		*flag = 0;
	else if (c == '\"' && *flag == 2)
		*flag = 0;
	if (check != *flag)
		return (-1);
	return (1);
}

int	check_redirect(char c, int flag)
{
	if (c == '>' && flag == 0)
		return (-1);
	if (c == '<' && flag == 0)
		return (-2);
	return (1);
}
