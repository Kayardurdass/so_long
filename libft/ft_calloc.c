/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 05:10:09 by uanglade          #+#    #+#             */
/*   Updated: 2024/11/07 05:29:34 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ret;
	long long	overflow_check;

	if (!size || !nmemb)
		return (malloc(0));
	overflow_check = nmemb * size;
	if (nmemb != overflow_check / size)
		return (NULL);
	ret = malloc(overflow_check);
	if (!ret)
		return (NULL);
	else
		ft_bzero(ret, overflow_check);
	return (ret);
}
