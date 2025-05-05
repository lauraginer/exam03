
#include <stdarg.h>
#include <unistd.h>
//#include <stdio.h>

void putstr(char *str, int *count)
{
	int i = 0;

	if(!str)
	{
		write(1, "(null)", 6);
		*count = *count + 6;
		return;
	}
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
		*count = *count + 1;
	}
}
void puthex(unsigned int n, int *count)
{
	char *str = "0123456789abcdef";
	if(n >= 16)
	{
		puthex(n / 16, count);
		write(1, &str[n % 16], 1);
		*count = *count + 1;
	}
	else
	{
		write(1, &str[n], 1);
		*count = *count + 1;
	}	
}
void putnbr(int n, int *count)
{
	char *str = "0123456789";

	if(n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count = *count + 11;
		return;
	}
	if(n < 0)
	{
		write(1, "-", 1);
		*count = *count + 1;
		n = -n;
	}
	if(n > 9)
	{
		putnbr(n / 10, count);
		write(1, &str[n % 10], 1);
		*count = *count + 1;
	}
	else
	{
		write(1, &str[n], 1);
		*count = *count + 1;
	}

}

int ft_printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	int i = 0;

	if(!format)
		return(-1);
	va_start(args, format);
	while(format[i])
	{
		if(format[i] == '%')
		{
			if(format[i + 1] == 's')
				putstr(va_arg(args, char *), &count);
			if(format[i + 1] == 'x')
				puthex(va_arg(args, unsigned int), &count);
			if(format[i + 1] == 'd')
				putnbr(va_arg(args, int), &count);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return(count);
}

/*int main()
{
	char *s1 = "toto";
	int i = 45;
	//unsigned int n = 24;

	printf("original: %s\n", s1);
	ft_printf("mi funcion: %s\n", s1);
	printf("original: %d\n", i);
	ft_printf("mi funcion: %d\n", i);
	printf("original: %d, %s\n", i, s1);
	ft_printf("mi funcion: %d, %s\n", i, s1);
	printf("original: %d, %x\n", i, i);
	ft_printf("mi funcion: %d, %x\n", i, i);
}*/