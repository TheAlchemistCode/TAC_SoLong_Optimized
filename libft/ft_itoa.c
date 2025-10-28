/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:16:02 by clyon             #+#    #+#             */
/*   Updated: 2025/06/27 17:20:47 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Count how many characters the number will take
*/
static int	ft_decimal_places(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/*
** Builds the string backwards, from right to left.
*/
static char	*mount_str(char *str, long l, int i)
{
	if (l == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (l < 0)
	{
		str[0] = '-';
		l *= -1;
	}
	while (l > 0)
	{
		str[i--] = l % 10 + '0';
		l /= 10;
	}
	return (str);
}

/*
** Time to wrap - here is the real slim schadi
*/
char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	l;

	l = n;
	i = ft_decimal_places(l);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	return (mount_str(str, l, i));
}

/* 
#include <stdio.h>

int	main(void)
{
	char	*str;

	str = ft_itoa(42);
	printf("ft_itoa(42)   = %s\n", str);
	free(str);

	str = ft_itoa(-123);
	printf("ft_itoa(-123) = %s\n", str);
	free(str);

	return (0);
}
*/