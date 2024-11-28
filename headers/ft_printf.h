/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 17:40:22 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# define BASE10  "0123456789"
# define BASE16l  "0123456789abcdef"
# define BASE16u  "0123456789ABCDEF"
typedef enum e_prnt_flag
{
	F_TAG,
	F_SPACE,
	F_ZERO,
	F_PLUS,
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
	t_prnt_flag	type;
	t_prnt_flag	mtype;
	int			modifier;
}				t_pflag;

typedef struct s_itoainfo
{
	char	*base;
	char	sign;
	char	*prefix;
	int		zeromin;
}				t_itoainfo;

char			*ft_lltoa_base(long n, char *base, int baselen, char sign);
char			*ft_strfreejoin(const char *s1, const char *s2, int free1, int free2);

int				get_flag_type(char *flag, t_pflag *type);

int				ft_printf(const char *, ...);

#endif