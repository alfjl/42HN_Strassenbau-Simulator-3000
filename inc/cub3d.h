#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/inc/libft.h"
# include <math.h>

//Settings
# define LINUX 1
# define COLISSION 1
# define MICROMAP 1
# define SHADES 1
# define OS LINUX
//Parameters
# define GRID_SIZE 16
# define MICROMAP_RADIUS 4
# define MICROMAP_OFFSET 10
# define TEXTURE_SIZE 32
# define STEP 0.035
# define STEP_A 0.025
# define NOSE 200
# define DISTANCE_FACTOR 20
# define DISTANCE 0.2
# define PLAYER_SIZE 5
# define ANGLE_OF_VIEW_CONST 60
# define ANGLE_OF_VIEW ANGLE_OF_VIEW_CONST
# define WINDOW_HEIGHT 512
# define WINDOW_WIDTH (2 * WINDOW_HEIGHT)
# define NUMBER_OF_RAYS WINDOW_WIDTH
# define MINIMAP_RAY_DENSITY_FACTOR 10
# define WALL_HEIGHT_RATIO 1
# define DEPTH_OF_FIELD (2 * WINDOW_HEIGHT)
//Math
# define PI 3.1415926535
# define PI1_2 (PI / 2)
# define PI3_2 (3 * PI1_2)
# define EDGE 0.00001
# define DR 0.0174533
//Color Theme
//Linux
# define ALPHA ((0xff) << 24)
//Mac
// # define ALPHA 0
# define SHADE_NORTH 1.0
# define SHADE_SOUTH 0.5
# define SHADE_EAST 0.8
# define SHADE_WEST 0.8
# define RAY_COLOR RED
# define MINIMAP_SPACE_COLOR WHITE
# define MINIMAP_WALL_COLOR GREY
# define MINIMAP_GRID_COLOR BLACK
# define MINIMAP_BACKGROUND_COLOR BLACK
# define MINIMAP_PLAYER_COLOR BLACK
//DEBUG
# define MINIMAP 0

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
	bool	backwards;
	bool	leftwards;
	bool	rightwards;
	bool	turnleft;
	bool	turnright;
} t_keys;

typedef enum e_mapchars
{
	WALL = '1',
	SPACE = '0',
	PLAYER_NORTH = 'N',
	PLAYER_SOUTH = 'S',
	PLAYER_EAST = 'E',
	PLAYER_WEST = 'W',
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
	OLIVE = 0xFF808000,
	AQUA = 0xFF00FFFF,
	CYAN = 0xFF00FFFF,
	BLUE = 0xFF0000FF,
	NAVY = 0xFF000080,
	MAGENTA = 0xFFFF00FF,
	BLACK = 0xFF000000,
	GREY = 0xFF808080,
	DARK_GREY = 0xFF424949,
	SILVER = 0xFFC0C0C0,
	WHITE = 0xFFFFFFFF,
	TRANSPARENT = 0x00000000,
}	t_colorcode;

typedef enum e_errorcodes
{
	SUCCESS = -2,
	SYSTEM = -1,
	MLX,
	MLX_WIN,
	MLX_IMAGE,
	ERRORS
}	t_errorcodes;

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*path;
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
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_orientation;

typedef struct s_ray
{
	int			index;
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	float		len;
	float		dist;
	float		line_h;
	int			orientation;
	float		tyoffset;
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
	NOSE_IMG,
	MINIMAP_IMG,
	MICROMAP_IMG,
	BACKGROUND_IMG,
	WALLS_IMG,
	RAYS_IMG,
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
	int					height;
	int					width;
	struct s_color		floor;
	struct s_color		ceiling;
	struct s_textures	textures;
}				t_map;

typedef struct s_fps
{
	long	lastTime;
	bool		first;
}				t_fps;

typedef struct s_data
{
	char			*filepath; //remove
	struct s_frame	screen;
	struct s_map	map;
	char			**map_old; //remove
	struct s_frame	grid; //remove
	void			*mlx;
	void			*win;
	struct s_frame	minimap;
	struct s_frame	window;
	int				line_w;
	t_img			imgs[IMAGES];
	int				img_size;
	struct s_player	player;
	struct s_ray	rays[NUMBER_OF_RAYS];
	// struct s_enemy	enemys;
	// int				texture[32];
	struct s_fps	fps; //remove
	long			time; //remove
}	t_data;


t_data	*data(void);
void	read_map(char *filepath);
void	mlx(void);
int		game(t_keys *keys);
void	player_update_position(t_keys *keys);
bool	is_wall(float y, float x);
void	player_nose_draw_to_image(void);
void	rays_create(void);
void	rays_draw_to_image(void);
t_ray	ray_calculate_vertical(float angle);
t_ray	ray_calculate_horizontal(float angle);
void	images_create(void);
void	textures_load(void);
int		exit_program(int errorcode);
void	walls_draw_to_image(void);
void	micromap_draw_to_image(void);
//utils
void			my_pixel_put(t_img *img, int x, int y, int color);
void			draw_line_a_to_b(t_img *img, t_point a, t_point b, int color);
unsigned int	create_rgba(int r, int g, int b, int a);
unsigned int	create_argb(int r, int g, int b, int a);
unsigned int	argb_color_shade(int color, float brightness);
float			radian_limits(float angle);
void			*my_new_image(void *mlx_ptr, int width, int height, t_img *img);
void			my_destroy_image(void *mlx_ptr, t_img *img);
bool			pixel_is_outside_img_limits(int x, int y, t_img *img);
void			image_fill(t_img *img, int color);
t_img			*image_clone(void *mlx, t_img *src, t_img *dst);
//fps
void	fps_to_window_buffer(void); //remove
void	timedifference(char *str); //remove
#endif