/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:44:50 by juanrodr          #+#    #+#             */
/*   Updated: 2020/08/04 12:41:26 by juanrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)						/////***************StrLen basico***************/////
{
	size_t	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char		*ft_strchr(const char *str, int ch_find)		/////***************StrChr basico***************/////
{
	int		count = 0;

	if (str == NULL)										//Comprobación o segmentation fault primera iteracion
		return (NULL);
	while (str[count] != '\0')								//Recorremos hasta encontrar caracter deseado
	{
		if (str[count] == ch_find)
			return ((char *)str + count);
		count++;
	}
	return (NULL);
}

char		*ft_strdup(const char *str)						/////***************StrDup básico***************/////
{
	size_t	count;
	char	*ret;

	count = 0;
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)) == NULL)		//Alocamos tamaño + 1
		return (NULL);
	while (str[count] != '\0')								//Recorremos todo guardando
	{
		ret[count] = str[count];
		count++;
	}
	ret[count] = '\0';										//Guardamos el \0
	return (ret);
}

char		*ft_strjoin(char const *s1, char const *s2)		/////***************StrJoin basico***************/////
{
	char	*ret;
	size_t	count;

	count = 0;
	if (s1 == NULL || s2 == NULL)							//Comprobamos nulos
		return (NULL);
	if ((ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)) == NULL)
		return (NULL);										//Alocamos tamaño de ambos + 1
	while (*s1)										//Alcamos primera
	{
		ret[count] = *s1;
		count++;
		s1++;
	}
	while (*s2)										//Alocamos segunda detras de la primera
	{
		ret[count] = *s2;
		count++;
		s2++;
	}
	ret[count] = '\0';										//Guardamos el \0
	return (ret);
}

int			get_next_line(char **line)						/////***************Creamos Func Principal***************/////
{
	static char	*mem;				//Para almacenar lo leido
	char		buffer[256 + 1];	//Para leer
	char		*tmp;				//Para pasar el join antes de mem
	int			ret;				//Para comprobar el read
	char		*aux1;
	char		*aux2;

	if (!line)
		return (-1);
	while (ft_strchr(mem, '\n') == NULL)	//Mientras que no este \n avanzamos guardandolo y vemos si \n de la anterior iteracion
	{
		ret = read(0, buffer, 256);			//Guardamos 0-256 caracteres a buffer de std_imput y en ret el n leido
		if (ret < 0)						//Comprobacion si da error read
			return (-1);					//Devolver error (-1)
		if (ret == 0)						//Cero bytes leidos
			break ;
		buffer[ret] = '\0';					//Guardamos 0 de fin de read
		if (!mem)							//Si nada guardado de antes guardamos buffer
			mem = ft_strdup(buffer);
		else								//Si ya guardado algo
		{
			tmp = ft_strjoin(mem, buffer);	//Unimos en tmp buffer con lo guardado
			free(mem);						//Liberamos
			mem = tmp;						//Podemos guardar
		}
	}						/////***************EN ESTE PUNTO LINEA GUARDA EN MEM***************/////
							/////***************SOLO QUEDA STRDUP EN LINE DE MEM***************/////
	if (!mem && !ret)
	{
		*line = ft_strdup("");
		free(mem);
		return (0);							//Devolver lectura completada (0)
	}
	else if ((aux1 = ft_strchr(mem, '\n')))	//Comprobamos si queda guardado algun \n en mem
	{
		*aux1 = 0;							//
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
		return (0);							//Devolver lectura completada (0)
	}
	return (1);								//Fin de linea leida (1)
}
