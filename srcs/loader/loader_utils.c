/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/23 20:23:13 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

//====< check_space >===========================================================
int	check_unit(char **map, int row, int colum)
{
	if (!strchr(" 012NSWE", map[row][colum]))
		return (false);
	if (!row || !colum || !map[row + 1] || !map[row][colum + 1])
		return (false);
	else if (map[row][colum - 1] == ' ' || map[row][colum + 1] == ' ')
		return (false);
	else if (ft_strlen(map[row - 1]) < colum + 1
			|| ft_strlen(map[row + 1]) < colum + 1)
		return (false);
	else if (map[row - 1][colum] == ' ' || map[row + 1][colum] == ' ')
		return (false);
	return (true);
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
	if (data == NULL)
		return (NULL);
	while (++i < 4)
	{
		if (data->wall[i])
			mlx_delete_texture(data->wall[i]);
	}
	i = -1;
	while(data->map[++i])
		free(data->map[i]);
	free(data->map);
	return (NULL);
}
