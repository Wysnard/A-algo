#include "path.h"

int main (int argc, char **argv)
{
	//t_map *path;
	t_ref	ref;
	char **tab;
	int **tab_h;
	t_list	*openset;
	t_list	*closeset;

	//path = NULL;
	openset = NULL;
	closeset = NULL;
	tab = ft_read_me(argv[1], &ref, ft_read_first(argv[1]));
	tab_h = ft_make_H(ref, ft_read_first(argv[1]));
	ft_the_route(&openset, &closeset, tab_h, tab, ref);
	ft_print_tab(tab, ref);
	//ft_print_tab_h(tab_h, ref);
	printf("ref->i = %d | ref->j = %d | ref->line = %d\n", ref.i, ref.j, ref.line);
	free(tab);
	free(tab_h);
}
