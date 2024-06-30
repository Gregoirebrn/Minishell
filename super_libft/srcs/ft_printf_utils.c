/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:18:35 by beroy             #+#    #+#             */
/*   Updated: 2024/01/17 16:20:00 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

ssize_t	ft_putstr(char *str)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		j = ft_putchar(str[i]);
		if (j == -1)
			return (-1);
		i += j;
	}
	return (i);
}

void	ft_putnbr_base(ssize_t nbr, char *str, ssize_t *length)
{
	ssize_t	i;

	if (nbr < 0)
	{
		i = ft_putchar('-');
		if (i == -1)
			return (*length = -1, (void)0);
		*length += i;
		ft_putnbr_base(nbr * -1, str, length);
		if (*length == -1)
			return (*length = -1, (void)0);
	}
	else
	{
		if (nbr >= (ssize_t)ft_strlen(str))
		{
			ft_putnbr_base(nbr / ft_strlen(str), str, length);
			if (*length == -1)
				return (*length = -1, (void)0);
		}
		i = ft_putchar(str[nbr % ft_strlen(str)]);
		if (i == -1)
			return (*length = -1, (void)0);
		*length += i;
	}
}

void	ft_putnbr_ul(size_t nbr, char *str, ssize_t *length)
{
	ssize_t	i;

	if (nbr >= ft_strlen(str))
	{
		ft_putnbr_ul(nbr / ft_strlen(str), str, length);
		if (*length == -1)
			return (*length = -1, (void)0);
	}
	i = ft_putchar(str[nbr % ft_strlen(str)]);
	if (i == -1)
		return (*length = -1, (void)0);
	*length += i;
}
