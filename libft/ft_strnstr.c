/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 03:51:11 by uanglade          #+#    #+#             */
/*   Updated: 2024/11/07 03:59:49 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big || !little)
		return (NULL);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	i = -1;
	while (big[++i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && little[j] \
			&& big[i + j] && i + j < len)
			j++;
		if (j == ft_strlen(little))
			return ((char *)big + i);
	}
	return (NULL);
}
