#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct	s_node
{
	char	*name;
	int		*links;
	int		parent;
	int		distance;
	int		start;
	int		end;
}					t_node;

#endif
