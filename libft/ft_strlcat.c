/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:44:07 by uanglade          #+#    #+#             */
/*   Updated: 2024/10/08 23:54:12 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	i = ft_strlen(dst);
	j = -1;
	if (!dst || !src)
		return (0);
	if (dstsize > ft_strlen(dst))
		ret = ft_strlen(dst);
	else
		ret = dstsize;
	if (!dstsize)
		return (ft_strlen(src));
	while (src[++j] && i + 1 < dstsize)
		dst[i++] = src[j];
	dst[i] = 0;
	return (ft_strlen(src) + ret);
}
