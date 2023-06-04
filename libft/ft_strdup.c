/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:59:24 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/22 19:15:56 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*cpy;

	len = ft_strlen(s1);
	cpy = (char *)ft_calloc(len + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	(void)ft_strlcpy(cpy, s1, len + 1);
	return (cpy);
}
