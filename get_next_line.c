/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:53:15 by adidion           #+#    #+#             */
/*   Updated: 2020/12/07 10:32:26 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	ft_line(char **s, char **line, int fd, int i)
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
			return (((i != 0)? get_next_line(fd, line) : 0 ));
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
	else if (i == 0 || s[fd] == 0)
		return (0);
	else
		return (ft_line(&s[fd], line, fd, i));
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
			free(s[fd]);
			s[fd] = ft_strdup(temp);
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

/*int main()
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
}*/
