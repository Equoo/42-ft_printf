/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 17:59:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static char	*getnumber(long nb, t_itoainfo params)
{
	char	*nbr;
	int		len;
	char	*tmp;
	
	nbr = ft_lltoa_base(nb, params.base, ft_strlen(params.base), params.sign);
	if (!nbr)
		return (NULL);
	len = ft_strlen(nbr);
	if (params.zeromin > len)
	{
		tmp = ft_calloc(params.zeromin + 1, sizeof(char));
		if (!nbr)
			return (free(nbr), NULL);
		ft_strlcpy(tmp + params.zeromin - len, nbr, params.zeromin);
		ft_memset(tmp, params.base[0], params.zeromin - len);
		free(nbr);
		nbr = tmp;
	}
	if (params.prefix)
	{
		nbr = ft_strfreejoin(params.prefix, nbr, 0, 1);
		if (!nbr)
			return (NULL);
	}
	return (nbr);
}

static char	*getconvert(va_list ap, t_pflag ptype)
{
	char	*tmp;
	char	prefix[3];
	char	sign;
	int		minzero;
	
	sign = 0;
	if (ptype.mtype == F_PLUS)
		sign = '+';
	if (ptype.mtype == F_SPACE)
		sign = ' ';
	if (ptype.mtype == F_TAG)
		ft_strlcpy(prefix, "0x", 3);
	if (ptype.mtype == F_ZERO)
		

	if (ptype.type == F_CHAR)
		tmp = ft_putchar_fd(va_arg(ap, char), 0);
	if (ptype.type == F_STRING)
		tmp = ft_putstr_fd(va_arg(ap, char *), 0);
	if (ptype.type == F_POINTER)
		tmp = getnumber((long)va_arg(ap, void *),
			(t_itoainfo){BASE16l, 0, "0x", 8});
	if (ptype.type == F_DECIMAL || ptype.type == F_INT)
	{
		tmp = getnumber(va_arg(ap, int), (t_itoainfo){BASE10, 0, NULL, sign});
	}
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
				if (!convertnjoin(ap, ptype))
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
