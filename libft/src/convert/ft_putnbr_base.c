/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:09:43 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/26 01:34:22 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbr_base_rec(long int nbr, char *base)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = nbr * -1;
	}
	if (nbr >= (int)ft_strlen(base))
		ft_putnbr_base_rec(nbr / ft_strlen(base), base);
	write(1, &base[nbr % ft_strlen(base)], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long int	nb;

	nb = (long int)nbr;
	if (ft_base_error(base))
		return ;
	ft_putnbr_base_rec(nb, base);
}
