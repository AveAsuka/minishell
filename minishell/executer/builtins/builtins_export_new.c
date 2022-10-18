/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:34:44 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:09:10 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_value(t_env *tmp, char *a)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(a);
	free(tmp->value);
	while (a[i] != '=')
		i++;
	tmp->value = (char *) malloc((l - i) * sizeof(char));
	if (tmp->value == NULL)
		return ;
	if (!tmp->value)
	{
		tmp->value = NULL;
		return ;
	}
	export_new_norme(tmp, a, l, i);
}

int	find_duplicate(t_info *struktura, char *a, int k, char *str)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = ft_strlen(a);
	j = 0;
	tmp = struktura->envp_list;
	while (tmp)
	{
		if (ft_strncmp_mod(a, tmp->key, i) && k == 1)
		{
			edit_value(tmp, str);
			j = 1;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = struktura->export_list_head;
	j += duplicate_norme(tmp, a, k, str);
	free(a);
	return (j);
}

int	export_analiz_word(t_info *struktura, char *str)
{
	int		i;
	int		find_equally;
	char	*a;

	i = 0;
	find_equally = 0;
	a = NULL;
	while (str[i])
	{
		if ((i == 0 && str[i] >= '0' && str[i] <= '9') || str[0] == '=')
			return (2);
		if (analiz_norme(15, str, i, find_equally) == 2)
			return (2);
		if (str[i] == '=')
		{
			find_equally = 1;
			a = copy_char_two(str, i);
		}
		i++;
	}
	if (find_equally == 0)
		a = copy_char_two(str, i);
	i = find_duplicate(struktura, a, find_equally, str);
	return (analiz_norme(10, str, i, find_equally));
}

void	export_error(char *stroka, t_info *struktura)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(stroka, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	struktura->command_result = 1;
	exit(0);
}

void	export_analiz(t_info *struktura, char **stroka)
{
	int	i;
	int	code;

	i = 1;
	code = 0;
	while (stroka[i])
	{
		code = export_analiz_word(struktura, stroka[i]);
		if (code == 0)
			add_new_elem_key(struktura->export_list_head, stroka[i]);
		else if (code == 1)
		{
			add_new_elem_key_value(struktura->export_list_head, stroka[i]);
			add_new_elem_key_value(struktura->envp_list, stroka[i]);
			struktura->envp_f = 0;
		}
		else if (code == 3)
		{
			add_new_elem_key_value(struktura->envp_list, stroka[i]);
			struktura->envp_f = 0;
		}
		else if (code == 2)
			export_error (stroka[i], struktura);
		i++;
	}
}
