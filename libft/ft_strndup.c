/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:57:49 by uanglade          #+#    #+#             */
/*   Updated: 2024/11/13 02:34:40 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	res = (char *)ft_calloc((n + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		res[i] = s[i];
	return (res);
}
