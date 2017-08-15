#ifndef PATH_H
#define PATH_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef	struct	s_list
{
	int	i;
	int	j;
	int	F;
	int	G;
	struct s_list	*next;
	struct s_list	*prev;
	struct s_list	*parent;
}								t_list;

typedef struct	s_ref
{
	int	i;
	int	j;
	char vide;
	char obs;
	char sqr;
	int line;
}								t_ref;

int ft_atoi(char *str);
char	**ft_read_me(char *argv, t_ref *ref, int ct);
int ft_read_first(char *argv);
void ft_print_tab(char **tab, t_ref ref);
int **ft_make_H(t_ref ref, int ct);
void ft_print_tab_h(int **tab_h, t_ref ref);
void ft_print_list(t_list *list);
void ft_the_route(t_list **openset, t_list **closeset, int **tab_h, char **tab, t_ref ref);
t_list *ft_create_list();
t_list *ft_addlink(t_list *list);
t_list *ft_init_start(t_list *list);
t_list *ft_addclose(t_list *list, t_list *link);
t_list *ft_minlist(t_list *list);
t_list *ft_drop(t_list **list);
int	ft_check_double(t_list	**closeset, t_list **openset, int j, int i, int G, int **tab_h);
void ft_init_map(int fd, t_ref *ref);
void clean_list(t_list *list);

#endif