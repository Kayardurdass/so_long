/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 05:30:02 by uanglade          #+#    #+#             */
/*   Updated: 2024/11/13 02:48:41 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	char				*ret;

	if (!s)
		return (NULL);
	if (len <= 0 || ft_strlen(s) < start)
		return (ft_calloc(1, 1));
	if (start + len > ft_strlen(s))
		ret = (char *)ft_calloc((ft_strlen(s) - start + 1), sizeof(char));
	else
		ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = start;
	j = -1;
	while (i < start + len && s[i])
		ret[++j] = s[i++];
	return (ret);
}
