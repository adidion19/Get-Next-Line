/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:04:10 by adidion           #+#    #+#             */
/*   Updated: 2020/12/07 13:48:11 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	static char *s[OPEN_MAX];
	int i;
	if (fd < 0 || fd > OPEN_MAX || 1 > BUFFER_SIZE || line == 0)
		return (-1);
	while (1)
	{
		if (!
	}
}
