/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:58:07 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/22 17:27:38 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_neg(int n, int fd)
{
	if (n <= -10)
		ft_print_neg((n / 10), fd);
	ft_putchar_fd(('0' - (n % 10)), fd);
}

static void	ft_printnum(int n, int fd)
{
	if (n >= 10)
		ft_printnum((n / 10), fd);
	ft_putchar_fd(((n % 10) + '0'), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483647)
	{
		write(fd, "−2", 2);
		n = 147483647;
		ft_printnum(n, fd);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_print_neg(n, fd);
	}
	else if (n > 0)
		ft_printnum(n, fd);
	else
		write(fd, "0", 1);
}
