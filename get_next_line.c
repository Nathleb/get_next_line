/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:58:32 by nle-biha          #+#    #+#             */
/*   Updated: 2021/01/05 16:38:36 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	pos_new_line(char *buf)
{
	size_t ret;

	ret = 0;
	while(buf[ret] && buf[ret] != '\n')
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

int	get_next_line(int fd, char **line)
{
	static char	start_of_next_line[BUFFER_SIZE + 1];
	char 		*temp;
	char		buf[BUFFER_SIZE + 1];
	int			err;

	ft_bzero(buf, BUFFER_SIZE + 1);
	*line = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (pos_new_line(start_of_next_line) + 1 < ft_strlen(start_of_next_line))
	{
		temp = ft_substr(start_of_next_line, 0, pos_new_line(start_of_next_line) + 1);
		*line = ft_strjoin(*line, temp);
		temp = ft_substr(start_of_next_line, pos_new_line(start_of_next_line) + 1, BUFFER_SIZE);
		ft_strlcpy(start_of_next_line, temp, BUFFER_SIZE);
		free(temp);
		return(1);
	}
	ft_strlcpy(*line, start_of_next_line, BUFFER_SIZE);
	while ((err = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		temp = ft_substr(buf, 0, pos_new_line(buf) + 1);
		*line = ft_strjoin(*line, temp);
		temp = ft_substr(buf, pos_new_line(buf) + 1, BUFFER_SIZE);
		ft_strlcpy(start_of_next_line, temp, BUFFER_SIZE);
		free(temp);
		if (pos_new_line(buf) < BUFFER_SIZE)
			return (1);
	}
	if (err == 0)
	{
		ft_bzero(start_of_next_line, BUFFER_SIZE + 1);
		return (0);
	}
	return (-1);
}

int main(int argc, char **argv)
{
	char **line;
	int max = 45;
	line = malloc(sizeof(char*) * max);
	(void)argc;
		//printf("%s\n", temp);
	int i = 0;
	int	fd = open(argv[1], O_RDONLY);
	while (i < max)
	{
		printf("%d\n",get_next_line(fd, &line[i]));
		printf("%s", line[i]);
		i++;
	}
	return (1);
}
