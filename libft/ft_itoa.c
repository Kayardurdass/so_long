/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:58:27 by uanglade          #+#    #+#             */
/*   Updated: 2024/11/07 22:46:42 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(long n)
{
	int	len;

	if (n < 0)
	{
		len = 2;
		n = -n;
	}
	else
		len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	nbr;
	int		len;
	int		i;

	nbr = (long)n;
	len = ft_nbrlen(nbr);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = len;
	if (nbr < 0)
	{
		nbr = -nbr;
		ret[0] = '-';
	}
	while (--i >= (n < 0))
	{
		ret[i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (ret);
}
