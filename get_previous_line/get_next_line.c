/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:42:38 by lstarek           #+#    #+#             */
/*   Updated: 2025/11/18 16:02:08 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline_contain(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
	{
		if (str[i] == SEP)
			return (1);
		i++;
	}
	return (0);
}

char	*amend(char *str)
{
	char	*rstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	rstr = malloc(safe_strlen(str) + 1);
	if (!rstr)
		return (free(str), NULL);
	while (str[j] != SEP && str[j] != 0)
		rstr[i++] = str[j++];
	rstr[i++] = str[j++];
	rstr[i] = 0;
	free(str);
	str = NULL;
	return (rstr);
}

void	take_rest(char *stash, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[j] && buffer[j] != SEP)
		j++;
	if (buffer[j] == SEP)
		j++;
	while (buffer[j])
		stash[i++] = buffer[j++];
	stash[i] = 0;
}

char	*getter(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*buffer;
	char		*readbuf;
	int			br;

	buffer = ft_strdup(stash);
	readbuf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer || !readbuf)
		return (free(buffer), free(readbuf), NULL);
	while (!(newline_contain(buffer)))
	{
		br = read(fd, readbuf, BUFFER_SIZE);
		if (br == -1)
			return (clear(stash), free(buffer), free(readbuf), NULL);
		else if (br == 0 && buffer[0] != 0)
			return (clear(stash), free(readbuf), buffer);
		else if (br == 0 && buffer[0] == 0)
			return (free(buffer), free(readbuf), NULL);
		readbuf[br] = 0;
		buffer = join_and_free(buffer, readbuf);
		if (!buffer)
			return (clear(stash), free(readbuf), NULL);
	}
	take_rest(stash, buffer);
	return (free(readbuf), amend(buffer));
}

char	*get_next_line(int fd)
{
	if (BUFFER_SIZE > 0 && fd >= 0)
		return (getter(fd));
	return (NULL);
}

/*
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd = 1;//open("multiple_nl.txt", O_RDONLY);
	char *str;
	while ((str = get_next_line(fd)))
	{
		printf("-->[%s]\n", str);
		if (str[0] == 'q')
			{free(str);break;}
		free(str);
	}
	
	if (fd > 0)
		close(fd);
	return 0;
} */
