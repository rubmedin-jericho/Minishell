
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
        // You may insert code here
	char c;
	c = fgetc(f);
	if (c == EOF && ferror(f))
		return -1;
	while (c != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c,f);
			break;
		}
		c = fgetc(f);
	}
	if(ferror(f))
		return -1;
    return (1);
}

int match_char(FILE *f, char c)
{
        // You may insert code here
	char ch;
	ch  = fgetc(f);
	if (ch == c)
		return 1; 
	if (ch == EOF)
		ungetc(ch,f);
    return (-1);
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
	char ch;

	ch = fgetc(f);
	char *cp = va_arg(ap, char *);
	if (ch == EOF)
		return -1;
	*cp = (char)ch;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
	int value = 0;
	int sign = 1;
	int *ip;
	int count = 0;
	char ch;
	ip = va_arg(ap, int *);
	ch = fgetc(f);
	if (ch == EOF)
		return -1;
	while (isspace(ch))
        ch = fgetc(f);
	if (ch == '-')
	{
		sign = -1;
		ch = fgetc(f);
	}
	else if (ch == '+')
	{	
		ch = fgetc(f); 
	}
	if (!isdigit(ch))
	{
		ungetc(ch, f);
		return -1;
	}
	while (isdigit(ch))
	{
		value = value * 10 + (ch - '0');
		count++;
		ch = fgetc(f);
	}
	if (ch != EOF)
		ungetc(ch,f);
	if (count == 0)
		return -1;
	*ip = value * sign;
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		printf("format\n");
		if (*format == '%')
		{
			format++;
			printf("entered format\n");
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			printf("entered isspace\n");
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	// ...
	va_list ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	// ...
	va_end(ap);
	return ret;
}
int main()
{
	int a;
	int b;
	char c;
	ft_scanf("%d %d %c", &a, &b, &c);
	//scanf("%d", &a);
	printf("%d %c\n", b,c);
}
