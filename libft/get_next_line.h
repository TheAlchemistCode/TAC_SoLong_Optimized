/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:49:38 by clyon             #+#    #+#             */
/*   Updated: 2025/08/20 18:25:31 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// unistd for read // stdlib for malloc, free & size_t
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* Buffer & stash funcs */
char	*get_next_line(int fd);
char	*_01_stash_builder(char *stash, int fd);
char	*_02_stashtrunc(char *stash);
char	*_03_leftover(char *stash);
char	*_01_stashjoiner(char *stash, char *buffer);

/* String funcs */
void	*ft_calloc(size_t nmeb, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
