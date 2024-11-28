/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:10 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 15:55:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef enum e_prnt_flag
{
	F_NONE,
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
	F_HEXAU,
	F_PERCENT,
}				t_prnt_flag;

typedef struct s_pflag
{
	t_prnt_flag	type;
	t_prnt_flag	mtype;
	int			modifier;
}				t_pflag;

char			*ft_lltoa_base(long n, char *base, int baselen, char sign);

int				get_flag_type(char *flag, t_pflag *type);

int				ft_printf(const char *, ...);