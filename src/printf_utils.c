/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:45:48 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 16:18:53 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

static int	numberlen(long n, int baselen, char sign)
{
	int	len;

	if (sign || n < 0 || !n)
		len++;
	while (n && ++len)
		n /= baselen;
	return (len);
}

char	*ft_lltoa_base(long n, char *base, int baselen, char sign)
{
	int			len;
	long long	nb;
	char		*str;

	len = numberlen(n, baselen, sign);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	nb = (long long)n;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	else if (sign)
		str[0] = sign;
	while ((n && nb && len--) || (!n && len--))
	{
		str[len] = base[nb % baselen];
		nb /= baselen;
	}
	return (str);
}

int	get_flag_type(char *flag, t_pflag *type)
{
	char	*sflag;
	int		tmp;

	sflag = flag;
	type->mtype = F_NONE;
	tmp = ft_strchrpos("# 0+", *flag);
	if (tmp >= 0 && flag++)
	{
		type->mtype = (t_prnt_flag)tmp;
		type->modifier = ft_atoi(flag);
		while (ft_isdigit(*flag))
			flag++;
	}
	tmp = ft_strchrpos("cspdiuxX%", *flag);
	if (tmp >= 0 && flag++)
	{
		type->type = (t_prnt_flag)(4 + tmp);
		return (flag - sflag);
	}
	return (0);
}
