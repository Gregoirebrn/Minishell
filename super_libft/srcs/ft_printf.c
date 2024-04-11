/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:03:15 by beroy             #+#    #+#             */
/*   Updated: 2024/01/17 16:17:27 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printmemory(size_t arg, ssize_t *length)
{
	if ((char *)arg == NULL)
	{
		*length = ft_putstr("(nil)");
		return ;
	}
	*length = ft_putstr("0x");
	if (*length == -1)
		return ;
	ft_putnbr_ul(arg, "0123456789abcdef", length);
}

void	ft_checkarg(const char c, va_list arg, ssize_t *length)
{
	ssize_t	tmp;

	tmp = 0;
	if (c == 'c')
		tmp = ft_putchar((unsigned char)va_arg(arg, int));
	else if (c == 's')
		tmp = ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		ft_printmemory((size_t)va_arg(arg, size_t), &tmp);
	else if (c == 'd' || c == 'i')
		ft_putnbr_base(va_arg(arg, int), "0123456789", &tmp);
	else if (c == 'u')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789", &tmp);
	else if (c == 'x')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef", &tmp);
	else if (c == 'X')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF", &tmp);
	else if (c == '%')
		tmp += ft_putchar('%');
	else if (c == 0)
		tmp = -1;
	if (tmp == -1)
		*length = tmp;
	else
		*length += tmp;
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	va_list	args;
	ssize_t	length;

	if (!str)
		return (-1);
	i = 0;
	length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			if (ft_putchar(str[i]) == -1)
				return (va_end(args), -1);
			length++;
		}
		else
			ft_checkarg(str[++i], args, &length);
		if (length == -1)
			break ;
		i++;
	}
	return (va_end(args), length);
}
