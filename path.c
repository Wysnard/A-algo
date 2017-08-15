#include "path.h"
#define BUF_SIZE 4096

int ft_read_first(char *argv)
{
	int fd;
	char buf[2];
	int ret;
	int ct;

	ct = 0;
	fd = open(argv, O_RDONLY);
	while (ret = read(fd, buf, 1))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n')
			break ;
	}
	while (ret = read(fd, buf, 1))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n')
			break ;
		ct++;
	}
	close(fd);
	return (ct);
}

void ft_init_map(int fd, t_ref *ref)
{
	char buf[2];
	int ret;
	char first[12];
	int i;

	i = 0;
	while (ret = read(fd, buf, 1))
	{
		buf[ret] = '\0';
		first[i] = buf[0];
		if (buf[0] == '\n')
			break ;
		i++;
	}
	first[i] = '\0';
	ref->line = ft_atoi(first);
	if (ref->line == 0)
		exit (0);
	ref->sqr = first[i - 1];
	ref->obs = first[i - 2];
	ref->vide = first[i - 3];
}

char **ft_read_me(char *argv, t_ref	*ref, int ct)
{
	int fd;
	char buf[BUF_SIZE + 1];
	int ret;
	char **tab;
	int i;
	int j;
	int b;

	j = 0;
	i = 0;
	fd = open(argv, O_RDONLY);
	ft_init_map(fd, ref);
	tab = (char**)malloc(sizeof(*tab) * (ref->line + 1));
	printf("ref->line = %d\n", ref->line);
	tab[0] = malloc(sizeof(char) * (ct + 1));
	while (ret = read(fd, buf, BUF_SIZE))
	{
		buf[ret] = '\0';
		b = 0;
		while (buf[b])
		{
			if (buf[b] == '\n')
			{
				tab[j][i] = '\0';
				j++;
				i = -1;
				tab[j] = malloc(sizeof(char) * (ct + 1));
			}
			else
				tab[j][i] = buf[b];
			i++;
			b++;
		}
	}
	tab[j][i] = '\0';
	j--;
	while (tab[j][i + 1])
		i++;
	tab[j][i] = ref->sqr;
	ref->i = i;
	ref->j = j;
	close(fd);
	return (tab);
}
