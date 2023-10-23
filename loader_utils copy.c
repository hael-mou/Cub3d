/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/23 16:37:46 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define RGB(R, G, B) (R << 24 | G << 16 | B << 8 | 255)

//====< get_line >==============================================================
char	*get_line(int fd, int index)
{
	char	*tmp;
	char	c;

	if (!read(fd, &c, 1) || c == '\n')
		return (ft_calloc((index + 1) * !(!index && c != '\n'), 1));
	tmp = get_line(fd, index + 1);
	if (tmp)
		tmp[index] = c;
	return (tmp);
}

//====< clean_data >=============================================================
void	*clean_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_delete_texture(data->wall[i]);
	i = -1;
	while(data->map[++i])
		free(data->map[i]);
	free(data->map);
	return (NULL);
}
//==== extract_rgb_color ========================================================
/*int32_t	extract_rgb_color(char *line)
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
}*/
