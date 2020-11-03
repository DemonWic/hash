//
// Created by Виктор Рыжков on 18.10.2020.
//

#include "lemin.h"

int short_path(t_data *all)
{
    char **buf;
    int i;
    int res;

    i = 0;
    res = 0;
    buf = ft_strsplit(all->start->rel, ' ');
    while(buf[i] != 0)
    {
        if (ft_strcmp(buf[i], all->end->name) == 0)
        {
            ft_add_edge(all->roads, res, all->end->name);
            ft_add_edge(all->roads, res, all->start->name);
            all->roads_count++;
            res = 1;
            break ;
        }
        i++;
    }
    ft_free_str(buf);
    return (res);
}


void free_edge(t_edge *e)
{
    free(e->end);
    e->end = NULL;
    free(e->begin);
    e->begin = NULL;
    free(e);
    e = NULL;
}

void  end_path(t_data *all, int num, int res)
{
    if (res != 0)
    {
        ft_add_edge(all->roads, num, all->end->name);
        all->roads_count++;
    }
}

void  build_path(t_data *all, t_stack *edges, int num, int res)
{
    char *node;
    t_node *n;
    t_edge *e;

    end_path(all, num, res);
    node = ft_strdup(all->end->name);
    while (!ft_stkempty(edges))
    {
        e = ft_stkpop(edges);
        if (!ft_strcmp(e->end,node))
        {
            free(node);
            node = ft_strdup(e->begin);
            if (ft_strcmp(node, all->start->name))
            {
                n = ft_search(node, all->nodes);
                n->exclude = 1;
            }
            ft_add_edge(all->roads, num, node);
        }
        free_edge(e);
    }
    free(node);
}



int bfs(t_data *all, int count, int num)
{
    t_queue queue;
    ft_quinit(&queue);
    t_stack edges;
    ft_stkinit(&edges);
    char *node;
    char **buf;
    int i;
    int res;
    t_edge *e;
    t_node *n;

    res = 0;
    if (short_path(all))
        return (0);
    ft_quinsert(&queue, all->start->name);
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
            if (n->met == count && n->exclude == 0)
            { // если вершина смежная и не обнаружена
                ft_quinsert(&queue, buf[i]);// добавляем ее в очередь
                n->met += 1;// отмечаем вершину как обнаруженную
                e = (t_edge *)ft_memalloc(sizeof(t_edge));
                e->begin = ft_strdup(node);
                e->end = ft_strdup(buf[i]);
                ft_stkpush(&edges, e);
                if (ft_strcmp(n->name, all->end->name) == 0)
                {
                    res = 1;
                    break;
                }
            }
            i++;
        }
        free(node);
        ft_free_str(buf);
    }
    build_path(all, &edges, num, res);
    return (res);
}