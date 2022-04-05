#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/inc/libft.h"
// # include <stdlib.h>
#include <math.h>

# define GRID_SIZE 32
# define STEP 0.2
# define STEP_A 0.2
# define NOSE 100
# define PLAYER_SIZE 5
# define PI 3.1415926535


typedef enum e_x11events
{
	KeyPress = 2,
	DestroyNotify = 17,
}	t_x11events;

typedef enum e_x11masks
{
	KeyPressMask = 1L << 0,
	StructureNotifyMask = 1L << 17,
}	t_x11masks;

//Linux
typedef enum e_key
{
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	UP_KEY = 65362,
	LEFT_KEY = 65361,
	DOWN_KEY = 65364,
	RIGHT_KEY = 65363,
	ESC_KEY = 65307,
}	t_key;

//mac
// typedef enum e_key
// {
// 	W_KEY = 13,
// 	A_KEY = 0,
// 	S_KEY = 1,
// 	D_KEY = 2,
// 	UP_KEY = 126,
// 	LEFT_KEY = 123,
// 	DOWN_KEY = 125,
// 	RIGHT_KEY = 124,
// 	ESC_KEY = 53,
// }	t_key;

typedef enum e_direction
{
	FORWARDS = 1,
	LEFT = 2,
	BACKWARDS = 3,
	RIGHT = 4,
}	t_direction;

typedef enum e_map
{
	WALL = '1',
	SPACE = '0',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
}	t_map;


typedef enum e_color
{
	RED = 0x00FF0000,
	ORANGE = 0x00FF8000,
	YELLOW = 0x00FFFF00,
	GREEN = 0x0000FF00,
	CYAN = 0x0000FFFF,
	BLUE = 0x000000FF,
	MAGENTA = 0x00FF00FF,
	BLACK = 0x00000000,
	GREY = 0x00808080,
	WHITE = 0x00FFFFFF,
}	t_color;

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	int		side;
}				t_player;

typedef struct s_ray
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
}				t_ray;

typedef struct s_enemy
{
	int		x;
	int		y;
	bool	status;
}				t_enemy;

typedef struct s_frame
{
	int		height;
	int		width;
}				t_frame;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef enum e_imgnr
{
	PLAYER_IMG,
	MINIMAP_IMG,
	IMAGES,
}	t_imgnr;

typedef struct s_data
{
	// bool			errorflags[ERRORS];
	char			*filepath;
	struct s_frame	screen;
	char			**map;
	struct s_frame	grid;
	void			*mlx;
	void			*win;
	struct s_frame	window;
	t_img			imgs[IMAGES];
	int				img_size;
	struct s_player	player;
	struct s_enemy	enemy;
	int				dx;
	int				dy;
}	t_data;

// typedef enum e_errorcode
// {
// 	ARGUMENTS,
// 	NOFILE,
// 	SHAPE,
// 	WALLS,
// 	SPAWN,
// 	NOEXIT,
// 	NOLOOT,
// 	WRONGFILE,
// 	MALLOC,
// 	OPEN,
// 	CLOSE,
// 	IMAGE,
// 	ERRORS,
// 	SETUP,
// }	t_errorcode;

t_data	*data(void);
void	read_map(char *filepath);
int		minimap(void);
void	mlx(void);
int		exit_program(void);
//utils
void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_line_a_to_b(t_img *img, t_point a, t_point b, int color);
// void	plot_line (t_point a, t_point b, t_img *img, int color);
#endif