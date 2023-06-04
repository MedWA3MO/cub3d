/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:33:34 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/22 19:16:20 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*alloc;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	alloc = (char *)ft_calloc(len, sizeof(char));
	if (!alloc)
		return (NULL);
	(void)ft_strlcpy(alloc, s1, len);
	(void)ft_strlcat(alloc, s2, len);
	return (alloc);
}
