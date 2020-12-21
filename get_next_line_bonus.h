/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:38:14 by adidion           #+#    #+#             */
/*   Updated: 2020/12/21 13:18:47 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strlen(char *str);
int		ft_return(int i, char *s);
#endif
