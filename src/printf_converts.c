/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_converts_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:41:34 by dderny            #+#    #+#             */
/*   Updated: 2024/12/05 17:01:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	*convertnbr(va_list ap, t_pflag ptype)
{
	char		*str;
	t_ltoainfo	info;
	long long	nbr;

	if (ptype.flag == F_DECIMAL || ptype.flag == F_INT)
		nbr = (long long)va_arg(ap, int);
	if (ptype.flag == F_UNSIGNED)
		nbr = (long long)va_arg(ap, unsigned int);
	info = (t_ltoainfo){BASE10, 10, 0, 0, 0, NULL};
	if (ptype.atributs[F_PLUS])
		info.sign = '+';
	if (ptype.atributs[F_SPACE])
		info.sign = ' ';
	if (ptype.atributs[F_POINT])
		info.zeronbr = 1;
	if (ptype.atributs[F_ZERO] || ptype.atributs[F_POINT])
		info.zeros = ptype.min;
	str = ft_lltoa_base(nbr, info);
	return (str);
}

char	*converthexa(long long nbr, char *base, int baselen, t_pflag ptype)
{
	char		*str;
	t_ltoainfo	info;

	info = (t_ltoainfo){base, baselen, 0, 0, 0, NULL};
	if (ptype.atributs[F_TAG])
		info.prefix = base + baselen;
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
		str = ft_ultoa_base(nbr, info);
	else
		str = ft_lltoa_base(nbr, info);
	return (str);
}

char	*convertchar(char c)
{
	char	*res;

	res = ft_calloc(2, sizeof(char));
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
}

char	*convertstr(va_list ap, t_pflag ptype)
{
	char	*cpystr;
	char	*res;
	int		strlen;

	cpystr = NULL;
	cpystr = (char *)va_arg(ap, char *);
	if (!cpystr)
		return (NULL);
	strlen = ft_strlen(cpystr);
	if (ptype.atributs[F_POINT] && ptype.flag != F_CHAR && strlen > ptype.min)
		strlen = ptype.min;
	res = ft_calloc(strlen + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, cpystr, strlen + 1);
	return (res);
}
