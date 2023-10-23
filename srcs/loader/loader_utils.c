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
// #define RGB(R, G, B) (R << 24 | G << 16 | B << 8 | 255)

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

//====< is_map >================================================================
int	is_map(char *line)
{
	int	index;

	index = 0;
	if (line == NULL)
		return (true);
	while (line[index] && strchr(" 012NSEW", line[index]))
		index++;
	return (index && line[index] == '\0');
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
