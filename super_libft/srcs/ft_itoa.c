/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:11:45 by beroy             #+#    #+#             */
/*   Updated: 2023/11/08 15:48:57 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_strfill(long int n, char *str, long int *i)
{
	if (n < 0)
	{
		str[*i] = '-';
		*i += 1;
		ft_strfill(n * -1, str, i);
	}
	else if (n > 9)
	{
		ft_strfill(n / 10, str, i);
		ft_strfill(n % 10, str, i);
	}
	else
	{
		str[*i] = n + 48;
		*i += 1;
	}
}

static void	ft_strsize(long int n, long int *size)
{
	if (n < 0)
	{
		*size += 1;
		ft_strsize(n * -1, size);
	}
	else if (n > 9)
	{
		ft_strsize(n / 10, size);
		ft_strsize(n % 10, size);
	}
	else
		*size += 1;
}

char	*ft_itoa(int n)
{
	long int	size;
	long int	i;
	char		*str;

	size = 0;
	i = 0;
	ft_strsize(n, &size);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (str);
	ft_strfill(n, str, &i);
	str[i] = 0;
	return (str);
}
