/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/20 21:37:08 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 02:25:05 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"

void	print_room(void)
{
	t_data	*d;
	t_room	*tmp;

	d = data_init();
	tmp = *(d->list_room);
	ft_putnbr(d->ant);
	ft_putchar('\n');
	while (tmp)
	{
		if (tmp == d->start)
			ft_putstr("##start\n");
		if (tmp == d->end)
			ft_putstr("##end\n");
		ft_putstr(tmp->name);
		ft_putchar(' ');
		ft_putnbr(tmp->x);
		ft_putchar(' ');
		ft_putnbr(tmp->y);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	print_pipe(void)
{
	t_data	*d;
	t_room	*tmp;
	t_room	*tmp2;
	t_pipe	*pipe_tmp;

	d = data_init();
	tmp = *(d->list_room);
	while (tmp)
	{
		pipe_tmp = tmp->pipe;
		while (pipe_tmp)
		{
			tmp2 = *(d->list_room);
			while (tmp2 && tmp2 != tmp && tmp2 != pipe_tmp->room)
				tmp2 = tmp2->next;
			if (tmp2 == NULL || tmp2 == tmp)
			{
				ft_putstr(tmp->name);
				ft_putchar('-');
				ft_putendl(pipe_tmp->room->name);
			}
			pipe_tmp = pipe_tmp->next;
		}
		tmp = tmp->next;
	}
}

void	print_lemin(int num_lemin, char *room, int i)
{
	if (i > 0)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(num_lemin);
	ft_putchar('-');
	ft_putstr(room);
	if (i < 0)
		ft_putchar('\n');
}
