/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:49:24 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/03 09:53:45 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\r' || *str == '\v' || *str == '\f')
		++str;
	if (*str == '-' && ++str)
		sign = -1;
	else if (*str == '+')
		++str;
	res = 0;
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str++ - '0');
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
			return (-1);
	}
	return ((int)(res * sign));
}
