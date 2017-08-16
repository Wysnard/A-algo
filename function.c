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

t_list *ft_sort_list(t_list * pList)
{
    // zero or one element in list
    if(pList == NULL || pList->next == NULL)
        return pList;
    // head is the first element of resulting sorted list
    t_list * head = NULL;
    while(pList != NULL) {
        t_list * current = pList;
        pList = pList->next;
        if(head == NULL || current->F < head->F) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            current->next = head;
            head = current;
        } else {
            // insert current element into proper position in non-empty sorted list
            t_list * p = head;
            while(p != NULL) {
                if(p->next == NULL || // last element of the sorted list
                   current->F < p->next->F) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    current->next = p->next;
                    p->next = current;
                    break; // done
                }
                p = p->next;
            }
        }
    }
    return head;
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
			/*if (tab[j][i] == '|')
				printf("%c", ref.vide);
			else*/
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
