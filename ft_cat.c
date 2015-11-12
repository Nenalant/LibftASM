#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE "ft_cat.c"

void	ft_cat(int fd)
{
	char	c;

	while (read(fd, &c, 1) == 1)
		write(1, &c, 1);
}

void	ft_cat_buffer(int fd)
{
	char	buffer[1024];
	int		ret;

	while ((ret = read(fd, buffer, sizeof(buffer))) > 0)
	{
		if (write(1, buffer, ret) == -1)
			return ;
	}
}

int main(void)
{
	int fd;
	int i = 100;

	while (i--)
	{
		fd = open(FILE, O_RDONLY);
		printf("fd = %i\n", fd);
		ft_cat(fd);
		close(fd);
	}
	return (0);
}