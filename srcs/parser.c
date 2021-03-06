/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 20:17:54 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 21:26:07 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"
#include "libft.h"

int		parse_entry(void)
{
	char	*line;
	char	**tmp;
	int		ret;

	line = NULL;
	add_nb_ant();
	while (42)
	{
		if ((ret = -1) && line)
			ft_strdel(&line);
		if (get_next_line(FD, &line) <= 0)
			return (finish_read(&line));
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			ret = add_position(&line, FD, START);
		else if (line[0] == '#')
			continue ;
		else if ((tmp = ft_strsplit(line, ' ')) && tmp[1])
			ret = add_room(tmp, 0, 0);
		else if (!free_tab(tmp) && !(tmp = NULL)
			&& (tmp = ft_strsplit(line, '-')) && tmp[1])
			ret = add_pipe(tmp);
		if (ret == -1)
			return (-1);
	}
}

int		add_position(char **line, int fd, int pos)
{
	char	**tmp;
	int		ret;

	if (!ft_strcmp(*line, "##end"))
		pos = END;
	ret = -1;
	ft_strdel(line);
	if ((get_next_line(fd, line) > 0) && (tmp = ft_strsplit(*line, ' '))
		&& tmp[1])
		ret = add_room(tmp, pos, 0);
	return (ret);
}

int		add_room(char **room, int pos, int i)
{
	int		x;
	int		y;
	t_data	*d;
	t_room	*new;

	d = data_init();
	while (room[i])
		i++;
	if (i != 3 || !ft_is_number(room[1]) || !ft_is_number(room[2]))
		return (-1);
	if ((pos == START && d->start != NULL) || (pos == END && d->end != NULL))
		return (-1);
	x = ft_atoi(room[1]);
	y = ft_atoi(room[2]);
	free(room[1]);
	free(room[2]);
	if ((new = list_add_room(room[0], x, y)) == NULL)
		return (-1);
	if (pos == START && d->start == NULL)
		d->start = new;
	else if (pos == END && d->end == NULL)
		d->end = new;
	free(room);
	return (0);
}

int		add_pipe(char **pipe)
{
	int		i;

	i = 0;
	while (pipe[i])
		i++;
	if (i != 2)
	{
		free_tab(pipe);
		pipe = NULL;
		return (-1);
	}
	if (list_add_pipe(pipe[0], pipe[1]) == -1)
	{
		free_tab(pipe);
		pipe = NULL;
		return (-1);
	}
	free_tab(pipe);
	return (0);
}

int		finish_read(char **line)
{
	ft_strdel(line);
	return (-1);
}
