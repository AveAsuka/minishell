/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:10:52 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/07 15:31:23 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*question_mark(char *cmd, t_info *shell)
{
	char	*str;
	int		i;

	i = 1;
	if (cmd[i] == '?')
	{
		str = ft_itoa(shell->command_result);
		i++;
	}
	while (cmd[i] != '\0')
	{
		str = join_symbol(&str, cmd[i]);
		i++;
	}
	return (str);
}
