/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:16:41 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 18:52:39 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*delete_knot(t_env *current_del)
{
	t_env	*tmp;

	tmp = current_del;
	current_del = current_del->next;
	tmp->next = NULL;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	return (current_del);
}

void	unset_error(t_info *struktura, char *stroka)
{
	ft_putstr_fd(": unset: \'", 2);
	ft_putstr_fd(stroka, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	struktura->command_result = 1;
	exit(0);
}

t_info	*find_env(t_info *struktura, char *stroka)
{
	t_env	*ex_l_current;
	t_env	*env_current;
	int		i;

	i = ft_strlen(stroka);
	env_current = struktura->envp_list;
	find_norme(env_current, stroka, i, struktura);
	ex_l_current = struktura->export_list_head;
	find_norme_2(ex_l_current, stroka, i, struktura);
	return (struktura);
}

t_info	*built_unset(t_info *struktura, char **stroka)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (stroka[i])
	{
		while (stroka[i][j])
		{
			if (j == 0 && stroka[i][j] >= '0' && stroka[i][j] <= '9')
				unset_error(struktura, stroka[i]);
			if ((stroka[i][j] >= '!' && stroka[i][j] <= '/') || \
				(stroka[i][j] >= ':' && stroka[i][j] <= '@') || \
				(stroka[i][j] >= '[' && stroka[i][j] <= '^') || \
				(stroka[i][j] >= '{' && stroka[i][j] <= '~'))
				unset_error(struktura, stroka[i]);
			j++;
		}
		struktura = find_env(struktura, stroka[i]);
		i++;
		j = 0;
	}
	struktura->command_result = 0;
	return (struktura);
}

// t_info	*find_env(t_info  *struktura, char *stroka)
// {
//     t_env *ex_l_current;
//     t_env *env_current;
//     t_env *previous;
//     int 	j;
//     int 	i;

//     i = ft_strlen(stroka);
//     j = 0;
//     env_current = struktura->envp_list;
//     previous = struktura->envp_list;
//     while (env_current)
//     {
//         if (ft_strncmp_mod(stroka, env_current->key, i))
//         {
//             printf("1. key = %s, stroka = %s\n", env_current->key, stroka);
//             if (j == 0)
//             {
//                 struktura->envp_list = delete_knot(env_current);
//                 env_current = struktura->envp_list;
//             }
//             else
//                 env_current = delete_knot(env_current);
//             previous->next = env_current;
//             struktura->envp_f = 0;
//         }
//         else
//         {
//             previous = env_current;
//             env_current = env_current->next;
//             j++;
//         }
//     }
// // -----
//     j = 0;
//     ex_l_current = struktura->export_list_head;
//     previous = struktura->export_list_head;
//     while (ex_l_current)
//     {
//         if (ft_strncmp_mod(stroka, ex_l_current->key, i))
//         {
//             printf("2. key = %s, stroka = %s\n", ex_l_current->key, stroka);
//             if (j == 0)
//             {
//                 struktura->export_list_head = delete_knot(ex_l_current);
//                 ex_l_current = struktura->export_list_head;
//             }
//             else
//                 ex_l_current = delete_knot(ex_l_current);
//             previous->next = ex_l_current;
//         }
//         else
//         {
//             previous = ex_l_current;
//             ex_l_current = ex_l_current->next;
//             j++;
//         }
//     }
// // -----
//     return (struktura);
// }