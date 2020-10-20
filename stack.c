//
// Created by Виктор Рыжков on 18.10.2020.
//


#include "lemin.h"


void ft_stkinit(t_stack *stk)
{
    stk->top = 0;
}


int ft_stkpush(t_stack *stk, t_edge *edge)
{
    if(stk->top < MAP_SIZE)
    {
        stk->elem[stk->top] = edge;
        stk->top++;
        return (1);
    }
    else
        return (0);
}
// нужно очищение памяти после использования полученного edge
t_edge *ft_stkpop(t_stack *stk)
{
    t_edge *elem;

    if((stk->top) > 0)
    {
        stk->top--;
        elem = stk->elem[stk->top];
        return (elem);
    }
    else
        return (NULL);
}

int ft_stkempty(t_stack *stk)
{
    if(stk->top == 0)
        return (1);
    else
        return (0);
}