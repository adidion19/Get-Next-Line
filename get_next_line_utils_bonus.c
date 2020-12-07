/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:45:01 by adidion           #+#    #+#             */
/*   Updated: 2020/12/07 10:45:09 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_substr(char *s, int start, int len)
{
	char		*ans;
	int			i;
	int			j;

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
