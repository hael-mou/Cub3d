/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:56:47 by hael-mou          #+#    #+#             */
/*   Updated: 2023/09/23 11:17:57 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_strlen(const char *string)
{
	int32_t	len;

	len = 0;
	while (string && string[len] != '\0')
		len++;
	return (len);
}
