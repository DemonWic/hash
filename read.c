//
// Created by Виктор Рыжков on 04/10/2020.
//
#include "libft.h"
#include "lemin.h"


t_data *init_data(int size_map)
{
    t_data *data;

    data = NULL;
    data = (t_data *)ft_memalloc(sizeof(t_data));
    data->start = NULL;
    data->end = NULL;
    data->nodes = (t_node **)ft_memalloc((sizeof(t_node) * size_map));
    data->roads = (t_road **)ft_memalloc((sizeof(t_road) * size_map));
    data->lines = (char **)ft_memalloc((sizeof(char *) * size_map));
    if (data->nodes == NULL || data->roads == NULL || data->lines == NULL)
        return NULL;
    data->roads_count = 0;
    data->ant_count = 0;
    data->lines_count = 0;
    data->check  = 0;
    data->invalid = 0;
   return (data);
}

t_node *new_node(t_data *data, char **buf)
{
    t_node *new;

    new = (t_node *)ft_memalloc(sizeof(t_node));
    if (new == NULL)
        data->check = -1;
    new->name = ft_strdup(buf[0]);
    new->x = ft_atoi(buf[1]);
    new->y = ft_atoi(buf[2]);
    new->met = 0;
    new->exclude = 0;
    new->marker = data->check;
    new->rel = NULL;
    return (new);
}


void push_node(t_data *data, t_node *new, int id)
{
    t_node *uk;

    if (data->nodes[id] != NULL)
    {
        uk = data->nodes[id];
        while(uk->next != NULL)
            uk = uk->next;
        uk->next = new;
    }
    else
        data->nodes[id] = new;
}

void  add_start_end(t_data *data, t_node *new)
{
    if (data->check == 3)
    {
        if (data->start != NULL)
            data->check = -1;
        data->start = new;
        data->check = 0;
    }
    else if (data->check == 4)
    {
        if (data->end != NULL)
            data->check = -1;
        data->end = new;
        data->check = 0;
    }
}

void  add_node(t_data *data, char *line, int size_map)
{
    t_node *new;
    char **buf;
    int id;

    data->lines[data->lines_count++] = ft_strdup(line);
    buf = ft_strsplit(line, ' ');
    id = ft_hash(buf[0], size_map);
    new = new_node(data, buf);
    push_node(data, new, id);
    if (data->check == 3 || data->check == 4)
        add_start_end(data, new);
    ft_free_str(buf);
    data->check = 0;
}

void  add_rel(t_data *data, char *line)
{
    char **buf;
    t_node *buf3;

    data->lines[data->lines_count++] = ft_strdup(line);
    buf = ft_strsplit(line, '-');
    buf3 = ft_search(buf[0], data->nodes);
    buf3->rel = ft_strchrjoin(buf3->rel, buf[1], ' ');
    buf3 = ft_search(buf[1], data->nodes);
    buf3->rel = ft_strchrjoin(buf3->rel, buf[0], ' ');
    ft_free_str(buf);
}

int check_sharp(t_data *data, char *line)
{
    if (ft_strcmp("##start", line) == 0)
    {
        data->check = 3;
        data->lines[data->lines_count++] = ft_strdup(line);
    }
    else if (ft_strcmp("##end", line) == 0)
    {
        data->check = 4;
        data->lines[data->lines_count++] = ft_strdup(line);
    }
    else if (line[0] == '#')
    {
        data->lines[data->lines_count++] = ft_strdup(line);
    }
    else if (line[0] == 'L')
        return (-1);
    return (0);
}

int check_line(t_data *data, char *line, int size_map)
{
    if (line[0] == '#' || line[0] == 'L')
        return (check_sharp(data, line));
    else if (ft_strchr(line, ' '))
    {
        add_node(data, line, size_map);
        if (data->check == -1)
            return (-1);
    }
    else if (ft_strchr(line, '-'))
        add_rel(data, line);
    else if (ft_strlen(line) == 0)
        return (1);
    else if (ft_isnumber(line))
        {
        data->lines[data->lines_count++] = ft_strdup(line);
        data->ant_count = ft_atoi(line);
        }
    else
        {
        data->invalid = 1; // возможно можно убрать, надо проверить если будет много строк
        return (-1);
    }
    return (0);
}


t_data *ft_read(int fd, int size_map)
{
    int i;
    int k;
    char *line;
    t_data *data;

    k = 0;
    data = init_data(size_map);
    if (data == NULL)
        return (NULL);
    while((i = get_next_line(fd,&line)) > 0)
    {
        k = check_line(data, line, size_map);
        if (k == -1)
            return (NULL);
        else if (k == 1)
        {
            ft_strdel(&line);
            break;
        }
        ft_strdel(&line);
    }
    return data;
}


