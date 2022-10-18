/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:16:13 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 18:16:14 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_pwd(t_info *str)
{
	char	tmp[1024];

	getcwd(tmp, 1024);
	ft_putendl_fd(tmp, 1);
	str->command_result = 0;
	exit(0);
}
