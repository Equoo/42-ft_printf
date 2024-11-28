/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:25:09 by dderny            #+#    #+#             */
/*   Updated: 2024/11/28 15:41:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchrpos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && (unsigned char)s[i] != (unsigned char)c)
		i++;
	if (!s[i] && (unsigned char)c != '\0')
		return (-1);
	return (i);
}