/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:44:36 by juanrodr          #+#    #+#             */
/*   Updated: 2020/08/05 12:54:57 by juanrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

size_t ft_strlen(char *s)				/////**************StrLen Basico***************/////
{
	size_t count = 0;

	while (s[count]!= '\0')
		count++;
	return (count);
}

int	ft_numlen(long long num, int base_len)	/////***************NumLen Basico***************/////
{											//Saber longitud en funcion de la base
	int count = 1;

	while (num >= base_len)
	{
		num = num / base_len;
		count++;
	}
	return (count);
}

void	ft_putnum(long long num, int base_len, char *base)	//////***************PutNum Recursivo***************/////
{															//Imprime numeros en todas las bases
	if (num >= base_len)
		ft_putnum(num / base_len, base_len, base);
	write (1, &base[num % base_len], 1);
}

int	ft_printf(char *format, ...)							//////***************Funcion principal***************/////
{
	va_list valist;												//Guardar lista argumentos
	char	*base, *str_print, *str;									//Guardar base, Cadena de conversion s y cadena principal
	long	num;												//Guardar numero de conversiones x y d
	int		count = 0,ret = 0, base_len, prec , width , len , space , zeros , bool_prec , bool_neg ;

	va_start(valist, format);		//Iniciamos lista de argumentos
	str = format;			//Guardar cadena principal
	while (str[count] != '\0')			//Mientras no acabe
	{
		if (str[count] != '%')		//Mientras no haga conversion imprimimos;
		{
			write(1, str + count, 1);
			++count && ++ret;			//Aumentamos impresos y el contador
		}
		else						//Cuando encontramos la conversion (%)
		{
			count++;			//Saltamos el '%'
			prec = 0, width = 0, space = 0, zeros = 0, bool_prec = 0, bool_neg = 0;		//Reiniciamos utiles de conversion
			while (str[count] >= '0' && str[count] <= '9')				//Guardamos Width (saltamos todos los digitos encontrados)
			{
				width = width * 10 + (str[count] - '0');
				count++;
			}
			if (str[count] == '.')			//Comprobamos si existe precision y la guardamos (saltamos digitos)
			{
				count++;					//Saltamos el '.'
				while (str[count] >= '0' && str[count] <= '9')
				{
					prec = prec * 10 + (str[count] - '0');
					count++;
				}
				bool_prec = 1;			//Activamos comprobacion de precision
			}
			if (str[count] == 's')			//////***************Conversion S***************/////
			{
				str_print = va_arg(valist, char *);	//Cogemos argumento (guardamos en s)
				if (!str_print)						//Si no existe o vacia
					str_print = "(null)";			//guardamos en (null) a imprimir
				len = ft_strlen(str_print);			//Guardamos numero caracteres
			}
			if (str[count] == 'x')			//////***************Conversion X***************/////
			{
				num = va_arg(valist, unsigned);	//Cogemos argumento (guardamos en num)
				base = "0123456789abcdef";		//Damos la base con longitud
				base_len = 16;
				len = ft_numlen(num, base_len);
			}
			if (str[count] == 'd')			//////***************Conversion D***************/////
			{
				num = va_arg(valist, int);	//Cogemos argumento (guardamos en num)
				base = "0123456789";		//Damos la base con longitud
				base_len = 10;
				if (num < 0)				//Comprobamos si es negativo
				{
					num = num * -1;
					bool_neg = 1;
				}
				len = ft_numlen(num, base_len) + bool_neg;		//Guardamos numero de caracteres
			}
			if (bool_prec == 1 && prec > len && str[count] != 's')	/****No es cadena, hay precision y es mayor que la longitud****/
				zeros = prec - len + bool_neg;			//Guardamos ceros a imprimir
			else if (bool_prec == 1 && prec < len && str[count] == 's')		/****Si es cadena, hay precision y es menor que la longitud****/
				len = prec;						//La longitud pasa a ser la precision
			else if(bool_prec == 1 && prec == 0 && (str[count] == 's'|| num == 0)) /****Es cadena de precision 0 o numero nulo existiendo precision****/
				len = 0;							//Longitud pasa a ser 0
			space = width - len - zeros;			//Calculamos espacios a imprimir
			while (space-- > 0)					//Imprimimos espacios
			{
				write(1, " ", 1);
				ret++;
			}
			if (bool_neg == 1)						//Imprimimos '-' en caso de numeros negativos
				write(1, "-", 1);
			while (zeros-- > 0)					//Imprimimos ceros necesarios
			{
				write(1, "0", 1);
				ret++;
			}
			if (str[count] == 's')				//Imprimimos cadena de caracteres hasta n
				write(1, str_print, len);
			else if (len > 0)						//Si no es 's', sino numero lo imprimimos
				ft_putnum(num, base_len, base);
			ret = ret + len;							//Sumamos a lo anterior los nuevos caracteres impresos
			count++;
		}
	}
    va_end(valist)
	return (ret);				//Retornar caracteres escritos
}

int main()
{
	printf("jaja%30.10s %.3s %.30s %20s %30.10d %30d %.10d %30.10d %5.0d %30.10x %30x %.10x %30.10x %5.0x\n", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0);
	ft_printf("jaja%30.10s %.3s %.30s %20s %30.10d %30d %.10d %30.10d %5.0d %30.10x %30x %.10x %30.10x %5.0x\n", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0);
	printf("\n%6.30s\n", "jaime");
	ft_printf("\n%6.30s\n", "jaime");
	return (0);
}