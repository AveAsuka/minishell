/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:53:10 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:10:52 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_echo(t_info *struktura, char **stroka)
{
	int	flag;
	int	i;

	if (stroka[0] && stroka[1])
	{
		flag = ft_strncmp_mod("-n", stroka[1], 2);
		if (flag == 1)
			i = 2;
		else
			i = 1;
		while (stroka[i])
		{
			ft_putstr_fd(stroka[i], 1);
			if (stroka[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (flag == 0)
			write(1, "\n", 1);
		struktura->command_result = 0;
	}
	exit(0);
}
