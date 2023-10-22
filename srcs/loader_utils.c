/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/22 17:52:41 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define RGB(R, G, B) (R << 24 | G << 16 | B << 8 | 255)

void	*ft_calloc(size_t count, size_t size);

//==== get_next_line ===========================================================
char	*get_next_line(int fd, int index)
{
	char	*tmp;
	char	c;

	if (!read(fd, &c, 1) || c == '\n')
		return (ft_calloc((index + 1) * !(!index && c != '\n'), 1));
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
	while (++i < (int) (count * size))
		((char *) buff)[i] = 0;
	return (buff);
}

#include <stdio.h>
//==== extract_rgb_color ========================================================
int32_t	extract_rgb_color(char *line)
{
	int	r;
	int	g;
	int	b;

	while(!strchr("+-0123456789", *line))
			line++;
	r = atoi(line);
	g = atoi(strchr(line, ',') + 1);
	b = atoi(strrchr(line, ',') + 1);
	if (r * g * b < 0 || r + g + b > 765)
		return (-1);
	return (RGB(r, g, b));
}
