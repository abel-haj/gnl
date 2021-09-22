/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:12:30 by abel-haj          #+#    #+#             */
/*   Updated: 2021/09/22 18:12:38 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	func(char ***line, char **left)
{
	int		nl;
	char	*tmp;

	nl = ft_strindof(*left, '\n');
	if (nl == -1)
	{
		free(**line);
		**line = ft_strdup(*left);
	}
	else
	{
		(*left)[nl] = '\0';
		free(**line);
		**line = ft_strdup(*left);
		tmp = *left;
		*left = ft_strdup((*left) + nl + 1);
		free(tmp);
		return (1);
	}
	free(*left);
	*left = NULL;
	return (0);
}

static int	func2(char buff[101], char ***line, char **left, int r)
{
	int		nl;
	char	*tmp;

	buff[r] = '\0';
	nl = ft_strindof(buff, '\n');
	if (nl != -1)
	{
		buff[nl] = '\0';
		tmp = **line;
		**line = ft_strjoin(**line, buff);
		free(tmp);
		*left = ft_strdup(buff + nl + 1);
		return (1);
	}
	else
	{
		**line = ft_strjoin(**line, buff);
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	int			r;
	static char	*left;
	char		buff[101];

	*line = ft_strdup("");
	if (fd < 0 || read(fd, NULL, 0) < 0 || !line || *line == NULL)
		return (-1);
	if (left)
		if (func(&line, &left))
			return (1);
	r = read(fd, buff, 100);
	while (r > 0)
	{
		if (func2(buff, &line, &left, r))
			return (1);
		r = read(fd, buff, 100);
	}
	return (r);
}
