/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:42:41 by lstarek           #+#    #+#             */
/*   Updated: 2025/12/26 21:02:31 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 10
# endif
# ifndef SEP
#  define SEP '\n'
# endif

char	*get_next_line(int fd);
int		until_nl(const char *str);
char	*ft_strdup(char *src);
void	clear(void **ptr);
char	*join_and_free(char *s1, char *s2);
size_t	safe_strlen(char const *str);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
