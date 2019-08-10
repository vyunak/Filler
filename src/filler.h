/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyunak <vyunak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:49:55 by vyunak            #+#    #+#             */
/*   Updated: 2019/04/10 17:03:14 by vyunak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/libft.h"

typedef	struct	s_filler {
	int			coord_map[2];
	int			coord_tetri[2];
	char		**map;
	char		pl[3][3];
	int			tety[4096];
	int			tetx[4096];
}				t_filler;

typedef	struct	s_distans {
	int			tmp_y;
	int			tmp_x;
	int			gtn_y;
	int			gtn_x;
	int			y;
	int			x;
	int			i;
	int			i2;
	int			i3;
	int			min_g_dst;
	int			len;
}				t_distans;

t_filler		g_fi;
t_distans		g_dst;

void			*ft_free_arr(char ***str);
void			get_coords(char *line, int *n1, int *n2);
void			fl_get_pl(char *line);
void			get_map(char *line);
void			fun_get_tetri(void);
int				check_to_paste(int y, int x);
int				get_min_dist(int x, int y);
void			go_to_next(void);

#endif
