/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:58:32 by nle-biha          #+#    #+#             */
/*   Updated: 2021/01/28 16:32:27 by nle-biha         ###   ########.fr       */
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

int		exit_gnl(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	return (-1);
}

int		fill_next_line(char *source, char **line, char *save)
{
	char *temp;

	if (!(temp = ft_substr(source, 0, pos_new_line(source))))
		return (exit_gnl(line));
	if (!(*line = ft_strjoin(*line, temp)))
		return (exit_gnl(line));
	if (!(temp = ft_substr(source, pos_new_line(source) + 1, BUFFER_SIZE)))
		return (exit_gnl(line));
	ft_strlcpy(save, temp, BUFFER_SIZE);
	free(temp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	save[1024][BUFFER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	int			err;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(*line = ft_calloc(BUFFER_SIZE, sizeof(char))))
		return (-1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	if (pos_new_line(save[fd]) < ft_strlen(save[fd]))
		return (fill_next_line(save[fd], line, save[fd]));
	ft_strlcpy(*line, save[fd], BUFFER_SIZE);
	while ((err = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (fill_next_line(buf, line, save[fd]) == -1)
			return (-1);
		if (pos_new_line(buf) < ft_strlen(buf))
			return (1);
		ft_bzero(buf, BUFFER_SIZE + 1);
	}
	if (err == 0)
		return (0);
	return (exit_gnl(line));
}
