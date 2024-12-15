/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:02:56 by uanglade          #+#    #+#             */
/*   Updated: 2024/10/09 00:05:42 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = -1;
	if (!s)
		return (NULL);
	if (!(unsigned char)c)
		return ((char *)s + ft_strlen(s));
	while (s[++i])
	{
		if (s[i] == (unsigned char)c)
			ret = (char *)s + i;
	}
	return (ret);
}
