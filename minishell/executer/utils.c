/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:00:01 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 13:19:58 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_key(char *content, t_env *d)
{
	int	j;
	int	l;

	j = 0;
	l = ft_strlen(content);
	d->key = (char *) malloc(l * sizeof(char));
	if (d->key == NULL)
		return ;
	d->value = NULL;
	while (l > j)
	{
		d->key[j] = content[j];
		j++;
	}
	d->key[j] = '\0';
	free(content);
}

void	find_kv_norme(t_env *d, int l, int i, char *content)
{
	int	j;
	int	r;

	j = 0;
	r = 0;
	while (l > j)
	{
		if (i > j)
			d->key[j] = content[j];
		else
		{
			d->key[j] = '\0';
			if (i != j)
			{
				d->value[r] = content[j];
				r++;
			}
		}
		j++;
	}
	d->value[r] = '\0';
}

void	find_key_value(char *content, t_env *d)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(content);
	while (content[i] != '=')
		i++;
	d->key = malloc(i * sizeof(char *));
	if (d->key == NULL)
		return ;
	d->value = malloc((l - i - 1) * sizeof(char *));
	if (d->value == NULL)
		return ;
	find_kv_norme(d, l, i, content);
}

void	add_new_elem_key_value(t_env *something, char *str)
{
	t_env	*new;

	new = ft_lstnew_mod(str);
	ft_lstadd_back_mod(something, new);
}

void	add_new_elem_key(t_env *ex_l_head, char *str)
{
	t_env	*new;

	new = ft_lstnew_mod_two(str);
	ft_lstadd_back_mod(ex_l_head, new);
}

/*
void	find_key_value(char *content, t_env *d)
{
	int	i;
	int	j;
	int	l;
	int	r;

	i = 0;
	j = 0;
	l = ft_strlen(content);
	while (content[i] != '=')
		i++;
	d->key = malloc(i * sizeof(char *));
	if (d->key == NULL)
		return ;
	d->value = malloc((l - i - 1) * sizeof(char *));
	if (d->value == NULL)
		return ;
	r = 0;
	while (l > j)
	{
		if (i > j)
			d->key[j] = content[j];
		else
		{
			d->key[j] = '\0';
			if (i != j)
			{
				d->value[r] = content[j];
				r++;
			}
		}
		j++;
	}
	d->value[r] = '\0';
}
*/