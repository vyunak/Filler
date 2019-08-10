/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_part_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyunak <vyunak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:59:01 by vyunak            #+#    #+#             */
/*   Updated: 2019/04/10 17:06:03 by vyunak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	*ft_free_arr(char ***str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *str;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (NULL);
}

void	get_coords(char *line, int *n1, int *n2)
{
	int		i;
	char	*n;

	i = ft_strlen(ft_strchr(line, ' ') + 1) - ft_strlen(ft_strchr(line, ':'));
	n = ft_strncpy(ft_strnew(i), ft_strchr(line, ' ') + 1, i);
	*n1 = ft_atoi(n);
	*n2 = ft_atoi(ft_strchr(n, ' ') + 1);
	if (n != NULL)
		free(n);
}

void	fl_get_pl(char *line)
{
	g_fi.pl[0][0] = (line[10] == '1' ? 'O' : 'X');
	g_fi.pl[0][1] = (line[10] == '1' ? 'o' : 'x');
	g_fi.pl[0][2] = '\0';
	g_fi.pl[1][0] = (line[10] == '2' ? 'O' : 'X');
	g_fi.pl[1][1] = (line[10] == '2' ? 'o' : 'x');
	g_fi.pl[1][2] = '\0';
}

void	get_map(char *line)
{
	int		i;
	int		e;
	char	*str;

	i = 0;
	e = 0;
	get_coords(line, &g_fi.coord_map[0], &g_fi.coord_map[1]);
	if (g_fi.map)
		ft_free_arr(&g_fi.map);
	g_fi.map = (char**)malloc(sizeof(char*) * (g_fi.coord_map[0] + 1));
	g_fi.map[g_fi.coord_map[0]] = NULL;
	get_next_line(0, &str);
	free(str);
	while (i < g_fi.coord_map[0])
	{
		get_next_line(0, &str);
		g_fi.map[e] = ft_strcpy(ft_strnew(ft_strlen(ft_strchr(str, ' ') +
			1)), ft_strchr(str, ' ') + 1);
		e++;
		i++;
		free(str);
	}
}
