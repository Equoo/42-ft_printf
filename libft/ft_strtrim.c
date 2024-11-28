/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:09 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 15:24:36 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	start;
	size_t			end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isin_set(s1[start], set))
		start++;
	end = start;
	while (s1[end])
		end++;
	while (end > start && ft_isin_set(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - (size_t)start));
}
