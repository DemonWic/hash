//
// Created by Виктор Рыжков on 18.10.2020.
//

#include "lemin.h"

void bfs(t_data *all, int count)
{
    t_queue queue;
    ft_quinit(&queue);
    t_stack edges;
    ft_stkinit(&edges);
    char *start;
    char *end;
    char *node;
    char **buf;
    int i;
    t_edge *e;
    t_node *n;

    start = all->start->name;
    end = all->end->name;
    ft_quinsert(&queue, start);
    all->start->met += 1;
    while (!ft_quempty(&queue))
    {
        node = ft_qupop(&queue);
        n = ft_search(node, all->nodes);
        n->met += 2;
        buf = ft_strsplit(n->rel, ' ');
        i = 0;
        while (buf[i] != 0)
        {
            n = ft_search(buf[i], all->nodes);
            if (n->met == count & n->exclude == 0)
            { // если вершина смежная и не обнаружена
                ft_quinsert(&queue, buf[i]);// добавляем ее в очередь
                n->met += 1;// отмечаем вершину как обнаруженную
                e = (t_edge *)ft_memalloc(sizeof(t_edge));
                e->begin = ft_strdup(node);
                e->end = ft_strdup(buf[i]);
                ft_stkpush(&edges, e);
                if (node == end)
                    break;
            }
            i++;
        }
        free(node);
        ft_free_str(buf);
    }
    printf("%s ", end);
    node = ft_strdup(end);
    while (!ft_stkempty(&edges))
    {
        e = ft_stkpop(&edges);
        if (!ft_strcmp(e->end,node))
        {
            free(node);
            node = ft_strdup(e->begin);
            if (ft_strcmp(node, start))
            {
                n = ft_search(node, all->nodes);
                n->exclude = 1;
//                printf("<%s> ", n->name);
            }
            printf("%s ", node);
        }
        free(e->end);
        e->end = NULL;
        free(e->begin);
        e->begin = NULL;
//        free(&e);
//        e = NULL;
    }
    free(node);
    printf("\n");
}