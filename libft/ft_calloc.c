/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:40:34 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/22 18:55:37 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long long	sz;
	void				*data;

	sz = count * size;
	if (sz > 0xffffffff)
		return (NULL);
	data = malloc((size_t)sz);
	if (!data)
		return (NULL);
	(void)ft_bzero(data, (size_t)sz);
	return (data);
}
