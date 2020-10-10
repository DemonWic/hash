#include <stdio.h>
#include "libft.h"
#include "lemin.h"
#include <unistd.h>
#include <fcntl.h>



int main()
{

//    char *s2[] = {"Jas5", "Zdb0", "Dgf6", "Mlk6", "Zdx4", "Cx_8", "Pww7", "Qnk9", "Pru7", "Jna5", "Uch0", "Ryk1", "Epo2", "Hfz5", "Sag7"};
//
//    int k = 15;
//    int j = 0;
//    while(j < k)
//    {
//        printf("%s  = %i\n", s2[j], ft_hash(s2[j],10000));
//        j++;
//    }

//    int i;
//    char *line;
//    while((i = get_next_line(0,&line)) > 0)
//    {
//        printf("%s\n", line);
//        free(line);
//    }


/*
    int size_map = 10;
    t_node **test;
    test = (t_node **)ft_memalloc((sizeof(t_node) * size_map));
    if (test == NULL)
        return 0;
    test[0] = (t_node *)ft_memalloc(sizeof(t_node));
    if (test[0] == NULL)
        return 0;
    test[0]->name = "test0";
    test[0]->x = 0;
    test[0]->y = 0;
    test[0]->next = NULL;
    test[1] = (t_node *)ft_memalloc(sizeof(t_node));
    if (test[1] == NULL)
        return 0;
    test[1]->name = "test1";
    test[1]->x = 1;
    test[1]->y = 1;
    test[1]->next = NULL;
    test[2] = (t_node *)ft_memalloc(sizeof(t_node));
    if (test[2] == NULL)
        return 0;
    test[2]->name = "test2";
    test[2]->x = 2;
    test[2]->y = 2;
    test[2]->next = NULL;
    int i = 0;
    while (i < 3)
    {
        printf("%s x=%i y=%i\n", test[i]->name, test[i]->x, test[i]->y);
        i++;
    }
*/
//    if (argc < 2)
//    {
//        printf("need argument");
//        return (0);
//    }
//    else
//    {

        int fd;
        fd = 0;
        fd = open("/Users/ahintz/CLionProjects/hash/test_rooms.txt", O_RDONLY);
        t_node **buf;
        buf = ft_read(fd, MAP_SIZE);
        int i = 0;
        int j = 0;
        while (i < MAP_SIZE)
        {
            if (buf[i] != NULL)
                j++;
            t_node *trash = buf[i];
            while (trash != NULL)
            {
                printf("%s x=%i y=%i, rel=%s\n", trash->name, trash->x, trash->y, trash->rel);
                trash = trash->next;
            }
            i++;
        }



        t_node *test;
        test = ft_search("Hwu4", buf);
        printf("---------------->>>>>>>>>>\n");
        printf("%s x=%i y=%i rel=%s\n", test->name, test->x, test->y, test->rel);
        printf("%i\n", j);
//        char *tst = "Hello";
//        char *t1 = ft_strdup(tst);
//        printf("%s\n", t1);
//        char *t2 = "Asfds";
//        char *t3 = ft_strchrjoin(t1, t2, ' ');
//        printf("%s\n", t3);
//    }
    return 0;
}
