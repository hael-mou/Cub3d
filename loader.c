#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define OTHER 1
#define MAP 2

//==============================================================================
char	*get_next_line(int fd, int index);
void	*ft_calloc(size_t count, size_t size);
//==============================================================================
char	**parse_scene_file(int fd, int index);
t_data	*loader(char *file);
int		load_textures(char **lines, t_textures **textrs)

//==== main ====================================================================
int	main(int ac, char **av)
{
	t_data	*data;

	data = loader(av[1]);
	return (EXIT_SUCCESS);
}

//==============================================================================
t_data	*loader(char *file)
{
	t_data	*data;
	int		fd;
	char	**lines;

	data = malloc(sizeof(t_data));
	fd = open(av[1], O_RDONLY);
	if (!data || fd < 0)
		return (free(data), NULL);
	lines = parse_scene_file(fd, 0, OTHER); 
	if (!lines)
		return (NULL);
//	loead_textures(data->texture, lines);
//	data->map = load_map(lines);
//	data->
	return (data);
}

//==== parse_===================================================================
char	**parse_scene_file(int fd, int index)
{
	char	**map;
	char	*line;

	line = get_next_line(fd, 0);
	if (!is_valid_line(line))
		return (NULL);
	if (!line)
		return (ft_calloc((index + 1) * (index > 2), sizeof(char *)));
	map = parse_scene_file(fd, index + 1);
	if (!map)
		return (free(line), NULL);
	map[index] = line;
	return (map);
}

//==== is_valid_line ===========================================================
int	is_valid_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (strstr(line, "NO") || strstr(line, "SO") || strstr(line, "WE") || strstr(line, "EA"))
			return (check_textures(line));
		else
			return (check_map_line(line));
	}
}

//==== check_textures ==========================================================
int	check_textures(char *line)
{
	char	*path;

	path = strchr(line, '/');
	if (!line || !path)
		return (0);
	if (access(path + 1, F_OK) == 0)
		return (0);
	return (1);
}

//==== is_valid ================================================================
int	check_map_line(char *colom)
{
	int	i;

	if (!colom)
		return (1);
	i = -1;
	if (colom[++i] != '1')
		return (0);
	while (colom[++i] && strchr("012", colom[i]))
		;
	return (!colom[i] && colom[i - 1] == '1');
}
