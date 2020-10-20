
#ifndef HASH_LEMIN_H
#define HASH_LEMIN_H
#define MAP_SIZE 4000

#include "libft.h"
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
    int         met;
    int         exclude;
    struct s_node *next;
}               t_node;


typedef struct  s_ukaz
{
    char        *prev;
    char        *cur;
}               t_ukaz;


typedef struct  s_way
{
    char        *way[MAP_SIZE];
    int         len;
}               t_way;

typedef struct  s_fdata
{
    char    *open[MAP_SIZE];
    char    *closed[MAP_SIZE];
    t_ukaz  uks[MAP_SIZE];
    int     u_len;
    int     o_len;
    int     c_len;
}               t_fdata;

typedef struct  s_lem
{
    t_way       *way;
    char        *pos;
    int         n;
    int         finished;
}               t_lem;

typedef struct  s_ulist
{
    struct s_ukaz   *val;
    struct s_ulist  *next;
}               t_ulist;


typedef struct  s_data
{
    t_node      *start;
    t_node      *end;
    t_node      **nodes;
    t_way       *ways[MAP_SIZE];
    int         w_count;
    int         col;
    int         ant_count;
    int         cur_n;
}               t_data;


///

typedef struct s_edge {
    char *begin;
    char *end;
}               t_edge;

typedef struct s_stack {
    t_edge elem[MAP_SIZE];
    int top;
}               t_stack;


typedef struct s_queue {
    char *qu[MAP_SIZE + 1];
    int rear;
    int frnt;
}              t_queue;

///



unsigned int ft_hash(const char * datum, int size);
//t_node **ft_read(int fd, int size_map);
t_node *ft_search(const char *name, t_node **rooms);
char *ft_strchrjoin(char *dest, char *src, char c);
t_data *ft_read(int fd, int size_map);
void	ft_nodedelone(t_node **alst);
void	ft_nodedel(t_node **alst);
void    ft_datadel(t_data *data);
int             find_ways(t_data *data);
int             go_lem(t_data *data);

//
void ft_stkinit(t_stack *stk);
int ft_stkpush(t_stack *stk, t_edge *edge);
t_edge *ft_stkpop(t_stack *stk);
int ft_stkempty(t_stack *stk);
void ft_quinit(t_queue *q);
int ft_quinsert(t_queue *q, char *s);
int ft_quempty(t_queue *q);
char *ft_qupop(t_queue *q);
void bfs(t_data *all, int count);

#endif
