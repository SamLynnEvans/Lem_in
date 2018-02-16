#include "vis.h"
#include <locale.h>
void	print_toscreen(t_vis *v)
{
	while (1)
	{
		v->img = mlx_new_image(v->mlx, 500, 500);
		v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
		v->data[0] = 0xFF;
		v->data[1] = 0xFF;
		v->data[2] = 0xFF;
		mlx_clear_window(v->mlx, v->win);
		sleep(1);
		mlx_put_image_to_window(v->mlx, v->win, v->img, 100, 100);
		sleep(1);
	}
}

void	print_start(t_vis *v)
{
	char martini[5] = {0xF0, 0x9F, 0x8D, 0xB8, '\0'};
	setlocale(LC_ALL, "en_US.utf8");
	mlx_string_put(v->mlx, v->win, 330, 300, 0xFFFFFF, "ANTZ");
	mlx_string_put(v->mlx, v->win, 250, 330, 0xFFFFFF, "press enter to begin");
	mlx_string_put(v->mlx, v->win, 250, 350, 0xFFFFFF, martini);
//	v->img = mlx_new_image(v->mlx, 500, 500);
//	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
	

}
/*
int	start_game(t_vis *v)
{
	int	i;

}
*/
int		begin_game(int key, t_vis *v)
{
	static int first = 0;

	ft_intdebug(key, "key");
		if (key == 53)
			exit(1);
	if (key == 36 && first == 0)
	{
		start_game(v);
		first = 1;
	}
	return (1);
}

void	visualiser(t_node *n, t_vis *v)
{
	if (n)
		;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 700, 700, "ANTS");
	mlx_key_hook(v->win, begin_game, v);
	print_start(v);
//	print_toscreen(v);
	mlx_loop(v->mlx);
//	ft_putstr("poo");
}
