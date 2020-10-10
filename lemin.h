
#ifndef HASH_LEMIN_H
#define HASH_LEMIN_H
#define MAP_SIZE 100000


//typedef struct  s_room
//{
//    int         x;
//    int         y;
//    int         marker;
//    char        *name;
//    char        *rel;  // соседи через пробел ' ' в одной строке.
//    struct s_room *next;       // на случай коллизий
//
//}               t_node;

typedef struct  s_link
{
    char        *s1;
    char        *s2;
}               t_link;

typedef struct  s_node
{
    char        *name;
    int         x;
    int         y;
    char        *rel;
    int         marker;
    struct s_node *next;
}               t_node;

typedef struct  s_ukaz
{
    char        *prev;
    char        *cur;
}               t_ukaz;

typedef struct  s_way
{
//    t_clist     *way;
    int         len;
}               t_way;

typedef struct  s_fdata
{
//    t_clist *open;
//    t_clist *closed;
    t_ukaz  uks[1000];
    int     u_len;
}               t_fdata;

typedef struct  s_lem
{
    t_way       *way;
    char        *pos;
    int         n;
}               t_lem;

typedef struct  s_data
{
    int         size_map; // 10000
    t_node      *start;
    t_node      *end;
    t_node      **nodes;
//    t_llist     *links;
//    t_wlist     *ways;
    int         ant_count;
    int         col;
    int         cur_n;
}               t_data;

unsigned int ft_hash(const char * datum, int size);
t_node **ft_read(int fd, int size_map);
t_node *ft_search(const char *name, t_node **rooms);
char *ft_strchrjoin(char *dest, char *src, char c);

#endif
