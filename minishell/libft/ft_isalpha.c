/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:41:23 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/24 18:22:05 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int a)
{
	if (((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122)))
		return (1);
	else
		return (0);
}