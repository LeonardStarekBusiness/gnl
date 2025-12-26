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
	rstr = malloc(until_nl(str) + 1);
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

char	*take_rest(char *stash, char *buffer)
{
	int	j;

	j = 0;
	while (buffer[j] && buffer[j] != SEP)
		j++;
	if (buffer[j] == SEP)
		j++;
	free(stash);
	return (ft_strdup(buffer + j));
}

char	*getter(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*rb;
	int			br;

	buffer = ft_strdup(stash);
	rb = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer || !rb)
		return (free(buffer), free(rb), NULL);
	while (!(newline_contain(buffer)))
	{
		br = read(fd, rb, BUFFER_SIZE);
		if (br == -1)
			return (free(stash), stash = NULL, free(buffer), free(rb), NULL);
		else if (br == 0 && buffer[0] != 0)
			return (free(stash), stash = NULL, free(rb), buffer);
		else if (br == 0 && buffer[0] == 0)
			return (free(stash), free(buffer), free(rb), NULL);
		rb[br] = 0;
		buffer = join_and_free(buffer, rb);
		if (!buffer)
			return (free(stash), stash = NULL, free(rb), NULL);
	}
	stash = take_rest(stash, buffer);
	return (free(rb), amend(buffer));
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
	int fd = open("baal", O_RDONLY);
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
