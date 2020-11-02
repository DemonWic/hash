//
// Created by Виктор Рыжков on 02.11.2020.
//

#include "lemin.h"

int     del_lems(t_data *data, t_lem *lems[data->ant_count])
{
    int     i;

    i = 0;
    while (i < data->ant_count)
    {
        free(lems[i++]);
    }
    return (1);
}

int     add_lem(t_data *data, int i, t_lem *lems[data->ant_count], int cur_lems)
{
    t_lem   *new;

    new = (t_lem*)malloc(sizeof(t_lem));
    new->road = data->roads[i];
    new->n = cur_lems + 1;
    new->finished = 0;
    lems[cur_lems] = new;
    data->col--;
    data->cur_n++;
    return (++cur_lems);
}

int     count_min_lems(t_data *data, int a)
{
    int     i;
    int     res;

    res = 0;
    i = 0;
    while (i < a)
    {
        res += data->roads[i]->len - data->roads[0]->len + 1;
        i++;
    }
    return (res);
}
int     new_lems(t_data *data, t_lem *lems[data->ant_count], int cur_lems)
{
    int     i;
    int     cur;

    i = 0;
    cur = data->col;
    while (i < data->roads_count)
    {
        if (cur >= count_min_lems(data, i) && cur_lems < data->ant_count)
            cur_lems = add_lem(data, i, lems, cur_lems);
        else
            break ;
        i++;
    }
    return (cur_lems);
}

int     make_step(t_data *data, t_lem *lems[data->ant_count], int cur_lems)
{
    int     i;
    char  *buf;

    i = 0;
    while (i < cur_lems)
    {
        if (lems[i++]->finished == 1)
            continue ;
        lems[i - 1]->road = lems[i - 1]->road->next;
        if (lems[i - 1]->road == NULL)
        {
            lems[i - 1]->finished = 1;
            data->cur_n--;
            continue ;
        }
        ft_putchar('L');
        buf = ft_itoa(lems[i - 1]->n);
        ft_putstr(buf);
        ft_strdel(&buf);
        ft_putchar('-');
        ft_putstr(lems[i - 1]->road->edge);
        ft_putchar(' ');
    }
    return (1);
}

int     way_len2(t_data *data)
{
    int     i;

    i = 1;
    while (i <= data->ant_count)
    {
        ft_putchar('L');
        ft_putstr(ft_itoa(i));
        ft_putchar('-');
        ft_putstr(data->end->name);
        ft_putchar(' ');
        i++;
    }
    return (1);
}

int     go_lem(t_data *data)
{
    int     cur_lems;
    t_lem   *lems[data->ant_count];

    if (data->roads[0]->len == 2)
    {
        ft_putchar('\n');  // пустая строка между картой и муравьями (если перебор со строками можно перенести в way_len2)
        return (way_len2(data));
    }
    cur_lems = 0;
    data->col = data->ant_count;
    data->cur_n = 0;
    cur_lems = new_lems(data, lems, cur_lems);
    ft_putchar('\n');
    while (data->cur_n > 0)
    {
        make_step(data, lems, cur_lems);
        cur_lems = new_lems(data, lems, cur_lems);
        ft_putchar('\n');
    }
    del_lems(data, lems);
    return (1);
}


