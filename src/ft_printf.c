/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/11/29 13:11:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static char	*justifytxt(char fill);

static char	*convertanynbr(va_list ap, t_pflag ptype)
{
	char		*str;
	t_lltoainfo	info;
	long long	nbr;
	
	if (ptype.flag == F_DECIMAL || ptype.flag == F_INT)
		nbr = (long long)va_arg(ap, int);
	if (ptype.flag == F_UNSIGNED)
		nbr = (long long)va_arg(ap, unsigned int);
	info = (t_lltoainfo){BASE10, 10, 0, 0};
	if (ptype.atributs[F_PLUS])
		info.sign = '+';
	if (ptype.atributs[F_SPACE])
		info.sign = ' ';
	if (ptype.atributs[F_ZERO])
		info.zeros = ptype.min;
	str = ft_lltoa_base(nbr, info);
	if (!str)
		return (NULL);
	return (justifytxt(ptype.atributs[F_MINUS], ptype.min, ptype.atributs[F_SPACE]))
}

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
	if (ptype.flag == F_CHAR)
		tmp = ft_strdup(&c);
	if (ptype.flag == F_STRING)
		tmp = ft_strdup(va_arg(ap, char *));
	if (ptype.flag == F_STRING)
		tmp = ft_strdup(va_arg(ap, char *));
	if (ptype.flag == F_POINTER)
		tmp = converthexa((unsigned int)va_arg(ap, void *));
	if (ptype.flag == F_DECIMAL || ptype.flag == F_INT || ptype.flag == F_UNSIGNED)
		tmp = convertanynbr(ap, ptype);
	if (ptype.flag == F_HEXAL || ptype.flag == F_HEXAU)
		tmp = converthexa(va_arg(ap, unsigned int), ptype);
	return (tmp);
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
