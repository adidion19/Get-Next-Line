/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:44:12 by adidion           #+#    #+#             */
/*   Updated: 2020/12/07 10:44:24 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = 0;
	}
}

static int	ft_line(char **s, char **line, int fd)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		if (!(*line = ft_substr(*s, 0, len)) ||
				!(tmp = ft_strdup(&((*s)[len + 1]))))
		{
			free(*s);
			return (-1);
		}
		free(s[fd]);
		s[fd] = tmp;
		//if ((s[fd])[0] == '\0')
			//ft_strdel(s);
	}
	else
	{
		if (!(*line = ft_strdup(s[fd])))
		{
			free(*s);
			return (-1);
		}
		//ft_strdel(s);
	}
	return (1);
}

static int		ft_return(char **s, char **line, int i, int fd)
{
	if (i < 0)
		return (-1);
	if (i == 0 && s[fd] == 0)
		return (0);
	else
		return (ft_line(&s[fd], line, fd));
}

int get_next_line(int fd, char **line)
{
	static char *s[OPEN_MAX];
	char *temp;
	char buff[BUFFER_SIZE + 1];
	int i;

	if (fd < 0 || fd > OPEN_MAX || 1 > BUFFER_SIZE || line == 0)
		return (-1);
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (!s[fd])
		{
			if (!(s[fd] = ft_strdup(buff)))
				return (-1);
		}
		else
		{
			if (!(temp = ft_strjoin(s[fd], buff)))
			{
				free(s[fd]);
				return (-1);
			}
			free(s[fd]);
			s[fd] = ft_strdup(temp);
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (ft_return(s, line, i, fd));
}
