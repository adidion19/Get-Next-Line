/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:53:15 by adidion           #+#    #+#             */
/*   Updated: 2020/12/02 17:37:38 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#define BUFFER_SIZE 9999

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	while (*str || c == 0)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	return (0);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*str;

	i = -1;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((char*)s2);
	if (!s2)
		return ((char*)s1);
	len1 = ft_strlen((char*)s1);
	len2 = ft_strlen((char*)s2);
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	return (str);
}

void	ft_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
		ft_memdel((void**)as);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char		*ans;
	size_t		i;
	size_t		j;

	j = 0;
	if (!s)
		return (0);
	if (!(ans = malloc(sizeof(char) * len + 1)))
		return (0);
	if (start >= ft_strlen(s))
		return (ans);
	i = start;
	len = len + start;
	while (s[i] && i < len)
	{
		ans[j] = s[i];
		j++;
		i++;
	}
	ans[j] = '\0';
	return (ans);
}

static int	ft_line(char **s, char **line)
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
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
		{
			free(*s);
			return (-1);
		}
		ft_strdel(s);
	}
	return (1);
}

int		ft_return(char **s, char **line, int i, int fd)
{
	if (i < 0)
		return (-1);
	if (i == 0 && s[fd] == 0)
		return (0);
	else
		return (ft_line(&s[fd], line));
}

int get_next_line(int fd, char **line)
{
	static char *s[OPEN_MAX];
	char *temp;
	char buff[BUFFER_SIZE + 1];
	int i;
	int j;

	if (fd < 0 || fd > OPEN_MAX || 1 > BUFFER_SIZE || line == 0)
		return (-1);
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (!s[fd])
		{
			if (!(s[fd] = ft_strdup(buff)))
			{
				free(s);
				return (-1);
			}
		}
		else
		{
			if (!(temp = ft_strjoin(s[fd], buff)))
			{
				free(temp);
				return (-1);
			}
			s[fd] = temp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	if ((j = ft_return(s, line, i, fd)) == -1)
	{
		free (s);
		return (-1);
	}
	return (j);
}

int        main(void)
{
	int ret1;
	int fd1;
	char *line1;
	int ret2;
	int fd2;
	char *line2;

	fd1 = open("teft.txt", O_RDONLY);
	fd2 = open("tejt.txt", O_RDONLY);
	while (1)
	{
		ret1 = get_next_line(fd1, &line1);
		printf("|%d|%s|\n", ret1, line1);
		
		if (!ret1)
			return (0);

		ret2 = get_next_line(fd2, &line2);
		printf("|%d|%s|\n", ret2, line2);
		free(line2);
		if (!ret2)
		    return (0);
	}
	return (0);
}