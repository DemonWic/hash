//
// Created by Виктор Рыжков on 04/10/2020.
//
#include "libft.h"
#include "lemin.h"


t_data *ft_read(int fd, int size_map)
{
    int i;
    int id;
    int k;
    char *line;
    char **buf;
    t_data *data;

    k = 0;
    buf = NULL;
    data = (t_data *)ft_memalloc(sizeof(t_data));
    data->start = NULL;
    data->end = NULL;
    data->nodes = (t_node **)ft_memalloc((sizeof(t_node) * size_map));
    data->roads = (t_road **)ft_memalloc((sizeof(t_road) * size_map));
    if (data->nodes == NULL || data->roads == NULL)
        return NULL;
    data->roads_count = 0;
    data->ant_count = 0;
    while((i = get_next_line(fd,&line)) > 0)
    {
        if (ft_strcmp("##start", line) == 0)
        {
            k = 1;
            ft_strdel(&line);
            continue;
        }
        else if (ft_strcmp("##end", line) == 0)
        {
            k = 2;
            ft_strdel(&line);
            continue;
        }
        else if (line[0] == '#' || line[0] == 'L')
        {
            ft_strdel(&line);
            continue;
        }
        else
        {
            if (ft_strchr(line, ' '))
            {
                buf = ft_strsplit(line, ' ');  //можно присваивать сразу массив и ничего не копировать ?
                id = ft_hash(buf[0], size_map);
                t_node *buf2= (t_node *)ft_memalloc(sizeof(t_node));
                if (buf2 == NULL)
                    return NULL;
                buf2->name = ft_strdup(buf[0]);
                buf2->x = ft_atoi(buf[1]);
                buf2->y = ft_atoi(buf[2]);
                buf2->met = 0;
                buf2->exclude = 0;
                buf2->marker = k;
                if (data->nodes[id] != NULL)
                {
                    t_node *buff = data->nodes[id];
                    while(buff->next != NULL)
                        buff = buff->next;
                    buff->next = buf2;
                }
                else
                    data->nodes[id] = buf2;
                if (k == 1)
                    data->start = buf2;
                if (k == 2)
                    data->end = buf2;
                k = 0;
                ft_free_str(buf);
                ft_strdel(&line);
            }
            else if (ft_strchr(line, '-'))
            {
                buf = ft_strsplit(line, '-');
                t_node *buf3;
                buf3 = ft_search(buf[0], data->nodes);
                buf3->rel = ft_strchrjoin(buf3->rel, buf[1], ' ');
                buf3 = ft_search(buf[1], data->nodes);
                buf3->rel = ft_strchrjoin(buf3->rel, buf[0], ' ');
                ft_free_str(buf);
                ft_strdel(&line);
            }
            else if (ft_strlen(line) == 0)
            {
                ft_strdel(&line);
                break ;
            }
            else
            {
                data->ant_count = ft_atoi(line);
                ft_strdel(&line);
            }

        }

    }
    return data;
}


