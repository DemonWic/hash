#include "lemin.h"
#include <fcntl.h>


int error_check(t_data *all)
{
    if (all == NULL || all->ant_count == 0)
        return (1);
    if (all->start == NULL|| all->end == NULL)
        return (1);
    if (all->start->rel == NULL || all->end->rel == NULL )
        return (1);
    if (all->invalid == 1)
        return (1);
    return (0);
}

void print_map(t_data *all)
{
    int i;

    i = 0;
    while (i < all->lines_count)
    {
        ft_putstr(all->lines[i]);
        ft_putchar('\n');
        i++;
    }
}

void print_roads(t_data *all, int j)
{
    int i;
    t_road *buf;

    i = 0;
    printf("%i\n", all->roads_count);
    while(i < j)
    {

        buf = all->roads[i];
        printf("len = %i  - ", buf->len);
        while(buf)
        {
            printf("%s ", buf->edge);
            buf = buf->next;
        }
        printf("\n");
        i++;
    }
}

int main()
{

    int fd;
    int i;
    int j;
    int res;
    char *test;

    i = 0;
    j = 0;
    res = 1;
    fd = 0;
    fd = open("../test3.txt", O_RDONLY);
    if (read(fd, test, 0) == -1)
        ft_error("ERROR");
    t_data *all;
    all = ft_read(fd, MAP_SIZE);
    if (error_check(all))
    {
        ft_datadel(all);
        ft_error("ERROR");
    }
    while (res != 0)
    {
        res = bfs(all, i, j);
        j++;
        i += 3;
    }
    j--;
    print_roads(all, j);
    print_map(all);
    go_lem(all);
    ft_datadel(all);
    return 0;
}
