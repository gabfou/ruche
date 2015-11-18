// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gfournie <gfournie@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/18 02:25:27 by gfournie          #+#    #+#             //
//   Updated: 2015/11/18 14:39:34 by gfournie         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../inc/ft_gkrellm.hpp"

t_env e;

void initmlx()
{
	char name[2];
	name[0] = '1';
	name[1] = 0;
	e.l = 1280;
	e.h = 800;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.l, e.h, name);
	e.img = mlx_new_image(e.mlx, e.l, e.h);
	e.addr = mlx_get_data_addr(e.img, &(e.bpp), &(e.sizel), &(e.endian));
//	bzero(e.tab, 10);
}

int loop_hook(void *v)
{
 //	t_env *e = static_cast<t_env>(v);
	(void)v;
	write(1, "dsad\n", 5);
	sleep(1);
//	bzero(e.addr, e.h * e.sizel + e.l * e.bpp / 8);
	preparator(e);
	render2(e);
//	bzero(e.addr, strlen(e.addr));
//	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
//	mlx_do_sync(e.mlx);
	return (0);
}

int key_hook(int keycode, void *v)
{
//	t_env *e = static_cast<t_env>(v);
	(void)v;
	if (keycode == 53)
		exit(0);
	return (0);
}

void	start_term(void)
{
	initscr();
	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_RED);
		init_pair(2, COLOR_BLACK, COLOR_GREEN);
	}
	curs_set(0);
	timeout(1);
	noecho();
}

void	end_term(void)
{
	endwin();
}

int	main(int argc, char **argv)
{
	void *v = NULL;
	int (*ptr)(int,void*);
	ptr = key_hook;
	int (*ptr2)(void*);
	ptr2 = loop_hook;

	if (argc != 2 || (argv[1][0] != '1' && argv[1][0] != '2'))
		return (0);
	if (argv[1][0] == '1')
	{
		std::cout << "dsda" <<std::endl;
		start_term();
		while (42)
		{
			req_render();
			controller();
		}
	}
	else
	{
		std::cout << "dsdf" <<std::endl;
		initmlx();
//		render2(e);
		mlx_key_hook(e.win, ptr, v);
//        mlx_mouse_hook (e.win, mouse_hook, &e);
//        mlx_hook(e.win, 6, 1 << 7, autrefonction, &e);
        mlx_loop_hook(e.mlx, ptr2, v);
		std::cout << "dsdi" <<std::endl;
        mlx_loop(e.mlx);
	}
	return (0);
}
