/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:53:15 by adidion           #+#    #+#             */
/*   Updated: 2020/12/14 17:21:56 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_newline(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_static(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * (ft_strlen(s) - i))))
		get_next_line(-1, &s);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*ft_line(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		get_next_line(-1, &s);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_protect(char *s, char *buff)
{
	if (s)
		free(s);
	if (buff)
		free(buff);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char *s;
	char		*buff;
	int			i;

	i = 1;
	buff = 0;
	if (fd < 0 || fd > OPEN_MAX || 1 > BUFFER_SIZE || line == 0 ||
	BUFFER_SIZE >= INT_MAX
	|| (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (ft_protect(buff, s));
	while (!ft_newline(s) && i != 0)
	{
		if ((i = read(fd, buff, BUFFER_SIZE)) == -1)
			return (ft_protect(buff, s));
		buff[i] = '\0';
		if (!(s = ft_strjoin(s, buff)))
			return (ft_protect(buff, s));
	}
	free(buff);
	*line = ft_line(s);
	s = ft_static(s);
	return (ft_return(i, s));
}
