/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:48:52 by clyon             #+#    #+#             */
/*   Updated: 2025/08/18 20:48:52 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
 * Reads from file descriptor and builds stash until newline or EOF
 * Allocates buffer, reads BUFFER_SIZE bytes at a time
 * Returns: Updated stash with new content or NULL on error
 */

char	*_01_stash_builder(char *stash, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stash), NULL);
		buffer[bytes_read] = '\0'; //add null terminator to the buffer
		stash = _01_stashjoiner(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (free(buffer), stash);
}

/* 
 * Joins stash with buffer into new string
 * Frees old stash and returns new concatenated string
 * Returns: New joined string or NULL on error
 */
char	*_01_stashjoiner(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	return (free(stash), temp);
}

/* 
 * Extracts a single line from stash (including newline if present)
 * Allocates new string for the line
 * Returns: Extracted line (like "Hello\n\0") or NULL on error
 */
char	*_02_stashtrunc(char *stash)
{
	size_t	len;
	char	*workline;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	workline = ft_calloc(len + 1, sizeof(char));
	if (!workline)
		return (NULL);
	ft_strlcpy(workline, stash, len + 1);
	return (workline);
}

/* 
 * Updates stash by removing extracted line and keeping remaining content
 * Allocates new string for remaining content
 * Returns: New string with remaining content or NULL on error
 */
char	*_03_leftover(char *stash)
{
	size_t	start;
	size_t	len;
	char	*leftovers;

	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (stash[start] == '\n')
		start++;
	len = ft_strlen(stash + start);
	leftovers = ft_calloc(len + 1, sizeof(char));
	if (!leftovers)
		return (free(stash), NULL);
	ft_strlcpy(leftovers, stash + start, len + 1);
	return (free(stash), leftovers);
}

/* 
 * Main function that returns one line at a time from file descriptor
 * Uses static variable stash to maintain state between calls
 * Returns: Next line from file or NULL if EOF/error
 */
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*workline;

	if (fd < 0 || BUFFER_SIZE <= 0) // Check for invalid file descriptor (fd) or invalid BUFFER_SIZE
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, 1); // to createe empty string
	if (!stash)
		return (NULL); //if memory allocation fails return null.
	if (!ft_strchr(stash, '\n'))
	{
		stash = _01_stash_builder(stash, fd);
		if (!stash)
			return (NULL);
	}
	workline = _02_stashtrunc(stash);
	if (!workline || workline[0] == '\0')
	{
		free(stash);
		stash = NULL;
		free(workline);
		return (NULL);
	}
	stash = _03_leftover(stash);
	return (workline);
}

/*#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int     fd;
	char    *line;
	int     line_count;

	// Test with a text file
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}

	line_count = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", line_count++, line);
		free(line);
	}

	close(fd);
	return (0);
}*/
