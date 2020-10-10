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

//    int i = 0;
//    int j = 0;
//    while (i < MAP_SIZE)
//    {
//        if (all->nodes[i] != NULL)
//            j++;
//        t_node *trash = all->nodes[i];
//        while (trash != NULL)
//        {
//            printf("%s x=%i y=%i, rel=%s\n", trash->name, trash->x, trash->y, trash->rel);
//            trash = trash->next;
//        }
//        i++;
//    }
//
//
//
//    t_node *test;
//    test = ft_search("Hwu4", all->nodes);
//    printf("---------------->>>>>>>>>>\n");
//    printf("%s x=%i y=%i rel=%s\n", test->name, test->x, test->y, test->rel);
//    printf("%s x=%i y=%i rel=%s\n", all->start->name, all->start->x, all->start->y, all->start->rel);
//    printf("%s x=%i y=%i rel=%s\n", all->end->name, all->end->x, all->end->y, all->end->rel);
//    printf("%i\n", j);

    return 0;
}
