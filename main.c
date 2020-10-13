#include <stdio.h>
#include "lemin.h"
#include <fcntl.h>



int main()
{
    int fd;
    fd = open("../test3.txt", O_RDONLY);
    t_data *all;
    all = ft_read(fd, MAP_SIZE);
    find_ways(all);
    go_lem(all);
    return 0;
}
