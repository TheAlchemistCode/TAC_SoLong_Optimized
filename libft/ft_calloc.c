/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:54:14 by clyon             #+#    #+#             */
/*   Updated: 2025/06/27 17:56:59 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	sum;
	void	*p;

	if (!nmemb || !size)
		return (malloc(1));
	sum = nmemb * size;
	if (sum / size != nmemb)
		return (NULL);
	p = malloc(sum);
	if (!p)
		return (NULL);
	ft_bzero(p, sum);
	return (p);
}
