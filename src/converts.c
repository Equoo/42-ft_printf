/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:41:34 by dderny            #+#    #+#             */
/*   Updated: 2024/12/02 15:40:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include "libft.h"

char	*convertnbr(va_list ap, t_pflag ptype)
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
	return (str);
}

char	*converthexa(long long nbr, char *base, int baselen, t_pflag ptype)
{
	char		*str;
	t_lltoainfo	info;
	
	info = (t_lltoainfo){base, baselen, 0, 0};		
	if (ptype.atributs[F_ZERO] && ptype.atributs[F_TAG])
		info.zeros = ptype.min - 2;
	if (ptype.atributs[F_ZERO] && !ptype.atributs[F_TAG])
		info.zeros = ptype.min;
	str = ft_lltoa_base(nbr, info);
	if (str && ptype.atributs[F_TAG])
		ft_strfreejoin("0x", str, 0, 1);
	return (str);
}

char	*convertchar(char c, t_pflag ptype)
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

	cpystr = va_arg(ap, char *);
	strlen = ft_strlen(cpystr);
	if (ptype.atributs[F_POINT] && ptype.flag != F_CHAR && strlen > ptype.min)
		strlen = ptype.min;
	res = ft_calloc(strlen + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, cpystr, strlen);
	return (res);
}
