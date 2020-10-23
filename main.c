#include "lemin.h"
#include <fcntl.h>



int main()
{
    int fd;
    int i;
    int j;
    int res;
    t_road *buf;

    i = 0;
    j = 0;
    res = 1;
    fd = open("../test_rooms.txt", O_RDONLY);
    t_data *all;
    all = ft_read(fd, MAP_SIZE);
    while (res != 0)
    {
        res = bfs(all, i, j);
        j++;
        i += 3;
    }
    all->roads_count = --j;
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
    ft_datadel(all);
//    find_ways(all);
//    go_lem(all);
    return 0;
}


//['Zs_1', 'Pas0', 'W_x3', 'In_1', 'Hdi3', 'Etd8', 'Msz9', 'Q_d6', 'Iqc8', 'Vrg5', 'Aub7', 'Jjt8', 'Rfd7', 'Poa9', 'Gop1', 'Hwu4']
// ['Zs_1', 'Foy3', 'Oh_5', 'Xaf3', 'C_t9', 'Hcj8', 'Afy5', 'Puz7', 'Bzh6', 'Pzm8', 'S__8', 'Ewy4', 'Kwz1', 'Nxp5', 'Dih4', 'Wzn1', 'Jah8', 'Hwu4']18