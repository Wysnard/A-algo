#include "path.h"

int ft_atoi(char *str)
{
	int nb;
	int i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

void ft_print_tab(char **tab, t_ref ref)
{
	int i;
	int j;

	j = 0;
	while (j < ref.line)
	{
		i = 0;
		while(tab[j][i])
		{
			printf("%c", tab[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void ft_print_tab_h(int **tab_h, t_ref ref)
{
	int i;
	int j;

	j = 0;
	while (j < ref.line)
	{
		i = 0;
		while(tab_h[j][i])
		{
			printf("%d |", tab_h[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void ft_print_list(t_list *list)
{
	while (list)
	{
		printf("list->F = %d | i = %d | j = %d\n", list->F, list->i, list->j);
		list = list->next;
	}
}
