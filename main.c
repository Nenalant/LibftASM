/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/20 17:16:14 by alanteri          #+#    #+#             */
/*   Updated: 2015/10/22 07:28:30 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define RESET	"\033[0m"
#define BOLD	"\033[1m"
//#define	UNBOLD	"\033[21m" /* UNBOLD not supported by zsh */
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define UNCOLOR	"\033[39m"
#define ULINE	"\033[4m"
#define UNULINE	"\033[24m"
#define STRING "Hello"
#define STRINGNULL NULL
#define STR "Old"
#define STR2 "New"

/* Comment out to remove the NULL tests */
#define SEGFAULT_ME
/* If the test segfaults, try skipping the NULL tests */
/* to see if they are the ones giving you a hard time */

void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_puts(char *str);
void	ft_putstr(char const *s);
void	ft_putchar(char c);
int		ft_islower(int c);
int		ft_isupper(int c);

void	ft_flush_write(int fd, char *str, int len)
{
	fflush(stdout);
	write(fd, str, len);
}

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static void	set(char *color_code)
{
	printf("%s", color_code);
}

static void print_test_name(char *str)
{
	set(CYAN);
	set(BOLD);
	printf("%s", str);
	set(RESET);
	if (strlen(str) > 6)
		printf(":\t");
	else
		printf(":\t\t");
	fflush(stdout);
}

static void	print_test_results(int	return_value[], int control_value[], int n, int warning[])
{
	int		i, j;

	if (n)
	{
		i = 0;
		while (i < n)
		{
			printf("test %d", i);
			if (return_value[i] == control_value[i])
			{
				set(GREEN);
				printf(" OK");
				set(UNCOLOR);
				if (i != n - 1)
					printf(", ");
			}
			else
			{
				j = -1;
				if (warning)
				{
					j = 0;
					while (warning[j] != -1 && warning[j] != i)
						++j;
					if (warning[j] != i)
						j = -1;
				}
				if (j == -1)
				{
					set(RED);
					printf(" failed");
					set(UNCOLOR);
					printf(" [ctrl=%d, test=%d]", control_value[i], return_value[i]);
					if (i != n - 1)
						printf(", ");
				}
				else
				{
					set(YELLOW);
					printf(" disagreed");
					set(UNCOLOR);
					printf(" [ctrl=%d, test=%d]", control_value[i], return_value[i]);
					if (i != n - 1)
						printf(", ");
				}
			}
			++i;
		}
		printf("\n");
	}
	else
	{
		set(YELLOW);
		printf("no test was performed\n");
		set(UNCOLOR);
	}
}

static void	print_test_results_summary(int	return_value[], int control_value[], int n)
{
	int		i;

	if (n)
	{
		if (n == 1)
			printf("1 test ");
		else
			printf("%d tests ", n);
		i = 0;
		while (i < n && return_value[i] == control_value[i])
			++i;
		if (i == n && return_value[i - 1] == control_value[i - 1])
		{
			set(GREEN);
			printf("OK");
			set(UNCOLOR);
		}
		else
		{
			if (i == n)
				--i;
			set(RED);
			printf("failed");
			set(UNCOLOR);
			printf(" @ [i=%d, ctrl=%d, test=%d]", i, control_value[i], return_value[i]);
		}
		printf("\n");
	}
	else
	{
		set(YELLOW);
		printf("no test was performed\n");
		set(UNCOLOR);
	}
}

static void	init(int tab[], int n, int c)
{
	int		i;

	i = 0;
	while (i < n)
	{
		tab[i] = c;
		++i;
	}
}

static int	cmp(char *str1, char *str2)
{
	if (str1 && str2)
		return (strcmp(str1, str2));
	return (-42);
}

void	ft_putnbr(int n)
{
	unsigned int	min;
	char			c;

	min = n;
	if (n < 0)
	{
		ft_flush_write(1, "-", 1);
		min = -min;
	}
	if (min > 9)
		ft_putnbr(min / 10);
	c = (char)(48 + min % 10);
	ft_flush_write(1, &c, 1);
}

static void	test_simple(void)
{
	set(YELLOW);
	set(BOLD);
	printf("TEST");
	set(UNCOLOR);
	printf("\n");
}

static void	test_hard(void)
{
	printf("\n\n");
	set(BOLD);
	printf("comparaison du résultat avec la fonction d origine: ");
	printf("\n");
}

static void	ok(void)
{
	set(GREEN);
	set(BOLD);
	printf(" OK ");
	set(UNCOLOR);
	printf("\n");
}

// ***************************************
// ------------TEST DES FONCTIONS---------
// ***************************************

static void	test_bzero(void)
{
	int		test[2], ctrl[2];
	char	str1[]="test string",
			str2[]="test string",
			str3[]="one test string",
			str4[]="two test string";

	print_test_name("------------BZERO------------");
	init(ctrl, 2, 0);
	init(test, 2, 0);
	bzero(str1, 0);
	ft_bzero(str2, 0);
	test[0] = cmp(str1, str2);
	bzero(str3, 10);
	ft_bzero(str4, 10);
	while (!(str3[ctrl[1]]))
		++(ctrl[1]);
	while (!(str4[test[1]]))
		++(test[1]);
	test_hard();
	print_test_results(test, ctrl, 2, NULL);
	printf("\n");
}

