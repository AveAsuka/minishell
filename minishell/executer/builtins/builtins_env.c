/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:54:37 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 16:54:55 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_env(t_info *struktura)
{
	t_env	*here;
	int		i;

	i = 0;
	here = struktura->envp_list;
	while (here)
	{
		i++;
		printf("%s=%s\n", here->key, here->value);
		here = here->next;
	}
	struktura->command_result = 0;
	exit(0);
}
