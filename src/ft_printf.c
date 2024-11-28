/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 16:21:17 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	ft_printf(const char *format, ...)
{
	t_pflag ptype;
	va_list	ap;
	int		i;
	int		tmp;

	i = 0;
	va_start(ap, arg1); 
	while (format[i])
    {
		tmp = 0;
		if ((unsigned char)format[i] == '%')
		{
			tmp = get_flag_type(format + i, &ptype);
			if (tmp > 0)
				va_arg(ap, int);
			i += tmp;
		}
		else
			write(0, format[i], 1);
		i++;
	}
	va_end(ap);
}