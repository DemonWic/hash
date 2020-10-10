//
// Created by Виктор Рыжков on 04/10/2020.
//
#include "libft.h"
#include "lemin.h"


t_node **ft_read(int fd, int size_map)
{
    int i;
    int id;
    int k;
    char *line;
    char **buf;
    t_node **rooms;

    k = 0;
    buf = NULL;
    rooms = (t_node **)ft_memalloc((sizeof(t_node) * size_map));
    if (rooms == NULL)
        return NULL;
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
                buf2->marker = k;
                if (rooms[id] != NULL)
                {
                    t_node *buff = rooms[id];
                    while(buff->next != NULL)
                        buff = buff->next;
                    buff->next = buf2;
                }
                else
                    rooms[id] = buf2;
                k = 0;
                ft_free_str(buf);
                free(line);
            }
            else if (ft_strchr(line, '-'))
            {
                buf = ft_strsplit(line, '-');
                t_node *buf3;
                buf3 = ft_search(buf[0], rooms);
                buf3->rel = ft_strchrjoin(buf3->rel, buf[1], ' ');
                buf3 = ft_search(buf[1], rooms);
                buf3->rel = ft_strchrjoin(buf3->rel, buf[0], ' ');
                ft_free_str(buf);
            }
            else
            {
                int ant_count = ft_atoi(line);
            }

        }

    }
    return rooms;
}


