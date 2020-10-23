//
// Created by Виктор Рыжков on 04/10/2020.
//
#include "lemin.h"
#include "libft.h"

#define BITS_IN_int     (sizeof(int) * 8)
#define THREE_QUARTERS  ((int) ((BITS_IN_int * 3) / 4))
#define ONE_EIGHTH      ((int) (BITS_IN_int / 8))
#define HIGH_BITS       (~((unsigned int)(~0) >> ONE_EIGHTH ))

//t_node *ft_search(const char *name);

unsigned int ft_hash(const char * datum, int size)
{
    unsigned int hash_value;
    unsigned int i;
    hash_value = 0;
    while(*datum++)
    {
        hash_value = (hash_value << ONE_EIGHTH) + *datum;
        if ((i = hash_value & HIGH_BITS)!= 0)
            hash_value = (hash_value ^ (i >> THREE_QUARTERS)) & ~HIGH_BITS;
    }
    return (hash_value % size);
}


t_node *ft_search(const char *name, t_node **rooms)
{
    int id;

    id = ft_hash(name, MAP_SIZE);
    if (rooms[id] == NULL)
        return NULL;
    else if (ft_strcmp(rooms[id]->name, name) == 0)
        return rooms[id];
    else
    {
        t_node *buf = rooms[id];
        while(buf != NULL)
        {
            if (ft_strcmp(buf->name, name) == 0)
                return buf;
            buf = buf->next;
        }
    }
    return NULL;
}

char *ft_strchrjoin(char *dest, char *src, char c)
{
    int len_dest;
    int len_src;
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (dest == NULL && src == NULL)
        return NULL;
    else if (dest == NULL && src != NULL)
        return ft_strdup(src);
    if (c == '\0')
        return NULL;
    len_dest = ft_strlen(dest);
    len_src = ft_strlen(src);
    new = ft_strnew(len_dest + len_src + 1);
    while (i < (len_dest + len_src + 1))
    {
        if (i < len_dest)
            new[i] = dest[i];
        else if (i == len_dest)
            new[i] = c;
        else
            new[i] = src[j++];
        i++;
    }
    new[i] = '\0';
    ft_memdel((void **)&dest);
//    free(dest);
    return new;
}

void	ft_nodedelone(t_node **alst)
{
    t_node *new_l;

    new_l = *alst;
    if (new_l)
    {
        free(new_l->name);
        free(new_l->rel);
        free(*alst);
        *alst = NULL;
    }
}

void	ft_nodedel(t_node **alst)
{
    t_node **buf;

    buf = alst;
    if (buf)
    {
        while ((*buf)->next)
            ft_nodedel(&(*buf)->next);
        ft_nodedelone(&(*buf));
    }
}

void	ft_roaddelone(t_road **alst)
{
    t_road *new_l;

    new_l = *alst;
    if (new_l)
    {
        free(new_l->edge);
        free(*alst);
        *alst = NULL;
    }
}

void	ft_roaddel(t_road **alst)
{
    t_road **buf;

    buf = alst;
    if (buf)
    {
        while ((*buf)->next)
            ft_roaddel(&(*buf)->next);
        ft_roaddelone(&(*buf));
    }
}

void ft_datadel(t_data *data)
{
    int i;
    t_node *buf;
    t_road *buf2;

    i = 0;
    while (i < MAP_SIZE)
    {
        if (data->nodes[i] != NULL)
        {
            buf = data->nodes[i];
            ft_nodedel(&buf);
        }
        i++;
    }
    free(data->nodes);
    i = 0;
    while(i < data->roads_count)
    {
        buf2 = data->roads[i];
        ft_roaddel(&buf2);
        i++;
    }
    free(data->roads);
    //TODO дописать очистку roads
    free(data);
}

void    ft_add_edge(t_road **road, int num, char *edge)
{
    t_road *new;
    t_road *buf;

    if (road[num] == NULL)
    {
        new = (t_road *) ft_memalloc(sizeof(t_road));
        new->next = NULL;
        new->edge = ft_strdup(edge);
        road[num] = new;
    }
    else
    {
        buf = road[num];
        new = (t_road *) ft_memalloc(sizeof(t_road));
        new->edge = ft_strdup(edge);
        new->next = buf;
        road[num] = new;
    }

}