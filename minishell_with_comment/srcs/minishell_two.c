/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:18:20 by rabderus          #+#    #+#             */
/*   Updated: 2022/09/22 17:18:41 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_current_shlvl(t_info *struktura)
{
	t_env	*head;
	int		i;

	head = struktura->envp_list;
	while (head)
	{
		i = ft_strlen(head->key);
		if (ft_strncmp_mod("SHLVL", head->key, i))
		{
			printf("Before [%s %s]\n", head->key, head->value);
			free(head->value);
			head->value = ft_itoa(ft_atoi(head->value) + 1);
			printf("After [%s %s]\n", head->key, head->value);
			break ;
		}
		head = head->next;
	}
}

void	print_env_list(t_info *shell)
{
	t_env	*temp;
	int		i;

	temp = shell->envp_list;
	while (temp->next != NULL)
	{
		printf("Key - %s, value %s\n\n", temp->key, temp->value);
		temp = temp->next;
		i++;
	}
	printf("Key - %s, value %s\n\n", temp->key, temp->value);
}

int	search_pipe(char *str, int *f)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (*f == 0)
	{
		while (str[i] != '\0')
		{
			if (str[i] == '|')
				flag = 1;
			else if (str[i] != ' ')
				flag = 0;
			i++;
		}
	}
	*f = 1;
	return (flag);
}
