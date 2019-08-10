/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyunak <vyunak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:23:41 by vyunak            #+#    #+#             */
/*   Updated: 2019/04/10 17:48:51 by vyunak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fun_get_tetri(void)
{
	char	*lb;
	int		y;
	int		x;
	int		z;

	y = 0;
	z = 0;
	lb = NULL;
	while (y < g_fi.coord_tetri[0])
	{
		get_next_line(0, &lb);
		x = 0;
		while (x < g_fi.coord_tetri[1])
		{
			(lb[x] == '*') ? (g_fi.tety[z] = y) : 0;
			(lb[x] == '*') ? (g_fi.tetx[z] = x) : 0;
			(lb[x] == '*') ? (z++) : 0;
			x++;
		}
		free(lb);
		y++;
	}
	g_fi.tetx[z] = -10;
	g_fi.tety[z] = -10;
}

int		check_to_paste(int y, int x)
{
	int i;
	int tx;
	int ty;
	int pf;

	i = 0;
	pf = 0;
	while (g_fi.tety[i] > -10 && g_fi.tetx[i] > -10)
	{
		ty = y + g_fi.tety[i];
		tx = x + g_fi.tetx[i];
		if ((ty >= 0 && ty < g_fi.coord_map[0]) && (tx >= 0 &&
			tx < g_fi.coord_map[1])
		&& ft_strchr(g_fi.pl[1], g_fi.map[ty][tx]) == NULL)
		{
			(ft_strchr(g_fi.pl[0], g_fi.map[ty][tx]) != NULL) ? pf++ : 0;
			i++;
		}
		else
			break ;
	}
	return (((g_fi.tety[i] == -10 && g_fi.tetx[i] == -10)
		&& pf == 1) ? 1 : 0);
}

int		get_min_dist(int x, int y)
{
	g_dst.i = -1;
	g_dst.len = g_dst.min_g_dst;
	while (++g_dst.i < g_fi.coord_map[0])
	{
		g_dst.i2 = -1;
		while (++g_dst.i2 < g_fi.coord_map[1])
			if (ft_strchr(g_fi.pl[1], g_fi.map[g_dst.i][g_dst.i2]))
			{
				g_dst.i3 = 0;
				while (g_fi.tety[g_dst.i3] > -10 && g_fi.tetx[g_dst.i3] > -10)
				{
					g_dst.y = g_fi.tety[g_dst.i3];
					g_dst.x = g_fi.tetx[g_dst.i3];
					g_dst.tmp_y = ((g_dst.y + y) - g_dst.i < 0) ? g_dst.i -
						y + g_dst.y : y + g_dst.y - g_dst.i;
					g_dst.tmp_x = ((g_dst.x + x) - g_dst.i2 < 0) ? g_dst.i2 -
						x + g_dst.x : x + g_dst.x - g_dst.i2;
					if (g_dst.tmp_y + g_dst.tmp_x < g_dst.len
					&& g_dst.tmp_y + g_dst.tmp_x > 0)
						g_dst.len = g_dst.tmp_y + g_dst.tmp_x;
					g_dst.i3++;
				}
			}
	}
	return (g_dst.len);
}

void	go_to_next(void)
{
	int x;
	int y;
	int	dist;

	dist = g_dst.min_g_dst;
	y = -300;
	while (y < g_fi.coord_map[0])
	{
		x = -300;
		while (x < g_fi.coord_map[1])
		{
			if (check_to_paste(y, x) == 1 && get_min_dist(x, y) < dist)
			{
				dist = get_min_dist(x, y);
				g_dst.gtn_y = y;
				g_dst.gtn_x = x;
			}
			x++;
		}
		y++;
	}
	ft_printf("%d %d\n", g_dst.gtn_y, g_dst.gtn_x);
	(g_dst.gtn_y == 0 && g_dst.gtn_x == 0) ? exit(1) : 0;
}

int		main(void)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "$$$ exec p", 9) &&
			(line[10] == '1' || line[10] == '2'))
			fl_get_pl(line);
		if (!ft_strncmp(line, "Plateau ", 8))
			get_map(line);
		if (!ft_strncmp(line, "Piece ", 6))
		{
			get_coords(line, &g_fi.coord_tetri[0], &g_fi.coord_tetri[1]);
			fun_get_tetri();
			g_dst.gtn_x = 0;
			g_dst.gtn_y = 0;
			g_dst.min_g_dst = 999999999;
			go_to_next();
		}
		if (line)
			free(line);
	}
	return (0);
}
