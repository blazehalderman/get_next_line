/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhalderm <bhalderm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:06:59 by bhalderm          #+#    #+#             */
/*   Updated: 2017/12/06 18:22:08 by bhalderm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	find_nl(int fd, char **str, char **line)
{
	char *point;
	char *delmem;

	if ((point = ft_strchr(str[fd], '\n')))
	{
		delmem = str[fd];
		*point = '\0';
		*line = ft_strdup(str[fd]);
		str[fd] = ft_strdup(point + 1);
		ft_strdel(&delmem);
		return (1);
	}
	else if (*str[fd])
	{
		*line = ft_strdup(str[fd]);
		str[fd] = ft_strnew(0);
		return (1);
	}
	return (0);
}

static	int	ft_readfile(int fd, char **str)
{
	char	*pylon;
	char	*delmem;
	int		ret;

	pylon = ft_strnew(BUFF_SIZE);
	while ((ret = (read(fd, pylon, BUFF_SIZE))) > 0)
	{
		if (!str[fd])
			str[fd] = ft_strdup(pylon);
		else
		{
			delmem = str[fd];
			str[fd] = ft_strjoin(str[fd], pylon);
			ft_strdel(&delmem);
		}
		ft_bzero(pylon, BUFF_SIZE);
	}
	ft_strdel(&pylon);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static	char	*str[4824];

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	if (ft_readfile(fd, &str[fd]) < 0)
		return (-1);
	if (find_nl(fd, &str[fd], line) == 1)
		return (1);
	return (0);
}
