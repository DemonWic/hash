#include "lemin.h"
#include <fcntl.h>



int main()
{

    int fd;
    int i;
    int j;
    int res;
    char *test;
    t_road *buf;

    i = 0;
    j = 0;
    res = 1;
    fd = 0;
    fd = open("../test_rooms.txt", O_RDONLY);
    if (read(fd, test, 0) == -1)
        ft_error("ERROR");
    t_data *all;
    all = ft_read(fd, MAP_SIZE);
    if (all == NULL || all->ant_count == 0 || all->start == NULL\
        || all->end == NULL || all->start->rel == NULL || all->end->rel == NULL)
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
    i = 0;
    char *buf2;
    while (i < all->lines_count)
    {
        buf2 = all->lines[i];
        printf("%s\n", buf2);
        i++;
    }
    go_lem(all);
    ft_datadel(all);
    return 0;
}


//['Zs_1', 'Pas0', 'W_x3', 'In_1', 'Hdi3', 'Etd8', 'Msz9', 'Q_d6', 'Iqc8', 'Vrg5', 'Aub7', 'Jjt8', 'Rfd7', 'Poa9', 'Gop1', 'Hwu4']
// ['Zs_1', 'Foy3', 'Oh_5', 'Xaf3', 'C_t9', 'Hcj8', 'Afy5', 'Puz7', 'Bzh6', 'Pzm8', 'S__8', 'Ewy4', 'Kwz1', 'Nxp5', 'Dih4', 'Wzn1', 'Jah8', 'Hwu4']18