/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_converts_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:41:34 by dderny            #+#    #+#             */
/*   Updated: 2024/12/06 15:07:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>

char	*convertnbr(va_list ap, t_pflag ptype, int *len)
{
	char		*str;
	t_ltoainfo	info;
	long long	nbr;

	if (ptype.flag == F_DECIMAL || ptype.flag == F_INT)
		nbr = (long long)va_arg(ap, int);
	if (ptype.flag == F_UNSIGNED)
		nbr = (long long)va_arg(ap, unsigned int);
	info = (t_ltoainfo){{BASE10, 10}, 0, 0, 0, NULL};
	if (ptype.atributs[F_PLUS])
		info.sign = '+';
	if (ptype.atributs[F_SPACE])
		info.sign = ' ';
	if (ptype.atributs[F_POINT])
		info.zeronbr = 1;
	if (ptype.atributs[F_ZERO] || ptype.atributs[F_POINT])
		info.zeros = ptype.min;
	str = ft_lltoa_base(nbr, info, len);
	return (str);
}

char	*converthexa(long long nbr, t_nbrbase base, t_pflag ptype, int *len)
{
	char		*str;
	t_ltoainfo	info;

	info = (t_ltoainfo){base, 0, 0, 0, NULL};
	if (ptype.atributs[F_TAG])
		info.prefix = base.str + base.len;
	if (ptype.atributs[F_POINT])
		info.zeronbr = 1;
	if (ptype.atributs[F_ZERO] || ptype.atributs[F_POINT])
		info.zeros = ptype.min;
	if (ptype.flag != F_HEXAL && ptype.flag != F_HEXAU)
	{
		if (ptype.atributs[F_SPACE])
			info.sign = ' ';
		if (ptype.atributs[F_PLUS])
			info.sign = '+';
	}
	if (ptype.flag == F_POINTER)
		str = ft_ultoa_base(nbr, info, len);
	else
		str = ft_lltoa_base(nbr, info, len);
	return (str);
}

char	*convertpointer(va_list ap, t_pflag ptype, int *len)
{
	__uint64_t pt;

	pt = (__uint64_t)va_arg(ap, void *);
	if (!pt)
	{
		*len = 5;
		return (ft_strdup("(nil)"));
	}
	ptype.atributs[F_TAG] = 1;
	return (converthexa(pt, (t_nbrbase){BASE16L, 16}, ptype, len));
}

char	*convertchar(char c, int *len)
{
	char	*res;

	*len = 1;
	res = ft_calloc(2, sizeof(char));
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
}

char	*convertstr(va_list ap, t_pflag ptype, int *len)
{
	char	*cpystr;
	char	*res;
	int		strlen;

	cpystr = NULL;
	cpystr = (char *)va_arg(ap, char *);
	if (!cpystr)
	{
		if (ptype.atributs[F_POINT])
		{
			*len = 0;
			return (ft_strdup(""));
		}
		*len = 6;
		return (ft_strdup("(null)"));
	}
	strlen = ft_strlen(cpystr);
	if (ptype.atributs[F_POINT] && ptype.flag != F_CHAR && strlen > ptype.min)
		strlen = ptype.min;
	res = ft_calloc(strlen + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, cpystr, strlen + 1);
	*len = strlen;
	return (res);
}
