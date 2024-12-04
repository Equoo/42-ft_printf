/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/12/04 14:43:27 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>

# define BASE10 "0123456789"
# define BASE16l "0123456789abcdef0x"
# define BASE16u "0123456789ABCDEF0X"

# define ATRIBUTES "# 0+-."
# define ATRIBUTESLEN 6
# define FLAGS "cspdiuxX%"
typedef enum e_prnt_flag
{
	F_TAG,
	F_SPACE,
	F_ZERO,
	F_PLUS,
	F_MINUS,
	F_POINT,
	F_CHAR,
	F_STRING,
	F_POINTER,
	F_DECIMAL,
	F_INT,
	F_UNSIGNED,
	F_HEXAL,
	F_HEXAU,
	F_PERCENT,
	F_NONE
}				t_prnt_flag;

typedef struct s_pflag
{
	t_prnt_flag	flag;
	int			atributs[ATRIBUTESLEN];
	int			min;
}				t_pflag;

typedef struct s_lltoainfo
{
	char		*base;
	int			baselen;
	char		sign;
	int			zeros;
	char		*prefix;
}				t_lltoainfo;

typedef struct s_pdata
{
	int			last;
	int			next;
	int			count;
	char		*str;
	int			strlen;
}				t_pdata;

char			*ft_lltoa_base(long long n, t_lltoainfo info);
char			*ft_strfreejoin(const char *s1, const char *s2, int free1,
					int free2);
char			*justifytxt(char *str, int reverse, int len);
int				get_flag_type(char *flag, t_pflag *type);

char			*convertnbr(va_list ap, t_pflag ptype);
char			*converthexa(long long nbr, char *base, int baselen,
					t_pflag ptype);
char			*convertchar(char c);
char			*convertstr(va_list ap, t_pflag ptype);

int				vft_printf(const char *format, va_list ap);
int				ft_printf(const char *, ...);

#endif