/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:08:54 by uanglade          #+#    #+#             */
/*   Updated: 2024/10/08 23:19:43 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst || !src)
		return (NULL);
	if (!len)
		return (dst);
	if ((size_t)dst - (size_t)src > len)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len-- > 0)
			*((char *)dst + len) = *((char *)src + len);
	}
	return (dst);
}
