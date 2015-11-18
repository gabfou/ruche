// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ft_gkrellm.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gfournie <gfournie@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/18 03:57:03 by gfournie          #+#    #+#             //
//   Updated: 2015/11/18 16:21:19 by gfournie         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef FT_GKRELLM_HPP
# define FT_GKRELLM_HPP

# include "../mlx/mlx.h"
# include <sys/sysctl.h>
# include <sys/types.h>
# include <ncurses.h>
# include <iostream>
# include <unistd.h>
# include <cstdlib>
# include <pwd.h>


typedef struct s_env
{
	int h;
	int l;
	void *win;
	void *mlx;
	void *img;
	char *addr;
	int bpp;
	int endian;
	int sizel;
	int tab[40];
	int tab2[40];
	int tab3[40];
	int tab4[40];
	int tab5[80];
}				t_env;

void	put_pixel(t_env & pos, int x, int y, int color);
void	render(void);
void	render2(t_env & e);
void	bar(int i, int x, int y, t_env & e);
void	preparator(t_env & e);
void	req_render(void);
void	controller(void);
void	start_term(void);
void	end_term(void);

#endif
