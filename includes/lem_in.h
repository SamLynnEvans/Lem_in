#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "limits.h"

typedef struct	s_node
{
	char	*name;
	int		*links;
	int		open;
	int		parent;
	int		distance;
	int		start;
	int		end;
}				t_node;

typedef struct	s_lem
{
	char **lines;
	int		ants;
	int		start;
	int		end;
	int 	rooms;
	int		count;
}				t_lem;

#endif
