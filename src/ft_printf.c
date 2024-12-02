/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/12/02 14:55:59 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>

static char	*convertany(va_list ap, t_pflag ptype)
{
	char	*tmp;
	char	c;

	c = '%';
	if (ptype.flag == F_CHAR)
	{
		c = (char)va_arg(ap, char);
		tmp = ft_strdup(&c);
	}
	if (ptype.flag == F_CHAR || ptype.flag == F_STRING)
		tmp = convertanystr(ap, ptype);
	if (ptype.flag == F_POINTER)
		tmp = convertanyhexa((unsigned int)va_arg(ap, void *), BASE16l, 16,
				(t_pflag){.flag=F_POINTER, .atributs[F_TAG]=1, .atributs[F_ZERO]=1, .min=8});
	if (ptype.flag == F_DECIMAL || ptype.flag == F_INT || ptype.flag == F_UNSIGNED)
		tmp = convertanynbr(ap, ptype);
	if (ptype.flag == F_HEXAL)
		tmp = convertanyhexa(va_arg(ap, unsigned int), BASE16l, 16, ptype);
	if (ptype.flag == F_HEXAU)
		tmp = convertanyhexa(va_arg(ap, unsigned int), BASE16u, 16, ptype);
	return (justifytxt(tmp, ptype.atributs[F_MINUS], ptype.min));
}

int	ft_printf(const char *format, ...)
{
	t_pflag ptype;
	va_list	ap;
	int		i;
	int		next;
	int		count;

	i = 0;
	va_start(ap, arg1);
	while (format[i])
    {
		next = 0;
		if ((unsigned char)format[i] == '%')
		{
			next = get_flag_type(format + i, &ptype);
			if (next > 0)
				if (!convertany(ap, ptype))
					return (0);
			i += next;
		}
		else
			write(0, format[i], 1);
		i++;
		count++;
	}
	va_end(ap);
	return (count);
}