static void	test_strcat(void)
{
	int		test[1], ctrl[1];
	char	*dst1, *dst2, src[]="test";
	char	tab1[100];
	char	tab2[100];
	char	*p1;
	char	*p2;
	
	print_test_name("------------STRCAT------------");
	printf("\n\n");
	test_simple();
	printf("s1: ");
	printf("%s\n", STR);
	printf("s2: ");
	printf("%s\n", STR2);
	printf("Original: ");
	strcpy(tab1, STR);
	p1 = strcpy(tab1, STR2);
	printf("%s\n", p1);
	printf("Homemade: ");
	strcpy(tab1, STR);
	p2 = ft_strcpy(tab2, STR2);
	printf("%s", p2);
	ok();
	if (!(dst1 = malloc(sizeof(*dst1) * (strlen(src) + 1) * 3)) || !(dst2 = malloc(sizeof(*dst2) * (strlen(src) + 1) * 3)))
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}
	strcpy(dst1, src);
	strcpy(dst2, src);
	ctrl[0] = 0;
	test[0] = cmp(strcat(dst1, src), ft_strcat(dst2, src));
	free(dst1);
	free(dst2);
	test_hard();
	print_test_results(test, ctrl, 1, NULL);
	printf("\n");
}

static void	test_isalpha(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISALPHA------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = isalpha(i);
		test[i] = ft_isalpha(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

static void	test_isdigit(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISDIGIT------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = isdigit(i);
		test[i] = ft_isdigit(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

static void	test_isalnum(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISALNUM------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = isalnum(i);
		test[i] = ft_isalnum(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

static void	test_isascii(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISACII------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = isascii(i);
		test[i] = ft_isascii(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

static void	test_isprint(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISPRINT------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = isprint(i);
		test[i] = ft_isprint(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

static void	test_toupper(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------TOUPPER------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = toupper(i);
		test[i] = ft_toupper(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

static void	test_tolower(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------TOLOWER------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = tolower(i);
		test[i] = ft_tolower(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

void	test_puts(void)
{
	int		orignal;
	int		homemade;

	print_test_name("------------PUTS------------");
	printf("\n\n");
	test_simple();
	printf("s: ");
	printf(STRING);
	printf("\n");
	printf("Original: ");
	orignal = puts(STRING);
	fflush(stdout);
	printf("Returned: ");
	ft_putnbr(orignal);
	printf("\n");
	printf("Homemade: ");
	fflush(stdout);
	homemade = ft_puts(STRING);
	printf("Returned: ");
	ft_putnbr(homemade);
	ok();
	printf("s: ");
	printf("NULL");
	printf("\n");
	printf("Original: ");
	orignal = puts(STRINGNULL);
	fflush(stdout);
	printf("Returned: ");
	ft_putnbr(orignal);
	printf("\n");
	printf("Homemade: ");
	fflush(stdout);
	homemade = ft_puts(STRINGNULL);
	printf("Returned: ");
	ft_putnbr(homemade);
	ok();
	printf("\n");
}

static void	test_strlen(void)
{
	int		test[2], ctrl[2];

	print_test_name("------------STRLEN------------");
	printf("\n\n");
	test_simple();
	printf("s: ");
	printf("str = %s\n", STR);
	printf("Original len: %zu\n", strlen(STR));
	printf("Homemade len: %zu", ft_strlen(STR));
	ok();
	test[0] = strlen("");
	ctrl[0] = ft_strlen("");
	test[1] = strlen("\001\002\003\004\005\200");
	ctrl[1] = ft_strlen("\001\002\003\004\005\200");
	test_hard();
	print_test_results(test, ctrl, 2, NULL);
	printf("\n");
}

static void	test_memset(void)
{
	int		test[4], ctrl[4];
	char	str1[]="don't kill me\n",
			str2[]="don't kill me\n";

	print_test_name("------------MEMSET------------");
	init(ctrl, 4, 0);
	init(test, 4, 1);
	str1[3] = '\0';
	str2[3] = '\0';
	test[0] = memcmp(memset(str1, '-', 0), ft_memset(str2, '-', 0), 15);
	test[1] = memcmp(memset(str1, '-', 1), ft_memset(str2, '-', 1), 15);
	test[2] = memcmp(memset(str1, '-', 5), ft_memset(str2, '-', 5), 15);
	test[3] = memcmp(memset(str1, 0, 5), ft_memset(str2, 0, 5), 15);
	test_hard();
	print_test_results(test, ctrl, 4, NULL);
	printf("\n");
}

static void	test_memcpy(void)
{
	int		test[5], ctrl[5], n;
	char	str1[]="test string", *str2, *str3;

	print_test_name("------------MEMCPY------------");
	init(ctrl, 5, 0);
	init(test, 5, 1);
	if (!(str2 = malloc(sizeof(*str2) * 20)) || !(str3 = malloc(sizeof(*str3) * 20)))
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}
	memset(str2, 'a', 20);
	memset(str3, 'a', 20);
	n = strlen(str1);
	test[0] = memcmp(memcpy(str2, str1, 0), ft_memcpy(str3, str1, 0), 20);
	test[1] = memcmp(memcpy(str2, str1, 1), ft_memcpy(str3, str1, 1), 20);
	test[2] = memcmp(memcpy(str2, str1, n), ft_memcpy(str3, str1, n), 20);
	test[3] = memcmp(memcpy(str2, str1, n + 1), ft_memcpy(str3, str1, n + 1), 20);
	str1[n - 1] = '\0';
	str1[n] = 'z';
	test[4] = memcmp(memcpy(str2, str1, n + 1), ft_memcpy(str3, str1, n + 1), 20);
	free(str2);
	free(str3);
	test_hard();
	print_test_results(test, ctrl, 5, NULL);
	printf("\n");
}

static void	test_strdup(void)
{
	int		test[3], ctrl[3];
	char	*dst, src[]="test string";

	print_test_name("------------STRDUP------------");
	printf("\n\n");
	test_simple();
	printf("s: ");
	printf(STRING);
	printf("\n");
	printf("Original: ");
	printf("%s", strdup(STRING));
	printf("\n");
	printf("Homemade: ");
	printf("%s", ft_strdup(STRING));
	ok();
	init(ctrl, 3, 0);
	init(test, 3, 1);
	dst = ft_strdup(src);
	test[0] = cmp(src, dst);
	if (!dst[strlen(src)])
		test[1] = 0;
	free(dst);
	dst = ft_strdup("");
	if (dst && !(*dst))
		test[2] = 0;
	free(dst);
	test_hard();
	print_test_results(test, ctrl, 3, NULL);
	printf("\n");
}

static void	test_strcpy(void)
{
	int		test[2], ctrl[2];
	char	*dst1, *dst2, src1[]="\001test string\200", src2[]="test";
	char	tab1[100];
	char	tab2[100];
	char	*p1;
	char	*p2;
	
	print_test_name("------------STRCPY------------");
	printf("\n\n");
	test_simple();
	printf("s: ");
	printf("%s\n", STRING);
	printf("Original: ");
	p1 = strcpy(tab1, STRING);
	printf("%s\n", p1);
	printf("Homemade: ");
	p2 = ft_strcpy(tab2, STRING);
	printf("%s", p2);
	ok();
	init(ctrl, 2, 0);
	init(test, 2, 1);
	if (!(dst1 = malloc(strlen(src1) + 1)) || !(dst2 = malloc(strlen(src1) + 1)))
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}
	test[0] = cmp(strcpy(dst1, src1), ft_strcpy(dst2, src1));
	ft_strcpy(dst1, src2);
	if (!dst1[strlen(src2)])
		test[1] = 0;
	free(dst1);
	free(dst2);
	test_hard();
	print_test_results(test, ctrl, 2, NULL);
	printf("\n");
}

void	test_islower(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISLOWER------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = islower(i);
		test[i] = ft_islower(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

void	test_isupper(void)
{
	int		i, test[1024], ctrl[1024];

	print_test_name("------------ISUPPER------------");
	i = 0;
	while (i < 1024)
	{
		ctrl[i] = isupper(i);
		test[i] = ft_isupper(i);
		++i;
	}
	test_hard();
	print_test_results_summary(test, ctrl, 1024);
	printf("\n");
}

void	test_putchar(void)
{
	print_test_name("------------PUTCHAR------------");
	printf("\n\n");
	test_simple();
	printf("c: ");
	printf("a");
	printf("\n");
	printf("Original: ");
	putchar('a');
	printf("\n");
	printf("Homemade: ");
	fflush(stdout);
	ft_putchar('a');
	ok();
	printf("\n");
}

void	test_putstr(void)
{
	print_test_name("------------PUTSTR------------");
	printf("\n\n");
	test_simple();
	printf("s: ");
	printf(STRING);
	printf("\n");
	printf("Homemade: ");
	fflush(stdout);
	ft_putstr(STRING);
	ok();
	printf("\n");
}

int			main(void)
{
	set(MAGENTA);
	set(BOLD);
	printf("\n\t\t\t\t\t\t\t\t=============== FUNCTIONS ===============\n\n");
	set(UNCOLOR);
	test_bzero();
	test_strcat();
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();
	test_toupper();
	test_tolower();
	test_puts();
	test_strlen();
	test_memset();
	test_memcpy();
	test_strdup();

	set(MAGENTA);
	set(BOLD);
	printf("\t\t\t\t\t\t\t\t================= BONUS =================\n\n");
	set(UNCOLOR);
	test_islower();
	test_isupper();
	test_strcpy();
	test_putchar();
	test_putstr();
	return (0);
}
