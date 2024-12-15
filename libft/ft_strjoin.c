/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 05:45:15 by uanglade          #+#    #+#             */
/*   Updated: 2024/11/07 05:45:15 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret || !s1 || !s2)
		return (ret);
	i = 0;
	j = -1;
	while (s1[++j])
		ret[i++] = s1[j];
	j = -1;
	while (s2[++j])
		ret[i++] = s2[j];
	ret[i] = 0;
	return (ret);
}
