#include "path.h"

t_list *ft_create_list()
{
	t_list *tmp;

	tmp = malloc(sizeof(*tmp));
	if (tmp)
	{
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->parent = NULL;
	}
	return (tmp);
}

t_list *ft_addlink(t_list *list)
{
	t_list *tmp;

	tmp = ft_create_list();
	tmp->next = list;
	if (list)
		tmp->next->prev = tmp;
	return (tmp);
}

t_list *ft_minlist(t_list *list)
{
	t_list	*min;
	t_list	*tmp;

	min = list;
	tmp = list;
	while (tmp)
	{
		if (tmp->F < min->F)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

t_list *ft_drop(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp->prev == NULL && tmp->next == NULL)
		return (tmp->next);
	else if (tmp->prev && tmp->next)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else if (tmp->prev == NULL && tmp->next)
		return (tmp->next);
	else if (tmp->prev && tmp->next == NULL)
	{
		tmp->prev->next = tmp->next;
		tmp = tmp->prev;
	}
	while (tmp->prev)
	{
		tmp = tmp->prev;
	}
	return (tmp);
}

t_list *ft_addclose(t_list *list, t_list *link)
{
	link->next = list;
	if (list)
		list->prev = link;
	return (link);
}

t_list *ft_init_start(t_list *list)
{
	t_list	*tmp;

	tmp = ft_addlink(list);
	tmp->i = 0;
	tmp->j = 0;
	tmp->G = 0;
	tmp->F = 1;
}

int **ft_make_H(t_ref ref, int ct)
{
	int **tab_h;
	int j;
	int i;

	j = 0;
	i = 0;
	tab_h = (int**)malloc(sizeof(*tab_h) * ref.line);
	tab_h[j] = malloc(sizeof(int) * (ct + 1));
	tab_h[j][i] = ref.i + ref.j;
	i++;
	while (j <= ref.j)
	{
		while (i <= ref.i)
		{
			if (j == 0)
				tab_h[j][i] = tab_h[j][i - 1] - 1;
			else
				tab_h[j][i] = tab_h[j - 1][i] - 1;
			i++;
		}
		i = 0;
		j++;
		tab_h[j] = malloc(sizeof(int) * (ct + 1));
	}
	tab_h[ref.j][ref.i] = 0;
	//printf("TAB H = %d\n", tab_h[ref.j][ref.i]);
	return (tab_h);
}

int	ft_check_double(t_list	**closeset, t_list **openset, int j, int i, int G, int **tab_h)
{
	t_list	*list;
	int F;

	list = *openset;
	F = G + 1 + tab_h[j][i];
	while (list)
	{
		if (list->j == j && list->i == i)
		{
			if (F < list->F)
			{
				list->parent = *closeset;
				return (0);
			}
		}
		list = list->next;
	}
	return (1);
}

t_list	*ft_new_openset(t_list **openset, t_list **closeset, int **tab_h, char **tab, t_ref ref)
{
	t_list *tmp;
	int i;
	int j;
	int G;

	i = (*closeset)->i;
	j = (*closeset)->j;
	G = (*closeset)->G;
	tmp = *openset;
	if (i > 0 && (tab[j][i - 1] == ref.vide || tab[j][i - 1] == ref.sqr) && ft_check_double(closeset, openset, j, i - 1, G, tab_h))
	{
		tmp = ft_addlink(tmp);
		tmp->parent = *closeset;
		tmp->i = i - 1;
		tmp->j = j;
		tmp->G = G + 1;
		tmp->F = (tab[j][i - 1] == ref.vide) ? tmp->G + tab_h[j][i - 1] : 0;
		//printf("openset->F = %d | G = %d | H = %d\n", tmp->F, tmp->G, tab_h[(*closeset)->j][(*closeset)->i + 1]);
		//printf("openset->j = %d | i = %d\n", tmp->j, tmp->i);
	}
	if (j > 0 && (tab[j - 1][i] == ref.vide || tab[j - 1][i] == ref.sqr) && ft_check_double(closeset, openset, j - 1, i, G, tab_h))
	{
		tmp = ft_addlink(tmp);
		tmp->parent = *closeset;
		tmp->i = i;
		tmp->j = j - 1;
		tmp->G = G + 1;
		tmp->F = (tab[j - 1][i] == ref.vide) ? tmp->G + tab_h[j - 1][i] : 0;
		//printf("openset->F = %d | G = %d | H = %d\n", tmp->F, tmp->G, tab_h[(*closeset)->j + 1][(*closeset)->i]);
		//printf("openset->j = %d | i = %d\n", tmp->j, tmp->i);
	}
	if (j < ref.j && (tab[j + 1][i] == ref.vide || tab[j + 1][i] == ref.sqr) && ft_check_double(closeset, openset, j + 1, i, G, tab_h))
	{
		tmp = ft_addlink(tmp);
		tmp->parent = *closeset;
		tmp->i = i;
		tmp->j = j + 1;
		tmp->G = G + 1;
		tmp->F = (tab[j + 1][i] == ref.vide) ? tmp->G + tab_h[j + 1][i] : 0;
		//printf("openset->F = %d | G = %d | H = %d\n", tmp->F, tmp->G, tab_h[(*closeset)->j + 1][(*closeset)->i]);
		//printf("openset->j = %d | i = %d\n", tmp->j, tmp->i);
	}
	if (i < ref.i && (tab[j][i + 1] == ref.vide || tab[j][i + 1] == ref.sqr) && ft_check_double(closeset, openset, j, i + 1, G, tab_h))
	{
		tmp = ft_addlink(tmp);
		tmp->parent = *closeset;
		tmp->i = i + 1;
		tmp->j = j;
		tmp->G = G + 1;
		tmp->F = (tab[j][i + 1] == ref.vide) ? tmp->G + tab_h[j][i + 1] : 0;
		//printf("openset->F = %d | G = %d | H = %d\n", tmp->F, tmp->G, tab_h[(*closeset)->j][(*closeset)->i + 1]);
		//printf("openset->j = %d | i = %d\n", tmp->j, tmp->i);
	}
	/*printf("--- OPEN ---\n");
	ft_print_list(tmp);
	printf("--- END OPEN ---\n");*/
	return (tmp);
}

void ft_here_is_is(t_list **closeset, char **tab, t_ref ref)
{
	while((*closeset))
	{
		tab[(*closeset)->j][(*closeset)->i] = ref.sqr;
		*closeset = (*closeset)->parent;
	}
}

void ft_the_route(t_list **openset, t_list **closeset, int **tab_h, char **tab, t_ref ref)
{
	t_list	*min;
	int ct;

	ct = 0;
	*openset = ft_init_start(*openset);
	printf("start = %d\n", (*openset)->F);
	*closeset = ft_addclose(*closeset, *openset);
	*openset = (*openset)->next;
	tab[(*closeset)->j][(*closeset)->i] = '|';
	*openset = ft_new_openset(openset, closeset, tab_h, tab, ref);
	ft_print_list(*openset);
	while (*openset)
	{
		*openset = ft_sort_list(*openset);
		min = *openset;
		*openset = (*openset)->next;
		*closeset = ft_addclose(*closeset, min);
		tab[(*closeset)->j][(*closeset)->i] = '|';
		//printf("close j = %d | close i = %d\n", (*closeset)->j, (*closeset)->i);
		*openset = ft_new_openset(openset, closeset, tab_h, tab, ref);
		if (((*closeset)->j == ref.j && (*closeset)->i == ref.i) || *openset == NULL)
		break ;
	}
	if (*openset == NULL)
	{
		printf("No Solution!\n");
		return ;
	}
	ft_here_is_is(closeset, tab, ref);
	//ft_print_list(*openset);
}
