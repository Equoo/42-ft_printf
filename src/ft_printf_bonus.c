/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/12/05 16:55:05 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "unistd.h"
#include <stdlib.h>

static char	*convertany(va_list ap, t_pflag pt)
{
	char	*tmp;

	if (pt.flag == F_PERCENT)
		return (convertchar('%'));
	if (pt.flag == F_CHAR)
		tmp = convertchar((char)va_arg(ap, int));
	if (pt.flag == F_STRING)
		tmp = convertstr(ap, pt);
	if (pt.flag == F_POINTER)
	{
		pt.atributs[F_TAG] = 1;
		tmp = converthexa((unsigned long)va_arg(ap, void *), BASE16l, 16, pt);
	}
	if (pt.flag == F_DECIMAL || pt.flag == F_INT || pt.flag == F_UNSIGNED)
		tmp = convertnbr(ap, pt);
	if (pt.flag == F_HEXAL)
		tmp = converthexa((long long)va_arg(ap, unsigned int), BASE16l, 16, pt);
	if (pt.flag == F_HEXAU)
		tmp = converthexa((long long)va_arg(ap, unsigned int), BASE16u, 16, pt);
	if (pt.atributs[F_POINT] || pt.atributs[F_ZERO])
		pt.min = 0;
	return (justifytxt(tmp, pt.atributs[F_MINUS], pt.min));
}

static int	get_flag_type(char *flag, t_pflag *type)
{
	char	*sflag;
	int		tmp;

	sflag = flag;
	tmp = ft_strchrpos(ATRIBUTES, *flag);
	while (tmp >= 0 && flag++)
	{
		type->atributs[tmp] = 1;
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

static int	processflag(va_list ap, char *format, char **returnstr)
{
	t_pflag	pt;
	int		next;
	char	*str;

	next = 0;
	if ((unsigned char)*format == '%')
	{
		pt = (t_pflag){};
		next = get_flag_type((char *)format + 1, &pt);
		if (next > 0)
		{
			str = convertany(ap, pt);			
			*returnstr = str;
			if (!str)
				return (-1);
		}
	}
	return (next);
}

int	vft_printf(const char *format, va_list ap)
{
	int		i;
	t_pdata	data;

	if (!format)
		return (-1);
	i = 0;
	data.count = 0;
	data.last = 0;
	data.str = NULL;
	while (format[i])
	{
		data.next = processflag(ap, (char *)format + i, &data.str);
		if (data.next == -1)
			return (-1);
		else if (data.next)
		{
			write(STDOUT_FILENO, format + data.last, i - data.last);
			data.strlen = ft_strlen(data.str);
			data.count += i - data.last + data.strlen;
			write(STDOUT_FILENO, data.str, data.strlen);
			free(data.str);
			i = i + data.next;
			data.last = i + 1;
		}
		i++;
	}
	data.count += i - data.last;
	write(STDOUT_FILENO, format + data.last, i - data.last);
	return (data.count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = vft_printf(format, ap);
	va_end(ap);
	return (count);
}
