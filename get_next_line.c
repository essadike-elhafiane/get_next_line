/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:47:45 by eelhafia          #+#    #+#             */
/*   Updated: 2022/11/20 19:56:28 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*alloc(size_t size)
{
	unsigned char	*pt;
	size_t			i;

	i = 0;
	pt = malloc(size);
	if (pt == NULL)
		return (NULL);
	while (i < size)
	{
		pt[i] = 0;
		i++;
	}
	return (pt);
}

char	*nexline(char *save)
{
	char	*defnext;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (free(save), NULL);
	defnext = alloc((ft_strlen(save) - i +1) * sizeof(char));
	if (!defnext)
		return (free(save), NULL);
	i++;
	while (save[i])
		defnext[j++] = save[i++];
	defnext[j] = '\0';
	free(save);
	return (defnext);
}

char	*linre(char *save)
{
	char	*res;
	int		i;
	int		a;

	a = 0;
	i = 0;
	while ((save[i] && save[i] != '\n'))
		i++;
	res = alloc((i +2) * sizeof(char));
	if (!res)
		return (NULL);
	if (save[i] == '\n')
		i++;
	while (save[a] && a < i)
	{
		res[a] = save[a];
		a++;
	}
	res[a] = '\0';
	return (res);
}

char	*readline(char *save, int fd)
{
	int		i;
	char	*rd;

	i = 1;
	rd = alloc((BUFFER_SIZE +1) * sizeof(char));
	if (!rd)
		return (NULL);
	while (i > 0 && !(ft_strchr(save, '\n')))
	{
		i = read(fd, rd, BUFFER_SIZE);
		if ((i < 0) || (i == 0 && !save) || (i == 0 && save[0] == 0))
			return (free(rd), free(save), NULL);
		rd[i] = '\0';
		save = ft_strjoin(save, rd);
	}
	free(rd);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = readline(save, fd);
	if (!save)
		return (NULL);
	res = linre(save);
	save = nexline(save);
	return (res);
}
