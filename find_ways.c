#include "lemin.h"

int     open_node(t_fdata *f_data, t_node *cur)
{
	int     i;
	
	i = 0;
	while (i < f_data->o_len)
	{
		if (ft_strcmp(cur->name, f_data->open[i]) == 0)
			return (0);
		i++;
	}
	i = 0;
    while (i < f_data->c_len)
    {
        if (ft_strcmp(cur->name, f_data->closed[i]) == 0)
            return (0);
        i++;
    }
	f_data->open[f_data->o_len] = ft_strdup(cur->name);
	f_data->o_len++;
	return (1);
}

int         close_node(t_fdata *f_data, t_node *cur)
{
	int     i;
	int     j;
	
	f_data->closed[f_data->c_len++] = ft_strdup(cur->name);
	i = 0;
	while (i < f_data->o_len)
	{
		if (ft_strcmp(f_data->open[i], cur->name) == 0)
		{
			while (i < f_data->o_len)
			{
				free(f_data->open[i]);
				f_data->open[i] = ft_strdup(f_data->open[i + 1]);
				i++;
			}
			free(f_data->open[i]);
			f_data->o_len--;
		}
		i++;
	}
	return (1);
}

int     add_ukaz(t_fdata *f_data, t_node *prev, char *cur)
{
	f_data->uks[f_data->u_len].cur = ft_strdup(cur);
	f_data->uks[f_data->u_len].prev = ft_strdup(prev->name);
	f_data->u_len++;
	return (1);
}

t_ulist *add_ul(t_ulist *ul, t_ukaz *uk)
{
	t_ulist *new;
	
	new = (t_ulist*)malloc(sizeof(t_ulist));
	new->val = uk;
	new->next = NULL;
	if (!ul)
		return (new);
	new->next = ul;
	return (new);
}

t_ukaz  *find_uk(t_node *cur, t_fdata *f_data)
{
	int     i;
	
	i = 0;
	while (i < f_data->u_len + 1)
	{
		if (ft_strcmp(cur->name, f_data->uks[i].cur) == 0)
			return (&f_data->uks[i]);
		i++;
	}
	return (NULL);
}

int     add_way(t_data *data, t_node *cur, t_fdata *f_data)
{
	t_way   *new;
	t_ulist *ul;
	int     i;
	
	ul = NULL;
	new = (t_way*)malloc(sizeof(t_way));
	new->len = 0;
	while (ft_strcmp(cur->name, data->start->name) != 0)
	{
		ul = add_ul(ul, find_uk(cur, f_data));
		cur = ft_search(ul->val->prev, data->nodes);
		new->len++;
	}
	i = 0;
	while (i < new->len)
	{
		new->way[i++] = ft_strdup(ul->val->cur);
		ul = ul->next;
	}
	data->ways[data->w_count] = new;
	data->w_count++;
	return (1);
}

t_node  *reset_search(t_data *data, t_fdata *f_data)
{
	int     i;
	int     j;
	
	f_data->o_len = 0;
	f_data->c_len = 0;
	f_data->u_len = 0;
	// dopisat free funkziu
	i = 0;
	while (i < data->w_count)
	{
		j = 0;
		while (j < data->ways[i]->len)
			close_node(f_data, ft_search(data->ways[i]->way[j++], data->nodes));
		i++;
	}
	open_node(f_data, data->start);
}

int     find_ways(t_data *data)
{
	t_fdata *f_data;
	t_node  *cur;
	char    **cur_rel;
	int     i;

    data->w_count = 0;
	f_data = (t_fdata*)malloc(sizeof(t_fdata));
	reset_search(data, f_data);
	while (f_data->open[0])
	{
		cur = ft_search(f_data->open[0], data->nodes);
		close_node(f_data, cur);
		i = 0;
		cur_rel = ft_strsplit(cur->rel, ' ');
		while (cur_rel[i] != NULL)
		{
			if (ft_strcmp(cur_rel[i], data->end->name) == 0)
			{
				add_way(data, cur, f_data);
				reset_search(data, f_data);
                break ;
			}
			if (open_node(f_data, ft_search(cur_rel[i], data->nodes)))
			    add_ukaz(f_data, cur, cur_rel[i]);
			i++;
		}
	}
}

