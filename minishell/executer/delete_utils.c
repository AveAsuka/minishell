/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:54:31 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 18:54:47 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_or_export(t_env *something)
{
	int	i;

	i = 0;
	while (something)
	{
		i++;
		something = something->next;
	}
}
