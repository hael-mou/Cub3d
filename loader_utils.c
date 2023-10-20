/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/20 16:14:08 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

//==== get_next_line ===========================================================
char	*get_next_line(int fd, int index)
{
	char	*tmp;
	char	c;

	if (!read(fd, &c, 1) || c == '\n')
		return (ft_calloc((index + 1) * (index > 2), 1));
	tmp = get_next_line(fd, index + 1);
	if (tmp)
		tmp[index] = c;
	return (tmp);
}

//==== ft_calloc ===============================================================
void	*ft_calloc(size_t count, size_t size)
{
	void	*buff;
	int		i;

	if (count <= 0 || size <= 0)
		return (NULL);
	buff = malloc(count * size);
	if (!buff)
		return (NULL);
	i = -1;
	while (++i < (count * size))
		((char *) buff)[i] = 0;
	return (buff);
}
