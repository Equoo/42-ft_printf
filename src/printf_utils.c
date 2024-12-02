/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:45:48 by dderny            #+#    #+#             */
/*   Updated: 2024/12/02 15:29:15 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	numberlen(long n, int baselen, char sign)
{
	int	len;

	if (sign || n < 0 || !n)
		len++;
	while (n && ++len)
		n /= baselen;
	return (len);
}

char	*ft_lltoa_base(long long n, t_lltoainfo info)
{
	int			len;
	long long	nb;
	char		*str;

	len = numberlen(n, info.baselen, info.sign) + info.zeros;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memset(str, info.base[0], info.zeros + 1);
	nb = n;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	else if (info.sign)
		str[0] = info.sign;
	while ((n && nb && len--) || (!n && len--))
	{
		str[len] = info.base[nb % info.baselen];
		nb /= info.baselen;
	}
	return (str);
}

char	*justifytxt(char *str, int reverse, int len)
{
	int		strlen;
	char	*res;

	if (!str)
		return (NULL);
	strlen = ft_strlen(str);
	if (len <= strlen)
		return (str);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (reverse)
	{
		ft_memset(res, 32, len - strlen);
		ft_strlcpy(res + len - strlen, str, strlen + 1);
	}
	else
	{
		ft_memset(res + strlen, 32, len - strlen);
		ft_strlcpy(res, str, len + 1);
	}
	return (res);
}

int	get_flag_type(char *flag, t_pflag *type)
{
	char	*sflag;
	int		tmp;

	sflag = flag;
	tmp = ft_strchrpos(ATRIBUTES, *flag);
	while (tmp >= 0 && flag++)
	{
		type->atributs[tmp];
		tmp = ft_strchrpos(ATRIBUTES, *flag);
	}
	type->min = ft_atoi(flag);
	while (ft_isdigit(*flag))
		flag++;
	type->flag = F_NONE;
	tmp = ft_strchrpos(FLAGS, *flag);
	if (tmp >= 0 && flag++)
	{
		type->flag = (t_prnt_flag)(ATRIBUTESLEN + tmp);
		return (flag - sflag);
	}
	return (0);
}

char	*ft_strfreejoin(const char *s1, const char *s2, int free1, int free2)
{
	char	*str;
	str = ft_strjoin(s1, s2);
	if (free1)
		free(s1);
	if (free2)
		free(s2);
	if (!str)
		return (NULL);
	return (str);
}
