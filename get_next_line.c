/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:58:32 by nle-biha          #+#    #+#             */
/*   Updated: 2021/01/15 20:44:29 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	pos_new_line(char *buf)
{
	size_t ret;

	ret = 0;
	while (buf[ret] && buf[ret] != '\n')
		ret++;
	return (ret);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *scpy;

	scpy = (unsigned char *)s;
	while (n > 0)
	{
		*scpy = 0;
		scpy++;
		n--;
	}
}

int		get_next_line(int fd, char **line)
{
	static char	save[BUFFER_SIZE + 1];
	char		*temp;
	char		buf[BUFFER_SIZE + 1];
	int			err;

	ft_bzero(buf, BUFFER_SIZE + 1);
	*line = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (pos_new_line(save) + 1 < ft_strlen(save))
	{
		temp = ft_substr(save, 0, pos_new_line(save) + 1);
		*line = ft_strjoin(*line, temp);
		temp = ft_substr(save, pos_new_line(save) + 1, BUFFER_SIZE);
		ft_strlcpy(save, temp, BUFFER_SIZE);
		free(temp);
		return (1);
	}
	ft_strlcpy(*line, save, BUFFER_SIZE);
	while ((err = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		temp = ft_substr(buf, 0, pos_new_line(buf) + 1);
		*line = ft_strjoin(*line, temp);
		temp = ft_substr(buf, pos_new_line(buf) + 1, BUFFER_SIZE);
		ft_strlcpy(save, temp, BUFFER_SIZE);
		free(temp);
		if (pos_new_line(buf) < BUFFER_SIZE)
			return (1);
	}
	if (err == 0)
	{
		ft_bzero(save, BUFFER_SIZE + 1);
		return (0);
	}
	return (-1);
}
