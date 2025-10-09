/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:16 by cguinot           #+#    #+#             */
/*   Updated: 2025/10/09 14:20:34 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	valid_text(char **texture, char *identifier, char *line)
{
	char	*path;
	char	*trimmed_path;
	int		fd;

	path = line + ft_strlen(identifier);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\ncannot open texture");
		free(trimmed_path);
		return (2);
	}
	close(fd);
	if (*texture != NULL)
	{
		printf("Error\ndouble path assignation");
		free(trimmed_path);
		return (2);
	}
	*texture = ft_strdup(trimmed_path);
	free(trimmed_path);
	return (1);
}

int	valid_color(t_color *color, char *line)
{
	char	**rgb;
	int		*rgb_i;
	char	*t[3];

	if (color->r != -1)
		return (printf("Error\ndouble color assignation \n"), 2);
	rgb_i = malloc(sizeof(int) * 3);
	rgb = ft_split(line + 2, ',');
	if (!rgb[2])
		return (free_tab(rgb), free(rgb_i),
			printf("Error\nnot enough color"), 2);
	t[0] = ft_strtrim(rgb[0], " \t\n\r");
	t[1] = ft_strtrim(rgb[1], " \t\n\r");
	t[2] = ft_strtrim(rgb[2], " \t\n\r");
	rgb_i[0] = ft_atoi_neuille(t[0]);
	rgb_i[1] = ft_atoi_neuille(t[1]);
	rgb_i[2] = ft_atoi_neuille(t[2]);
	if (rgb_i[0] < 0 || rgb_i[0] > 255 || rgb_i[1] < 0 || rgb_i[1] > 255
		|| rgb_i[2] < 0 || rgb_i[2] > 255)
		return (free(t[0]), free(t[1]), free(t[2]),
			free_tab(rgb), free(rgb_i), printf("Error\ncolor problem"), 2);
	color->r = rgb_i[0];
	color->g = rgb_i[1];
	color->b = rgb_i[2];
	return (free(t[0]), free(t[1]), free(t[2]), free_tab(rgb), free(rgb_i), 1);
}

int	handle_map_line(t_config *config, char *line, int textcount)
{
	if (is_map_line(line))
	{
		if (textcount == 6)
		{
			if (config->map_started == 0 || config->map_started == 1)
			{
				config->map_started = 1;
				add_map_line(config, line);
				return (0);
			}
			else if (config->map_started == 2)
			{
				return (printf("Error\nstring invalid: %smap already exist\n",
						line), 2);
			}
		}
		else
			return (printf("Error\nmap before argument or not enough arg"), 2);
	}
	else if (!is_only_whitespace(line))
		return (2);
	return (-1);
}

int	text_parse(t_config *config, char *line, int textcount)
{
	int	ret;

	if (ft_strncmp(line, "NO ", 3) == 0)
		return (valid_text(&config->no_texture, "NO ", line));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (valid_text(&config->so_texture, "SO ", line));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (valid_text(&config->we_texture, "WE ", line));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (valid_text(&config->ea_texture, "EA ", line));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (valid_color(&config->floor_color, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (valid_color(&config->ceiling_color, line));
	ret = handle_map_line(config, line, textcount);
	if (ret != -1)
		return (ret);
	if (config->map_started == 1)
		config->map_started = 2;
	return (0);
}
