#include "path.h"

int main (int argc, char **argv)
{
	t_ref	ref;
	char **tab;
	t_list	*openset;
	t_list	*closeset;

	openset = NULL;
	closeset = NULL;
	tab = ft_read_me(argv[1], &ref, ft_read_first(argv[1]));
	if (ft_the_route(&openset, &closeset, tab, ref))
		ft_print_tab(tab, ref);
	printf("ref->i = %d | ref->j = %d | ref->line = %d\n", ref.i, ref.j, ref.line);
	free(tab);
}
