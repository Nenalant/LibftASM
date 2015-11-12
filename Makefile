
NAME = libfts.a

SRCS =	ft_bzero.s \
		ft_strcat.s \
		ft_isalpha.s \
		ft_isdigit.s \
		ft_isalnum.s \
		ft_isascii.s \
		ft_isprint.s \
		ft_toupper.s \
		ft_tolower.s \
		ft_puts.s \
		ft_strlen.s \
		ft_memset.s \
		ft_memcpy.s \
		ft_strdup.s \
		ft_strcpy.s \
		ft_putchar.s \
		ft_putstr.s \
		ft_islower.s \
		ft_isupper.s

SRCC =	main.c
CCS = nasm -f macho64
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.s
	$(CCS) $< -o $@

test: $(NAME)
	gcc $(CFLAGS) $(NAME) main.c -o test_libfs

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) test_libfs

re: fclean all