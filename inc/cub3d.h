#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/inc/libft.h"
// # include <stdlib.h>
#include <math.h>

# define GRID_SIZE 16
# define STEP 0.1
# define STEP_A 0.1
# define NOSE 50
# define PLAYER_SIZE 5
# define PI 3.1415926535
# define PI1 PI/2
# define PI3 3*PI1
# define EDGE 0.0001
# define DR 0.0174533/2
# define NUMBER_OF_RAYS 128
# define WINDOW_HEIGHT 512
# define WINDOW_WIDTH 1024
# define DEPTH_OF_FIELD 100


typedef enum e_x11events
{
	KeyPress = 2,
	KeyRelease = 3,
	DestroyNotify = 17,
}	t_x11events;

typedef enum e_x11masks
{
	KeyPressMask = 1L << 0,
	KeyReleaseMask = 1L << 1,
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

typedef struct s_keys
{
	bool	forwards;
	bool	turnleft;
	bool	backwards;
	bool	turnright;
} t_keys;

typedef enum e_mapchars
{
	WALL = '1',
	SPACE = '0',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
}	t_mapchars;

//mac
// typedef enum e_color
// {
// 	RED = 0x00FF0000,
// 	ORANGE = 0x00FF8000,
// 	YELLOW = 0x00FFFF00,
// 	GREEN = 0x0000FF00,
// 	CYAN = 0x0000FFFF,
// 	BLUE = 0x000000FF,
// 	MAGENTA = 0x00FF00FF,
// 	BLACK = 0x00000000,
// 	GREY = 0x00808080,
// 	WHITE = 0x00FFFFFF,
// }	t_color;

//linux
typedef enum e_colorcode
{
	RED = 0xFFFF0000,
	ORANGE = 0xFFFF8000,
	YELLOW = 0xFFFFFF00,
	GREEN = 0xFF00FF00,
	CYAN = 0xFF00FFFF,
	BLUE = 0xFF0000FF,
	MAGENTA = 0xFFFF00FF,
	BLACK = 0xFF000000,
	GREY = 0xFF808080,
	WHITE = 0xFFFFFFFF,
	TRANSPARENT = 0x00000000,
}	t_colorcode;

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
}				t_player;

typedef enum e_orientation
{
	HORIZONTAL,
	VERTICAL,
}	t_orientation;

typedef struct s_ray
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	float		len;
	float		dist;
	float		lineH;
	int			orientation;
}				t_ray;

// typedef struct s_enemy
// {
// 	int		x;
// 	int		y;
// 	bool	status;
// }				t_enemy;

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
	BACKGROUND_IMG,
	NORTH_IMG,
	SOUTH_IMG,
	EAST_IMG,
	WEST_IMG,
	IMAGES,
}	t_imgnr;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	rgb;
}				t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}				t_textures;

typedef struct s_map
{
	char				**grid;
	struct s_color		floor;
	struct s_color		ceiling;
	struct s_textures	textures;
}				t_map;

typedef struct s_data
{
	char			*filepath;
	struct s_frame	screen;
	struct s_map	map;
	char			**map_old;
	struct s_frame	grid;
	void			*mlx;
	void			*win;
	struct s_frame	minimap;
	struct s_frame	window;
	t_img			imgs[IMAGES];
	int				img_size;
	struct s_player	player;
	struct s_ray	rays[NUMBER_OF_RAYS];
	// struct s_enemy	enemys;
}	t_data;

t_data	*data(void);
void	read_map(char *filepath);
void	mlx(void);
int		game(t_keys *keys);
void	minimap_display(void);
// int		game(void);
void	create_images(void);
int		exit_program(void);
void	walls_display(void);
//utils
void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_line_a_to_b(t_img *img, t_point a, t_point b, int color);
#endif