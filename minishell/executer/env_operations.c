/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:55:26 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 19:07:30 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_reverse_norme(t_info *struktura, t_env *current, int i)
{
	while (current)
	{
		struktura->envp[i] = ft_strjoin(current->key, "=");
		struktura->envp[i] = ft_strjoin(struktura->envp[i], current->value);
		i++;
		current = current->next;
	}
	struktura->envp[i] = NULL;
	struktura->envp_f = 1;
}

void	env_reverse_convert(t_info *struktura)
{
	int		i;
	t_env	*current;

	i = 0;
	current = struktura->envp_list;
	if (current)
	{
		while (struktura->envp[i] != NULL)
		{
			free(struktura->envp[i]);
			current = current->next;
			i++;
		}
		free(struktura->envp);
		struktura->envp = NULL;
	}
	i = ft_lstsize_mod(current);
	struktura->envp = (char **) malloc((i + 1) * sizeof(struktura->envp));
	if (struktura->envp == NULL)
		return ;
	i = 0;
	env_reverse_norme(struktura, current, i);
}

void	free_old_export(t_info *struktura)
{
	t_env	*tmp;

	tmp = struktura->export_list_head;
	while (tmp)
	{
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		tmp = tmp->next;
	}
	free(tmp);
	tmp = NULL;
}

void	copy_norme(t_env *envp_struct, t_env *tmp, t_env *new)
{
	while (envp_struct != NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			return ;
		tmp->key = ft_strdup(envp_struct->key);
		tmp->value = ft_strdup(envp_struct->value);
		tmp->num = 0;
		tmp->next = NULL;
		new->next = tmp;
		while (new)
		{
			if (!new->next)
				break ;
			new = new->next;
		}
		envp_struct = envp_struct->next;
	}
}

void	copy_in_export(t_info *struktura, t_env *envp_struct)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*keep;

	tmp = NULL;
	if (struktura->export_list_head)
		free_old_export(struktura);
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		ft_error("malloc error\n", struktura);
	keep = envp_struct;
	new->key = copy_char(envp_struct->key);
	new->value = copy_char(envp_struct->value);
	new->num = 0;
	new->next = NULL;
	struktura->export_list_head = new;
	envp_struct = envp_struct->next;
	copy_norme(envp_struct, tmp, new);
	envp_struct = keep;
}

/*
void  copy_in_export(t_info *struktura, t_env *envp_struct)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*keep;

	tmp = NULL;
	if (struktura->export_list_head)
		free_old_export(struktura);
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		ft_error("malloc error\n", struktura);
	keep = envp_struct;
	new->key = copy_char(envp_struct->key);
	new->value = copy_char(envp_struct->value);
	new->num = 0;
	new->next = NULL;
	struktura->export_list_head = new;
	envp_struct = envp_struct->next;
	copy_norme();
	while (envp_struct != NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			return ;
		tmp->key = ft_strdup(envp_struct->key);
		tmp->value = ft_strdup(envp_struct->value);
		tmp->num = 0;
		tmp->next = NULL;
		new->next = tmp;
		while (new)
		{
			if (!new->next)
				break ;
			new = new->next;
		}
		envp_struct = envp_struct->next;
	}
	envp_struct = keep;
}

void	env_reverse_convert(t_info *struktura)
{
	int		i;
	t_env	*current;

	i = 0;
	current = struktura->envp_list;
	if (current)
	{
		while (struktura->envp[i] != NULL)
		{
			free(struktura->envp[i]);
			current = current->next;
			i++;
		}
		free(struktura->envp);
		struktura->envp = NULL;
	}
	i = ft_lstsize_mod(current);
	struktura->envp = (char **) malloc((i + 1) * sizeof(struktura->envp));
	if (struktura->envp == NULL)
		return ;
	i = 0;
	while (current)
	{
		struktura->envp[i] = ft_strjoin(current->key, "=");
		struktura->envp[i] = ft_strjoin(struktura->envp[i], current->value);
		i++;
		current = current->next;
	}
	struktura->envp[i] = NULL;
	struktura->envp_f = 1;
}
*/
