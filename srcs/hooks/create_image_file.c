/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:53:32 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/19 16:17:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_headers(int filesize, t_img *pic, unsigned char *fileheader,
													unsigned char *infoheader)
{
	fileheader[2] = (unsigned char)(filesize);
	fileheader[3] = (unsigned char)(filesize >> 8);
	fileheader[4] = (unsigned char)(filesize >> 16);
	fileheader[5] = (unsigned char)(filesize >> 24);
	infoheader[4] = (unsigned char)(pic->width);
	infoheader[5] = (unsigned char)(pic->width >> 8);
	infoheader[6] = (unsigned char)(pic->width >> 16);
	infoheader[7] = (unsigned char)(pic->width >> 24);
	infoheader[8] = (unsigned char)(pic->height);
	infoheader[9] = (unsigned char)(pic->height >> 8);
	infoheader[10] = (unsigned char)(pic->height >> 16);
	infoheader[11] = (unsigned char)(pic->height >> 24);
	infoheader[21] = (unsigned char)(4 * (pic->height * pic->width));
	infoheader[22] = (unsigned char)((4 * (pic->height * pic->width)) >> 8);
	infoheader[23] = (unsigned char)((4 * (pic->height * pic->width)) >> 16);
	infoheader[24] = (unsigned char)(4 * (pic->height * pic->width) >> 24);
	infoheader[25] = (unsigned char)(39 * 72);
	infoheader[26] = (unsigned char)((39 * 72) >> 8);
	infoheader[27] = (unsigned char)((39 * 72) >> 16);
	infoheader[28] = (unsigned char)((39 * 72) >> 24);
	infoheader[29] = (unsigned char)(39 * 72);
	infoheader[30] = (unsigned char)((39 * 72) >> 8);
	infoheader[31] = (unsigned char)((39 * 72) >> 16);
	infoheader[32] = (unsigned char)((39 * 72) >> 24);
}

static void	write_in_file(t_img *pic, FILE *f)
{
	unsigned char	color[3];
	t_color			rgb_col;
	int				x;
	int				y;

	y = pic->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < pic->width)
		{
			rgb_col = color_from_pixel(pic, x, y);
			color[0] = rgb_col.b * 255;
			color[1] = rgb_col.g * 255;
			color[2] = rgb_col.r * 255;
			fwrite(&color, 1, 3, f);
			x++;
		}
		y--;
	}
}

void		create_img_file(t_img *pic)
{
	FILE			*f;
	char			*str;
	int				filesize;
	unsigned char	*fileheader;
	unsigned char	*infoheader;

	fileheader = (unsigned char*)ft_strnew(14);
	infoheader = (unsigned char*)ft_strnew(40);
	fileheader[0] = 'B';
	fileheader[1] = 'M';
	fileheader[10] = 54;
	infoheader[0] = 40;
	infoheader[12] = 1;
	infoheader[14] = 24;
	filesize = 54 + (4 * (pic->height * pic->width));
	str = ft_strjoin(ft_itoa(time(NULL) / 60), ".bmp");
	fill_headers(filesize, pic, fileheader, infoheader);
	f = fopen(str, "wb");
	fwrite(fileheader, 1, 14, f);
	fwrite(infoheader, 1, 40, f);
	write_in_file(pic, f);
	fclose(f);
}
