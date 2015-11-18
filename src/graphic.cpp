// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graphic.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gfournie <gfournie@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/18 09:04:45 by gfournie          #+#    #+#             //
//   Updated: 2015/11/18 16:46:29 by gfournie         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../inc/ft_gkrellm.hpp"

void put_pixel(t_env & pos, int x, int y, int color)
{
	unsigned char color1;
	unsigned char color2;
	unsigned char color3;
	int img_size;

	img_size = pos.h * pos.l * pos.bpp / 8;
	if (x < 0 || y < 0 || y * pos.sizel + x * pos.bpp / 8 > img_size
		|| x >= pos.sizel / (pos.bpp / 8) || y >= img_size / pos.sizel)
		return ;
	color1 = color >> 0;
	color2 = color >> 8;
	color3 = color >> 16;
	pos.addr[y * pos.sizel + x * pos.bpp / 8] = color1;
	pos.addr[y * pos.sizel + x * pos.bpp / 8 + 1] = color2;
	pos.addr[y * pos.sizel + x * pos.bpp / 8 + 2] = color3;
}

void put_barxel(t_env & pos, int x, int y, int color)
{
    unsigned char color1;
    unsigned char color2;
    unsigned char color3;
    int img_size;

    img_size = pos.h * pos.l * pos.bpp / 8;
    if (x < 0 || y < 0 || y * pos.sizel + x * pos.bpp / 8 > img_size
        || x >= pos.sizel / (pos.bpp / 8) || y >= img_size / pos.sizel)
        return ;
    color3 = static_cast<unsigned char>(255);
    color2 = color;
    color1 = 0;
    pos.addr[y * pos.sizel + x * pos.bpp / 8] = color1;
    pos.addr[y * pos.sizel + x * pos.bpp / 8 + 1] = color2;
    pos.addr[y * pos.sizel + x * pos.bpp / 8 + 2] = color3;
}

void bar(int i, int x, int y, t_env & e)
{
	int x2;
	while (--i > 0)
	{
		x2 = 0;
		while (x2++ < 5)
			put_barxel(e, x + x2, y, -i + 200);
		y--;
	}
}

void preparator(t_env & e)
{
	int    x;
	int    y;

	y = -1;
	while (++y < e.h)
	{
		x = -1;
		while (++x < e.l)
			put_pixel(e, x, y, 0x555555);
	}
	y = 299;
	while (++y < 501)
	{
		x = 99;
		while (++x < 301)
			put_pixel(e, x, y, 0x333333);
	}
	y = 299;
	while (++y < 501)
    {
        x = 319;
        while (++x < 521)
            put_pixel(e, x, y, 0x333333);
    }
	y = 299;
	while (++y < 501)
    {
        x = 539;
        while (++x < 741)
            put_pixel(e, x, y, 0x333333);
    }
	y = 299;
	while (++y < 501)
    {
        x = 759;
        while (++x < 961)
            put_pixel(e, x, y, 0x333333);
    }
	y = 49;
    while (++y < 250)
    {
        x = 759;
		while (++x < 1161)
            put_pixel(e, x, y, 0x333333);
    }
}
