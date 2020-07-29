/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:56:42 by juanrodr          #+#    #+#             */
/*   Updated: 2020/07/29 12:59:13 by juanrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	int		d;

	d = 0;
	while (s[d] != '\0')
	{
		d++;
	}
	return (d);
}

char		*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

char		*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ret;

	i = 0;
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)) != NULL)
	{
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!ret)
		return (NULL);
	while (*s1)
	{
		ret[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		ret[i] = *s2;
		i++;
		s2++;
	}
	ret[i] = '\0';
	return (ret);
}

int			get_next_line(char **line)
{
	static char	*mem;
	char		buffer[256 + 1];
	char		*tmp;
	int			ret;
	char		*aux1;
	char		*aux2;

	if (!line)
		return (-1);
	while (ft_strchr(mem, '\n') == NULL)
	{
		ret = read(0, buffer, 256);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			break ;
		buffer[ret] = 0;
		if (!mem)
			mem = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(mem, buffer);
			free(mem);
			mem = tmp;
		}
	}
	if (!mem && !ret)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if ((aux1 = ft_strchr(mem, '\n')))
	{
		*aux1 = 0;
		*line = ft_strdup(mem);
		aux2 = ft_strdup(++aux1);
		free(mem);
		mem = aux2;
	}
	else
	{
		*line = ft_strdup(mem);
		free(mem);
		mem = NULL;
		return (0);
	}
	return (1);
}
