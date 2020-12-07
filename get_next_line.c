/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:53:15 by adidion           #+#    #+#             */
/*   Updated: 2020/12/07 17:35:58 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_newline(char *s)
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

char *ft_static(char *s)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] == '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * ((ft_strlen(s) - i) + 1))))
		return (0);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char *ft_line(char *s)
{
	int i;
	char *str;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (!(str = malloc (sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int get_next_line(int fd, char **line)
{
	static char *s;
	char *buff;
	int i;

	i = 1;
	if (fd < 0 || fd > OPEN_MAX || 1 > BUFFER_SIZE || line == 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (ft_newline(s) == 0 && i != 0)
	{
		if ((i = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[i] = '\0';
		s = join_str(s, buff);
	}
	free(buff);
	*line = ft_line(s);
	s = ft_static(s);
	if (i == 0)
		return (0);
	return (1);
}

int main()
{
	int ret1;
	int fd1;
	char *line1;
	//int ret2;
	//int fd2;
	//char *line2;

	fd1 = open("test.txt", O_RDONLY);
	//fd2 = open("test.txt", O_RDONLY);
	while (1)
	{
		ret1 = get_next_line(fd1, &line1);
		printf("|%d|%s|\n", ret1, line1);
		free(line1);
		if (!ret1)
			return (0);

		//ret2 = get_next_line(fd2, &line2);
		//printf("|%d|%s|\n", ret2, line2);
		//free(line2);
		//if (!ret2)
		//    return (0);
	}
	return (0);
}
