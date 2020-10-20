//
// Created by Виктор Рыжков on 18.10.2020.
//

#include "lemin.h"


void ft_quinit(t_queue *q)
{
    q->frnt = 1;
    q->rear = 0;
}

int ft_quinsert(t_queue *q, char *s)
{
    if(q->rear < MAP_SIZE)
    {
        q->rear++;
        q->qu[q->rear]=ft_strdup(s);
        return (1);
    }
    else
        return (0);
}

int ft_quempty(t_queue *q)
{
    if(q->rear < q->frnt)
        return (1);
    else
        return (0);
}

// нужно очищение памяти после использования полученного char *node
char *ft_qupop(t_queue *q)
{
    char *node;

    if(ft_quempty(q)==1)
        return (NULL);
    node = q->qu[q->frnt];
    q->frnt++;
    return node;
}