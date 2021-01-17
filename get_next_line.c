/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:58:32 by nle-biha          #+#    #+#             */
/*   Updated: 2021/01/17 01:02:22 by nle-biha         ###   ########.fr       */
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

void	fill_next_line(char *source, char **line, char *save)
{
	char *temp;

	temp = ft_substr(source, 0, pos_new_line(source));
	*line = ft_strjoin(*line, temp);
	temp = ft_substr(source, pos_new_line(source) + 1, BUFFER_SIZE);
	ft_strlcpy(save, temp, BUFFER_SIZE);
	free(temp);
}

int		get_next_line(int fd, char **line)
{
	static char	save[BUFFER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	int			err;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line ||
		!(*line = ft_calloc(BUFFER_SIZE, sizeof(char))))
		return (-1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	if (pos_new_line(save) < ft_strlen(save))
	{
		fill_next_line(save, line, save);
		return (1);
	}
	ft_strlcpy(*line, save, BUFFER_SIZE);
	while ((err = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		fill_next_line(buf, line, save);
		if (pos_new_line(buf) < ft_strlen(buf))
			return (1);
		ft_bzero(buf, BUFFER_SIZE + 1);
	}
	if (err == 0)
		return (0);
	return (-1);
}
