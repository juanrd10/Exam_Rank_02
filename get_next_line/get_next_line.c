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

size_t		ft_strlen(const char *str)
{
	int		count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char		*ft_strchr(const char *str, int ch_find)
{
	int		count = 0;
	if (str == NULL)
		return (0);
	if (str[count] == '\0')
	{
		if (ch_find == '\0')
			return ((char *)str);
		return (0);
	}
	while (str[count] != '\0')
	{
		if (str[count] == ch_find)
			return ((char *)str + count);
		count++;
	}
	return (0);
}

char		*ft_strdup(const char *str)
{
	size_t	count;
	char	*ret;

	count = 0;
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)) == NULL)
		return (NULL);
	while (str[count] != '\0')
	{
		ret[count] = str[count];
		count++;
	}
	ret[count] = '\0';
	return (ret);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	count;

	count = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((ret = (char *)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2)) + 1)) == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		ret[count] = *s1;
		count++;
		s1++;
	}
	while (*s2 != '\0')
	{
		ret[count] = *s2;
		count++;
		s2++;
	}
	ret[count] = '\0';
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