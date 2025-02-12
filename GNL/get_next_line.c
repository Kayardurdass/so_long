/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 02:13:18 by uanglade          #+#    #+#             */
/*   Updated: 2025/01/07 14:34:07 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*ft_strjoin_(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		return (ft_strndup(s2, ft_strchr(s2, '\n') - s2 + 1));
	ret = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!ret)
		return (free(s1), NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		ret[i++] = s1[j];
	j = 0;
	while (s2[j] != '\n' && s2[j] && --n > 0)
		ret[i++] = s2[j++];
	ret[i] = s2[j];
	if (s1)
		free(s1);
	return (ret);
}

void	trim_buffer(char *buffer, char *left, int n)
{
	int		i;
	char	*tmp;

	if (ft_strchr(buffer, '\n') && ft_strchr(buffer, '\n') - buffer != n - 1)
		tmp = ft_strndup(ft_strchr(buffer, '\n') + 1, n - 1);
	else
		return (ft_bzero(left, n));
	if (!tmp)
		return ;
	if (!buffer)
	{
		left[0] = 0;
		return (free(tmp));
	}
	i = -1;
	while (*tmp)
	{
		left[++i] = *tmp;
		tmp++;
	}
	left[++i] = *tmp;
	free(tmp - i);
}

char	*read_until_nl(char *left, char *ret, int fd)
{
	char	*buffer;
	int		rd_size;

	rd_size = BUFFER_SIZE;
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (free(ret), NULL);
	while (rd_size > 0)
	{
		rd_size = read(fd, buffer, BUFFER_SIZE);
		if (rd_size == -1)
			return (free(buffer), free(ret), NULL);
		if (rd_size == 0 && ft_strlen(ret) > 0)
			return (free(buffer), ret);
		if (rd_size == 0 && ft_strlen(ret) == 0)
			return (free(buffer), free(ret), NULL);
		ret = ft_strjoin_(ret, buffer, rd_size);
		if (!ret)
			return (free(buffer), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (rd_size > 0)
		trim_buffer(buffer, left, rd_size);
	return (free(buffer), ret);
}

static int	init(char **left, char **ret)
{
	if (!(*left))
	{
		*left = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		*ret = ft_calloc(1, 1);
		if (!(*left) || !(*ret))
			return (-1);
	}
	else if (ft_strlen(*left) > 0)
	{
		if (ft_strchr(*left, '\n'))
		{
			*ret = ft_strndup(*left, ft_strchr(*left, '\n') - *left + 1);
			if (!(*ret))
				return (-1);
			return (trim_buffer(*left, *left, BUFFER_SIZE), 1);
		}
		*ret = ft_strndup(*left, ft_strlen(*left) + 1);
		if (!(*ret))
			return (-1);
		trim_buffer(*left, *left, BUFFER_SIZE);
	}
	else
		*ret = ft_calloc(1, 1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*ret;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	n = init(&left, &ret);
	if (n == -1)
	{
		if (left)
			free(left);
		if (ret)
			free(ret);
		return (left = NULL, NULL);
	}
	if (n == 1)
		return (ret);
	ret = read_until_nl(left, ret, fd);
	if (!ret)
		return (free(left), left = NULL, NULL);
	return (ret);
}
