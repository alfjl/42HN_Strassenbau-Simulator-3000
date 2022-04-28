#include "cub3d.h"

void	ft_floor(t_img *img)
{
	int	y;
	int	x;
	int	screenHeight = data()->window.height;
	int	h = screenHeight; //halbe?
	int	screenWidth = data()->window.width;
	float	posX = data()->player.x;
	float	posY = data()->player.y;
	// float	dirX = data()->player.dx; // maybe without step?
	// float	dirY = data()->player.dy;

	y = h / 2;
	while (y < h)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// float rayDirX0 = dirX - planeX;
		// float rayDirY0 = dirY - planeY;
		// float rayDirX1 = dirX + planeX;
		// float rayDirY1 = dirY + planeY;
		// float rayDirX0 = data()->rays[0].dx;
		// float rayDirY0 = data()->rays[0].dy;
		// float rayDirX1 = data()->rays[NUMBER_OF_RAYS - 1].dx;
		// float rayDirY1 = data()->rays[NUMBER_OF_RAYS - 1].dy;
		float rayDirX0 = cos(data()->rays[0].angle);
		float rayDirY0 = sin(data()->rays[0].angle);
		float rayDirX1 = cos(data()->rays[NUMBER_OF_RAYS - 1].angle);
		float rayDirY1 = sin(data()->rays[NUMBER_OF_RAYS - 1].angle);
		// float rayDirX0 = cos(data()->rays[0].angle - radian_limits(data()->player.angle) + M_PI_2);
		// float rayDirY0 = sin(data()->rays[0].angle - radian_limits(data()->player.angle) + M_PI_2);
		// float rayDirX1 = cos(data()->rays[NUMBER_OF_RAYS - 1].angle + radian_limits(data()->player.angle) + M_PI_2);
		// float rayDirY1 = sin(data()->rays[NUMBER_OF_RAYS - 1].angle + radian_limits(data()->player.angle) + M_PI_2);

		

		// Current y position compared to the center of the screen (the horizon)
		int p = y - screenHeight / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * screenHeight;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = posX + rowDistance * rayDirX0;
		float floorY = posY + rowDistance * rayDirY0;

		x = 0;
		while(x < screenWidth)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(TEXTURE_SIZE * (floorX - cellX)) & (TEXTURE_SIZE - 1);
			int ty = (int)(TEXTURE_SIZE * (floorY - cellY)) & (TEXTURE_SIZE - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// // choose texture and draw the pixel
			// int floorTexture = 3;
			// int ceilingTexture = 6;
			int color;

			// // floor
			// color = texture[floorTexture][texWidth * ty + tx];
			// color = (color >> 1) & 8355711; // make a bit darker
			// buffer[y][x] = color;

			int image = FLOOR_IMG;

			if (is_inside_image_limits(tx, ty, img))
			{
				color = *(unsigned int *)(data()->imgs[image].addr
						+ (unsigned int)((int)ty * data()->imgs[image].line_len
							+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
				my_pixel_put(img, x, y, color);
			}
			x++;
		}

		y++;
	}
}