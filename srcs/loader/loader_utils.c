/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/23 17:51:11 by oezzaou          ###   ########.fr       */
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
int	check_space(char **map, int i, int j)
{
	if (!i || !j || !map[i + 1] || !map[i][j + 1])
		return (false);
	else if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (false);
	else if (ft_strlen(map[i - 1]) < j + 1 || ft_strlen(map[i + 1]) < j + 1)
		return (false);
	else if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
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
	while (++i < 4)
		mlx_delete_texture(data->wall[i]);
	i = -1;
	while(data->map[++i])
		free(data->map[i]);
	free(data->map);
	return (NULL);
}
