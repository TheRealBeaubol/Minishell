/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:45:07 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_atoi_base(char *str, char *base)
{
	int	i;
	int	res;
	int	signe;

	signe = 1;
	i = 0;
	res = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] && ft_position_in_base(base, str[i]) != -1)
	{
		res = res * ft_convert_base_strlen(base) + \
			ft_position_in_base(base, str[i]);
		i++;
	}
	return (res * signe);
}

static int	ft_intlen_in_base(int nb, char *base)
{
	int	n;

	if (nb < 0)
	{
		n = 2;
		while (nb < (ft_convert_base_strlen(base) * -1))
		{
			nb /= ft_convert_base_strlen(base);
			n++;
		}
	}
	else
	{
		n = 1;
		while (nb > ft_convert_base_strlen(base))
		{
			nb /= ft_convert_base_strlen(base);
			n++;
		}
	}
	return (n);
}

static char	*convert_putnbr_base_rec(long int nbr, char *base, char *res)
{
	if (nbr >= ft_convert_base_strlen(base))
		convert_putnbr_base_rec(nbr / ft_convert_base_strlen(base), base, res);
	ft_convert_base_strcat(res, base[nbr % ft_convert_base_strlen(base)]);
	return (res);
}

static char	*convert_putnbr_base(int nbr, char *base)
{
	long int	nb;
	char		*res;

	nb = (long int)nbr;
	res = malloc((ft_intlen_in_base(nbr, base) + 1) * sizeof(char));
	*res = 0;
	if (nb < 0)
	{
		ft_convert_base_strcat(res, '-');
		nb = nb * -1;
	}
	return (convert_putnbr_base_rec(nb, base, res));
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*res;

	if (ft_base_error(base_from))
		return (NULL);
	if (ft_base_error(base_to))
		return (NULL);
	res = convert_putnbr_base(convert_atoi_base(nbr, base_from), base_to);
	return (res);
}
