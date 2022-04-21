#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include "libft.h"
# include <math.h>

//Settings
# define COLLISION 1
# define MINIMAP 1
# define SHADES 1
//mlx
# define LINUX 1
# define HAS_ALPHA 0
//Parameters
# define WINDOW_HEIGHT 512
# define GRID_SIZE 16
# define TEXTURE_SIZE 512
# define MINIMAP_RADIUS 4
# define MINIMAP_OFFSET 10
# define MINIMAP_RAY_DENSITY_FACTOR 20
# define STEP 0.06
# define STEP_A 0.035
# define COLLISION_DISTANCE 0.20
# define PLAYER_SIZE 4
# define ANGLE_OF_VIEW_CONST 60
# define ANGLE_OF_VIEW ANGLE_OF_VIEW_CONST
# define NUMBER_OF_RAYS WINDOW_WIDTH
# define WALL_HEIGHT_RATIO 1
//Math
# define EDGE 0.00001
# define DR 0.0174533
//Color Theme
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

typedef enum e_defines
{
	WINDOW_WIDTH = (2 * WINDOW_HEIGHT),
	DEPTH_OF_FIELD = (2 * WINDOW_HEIGHT),
}	t_defines;

typedef enum e_argb_colorcode
{
	COLOR_RED = 0x00FF0000,
	COLOR_ORANGE = 0x00FF8000,
	COLOR_YELLOW = 0x00FFFF00,
	COLOR_GREEN = 0x0000FF00,
	COLOR_CYAN = 0x0000FFFF,
	COLOR_BLUE = 0x000000FF,
	COLOR_MAGENTA = 0x00FF00FF,
	COLOR_BLACK = 0x00000000,
	COLOR_GREY = 0x00808080,
	COLOR_WHITE = 0x00FFFFFF,
	COLOR_OLIVE = 0x00808000,
	COLOR_AQUA = 0x0000FFFF,
	COLOR_NAVY = 0x00000080,
	COLOR_DARK_GREY = 0x00424949,
	COLOR_SILVER = 0x00C0C0C0,
	COLOR_TRANSPARENT = 0xFF000000,
}	t_argb_colorcode;

# if LINUX
#  define ALPHA 0xFF000000

typedef enum e_keycode_linux
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
}	t_keycode_linux;

typedef enum e_argb_colorcode_linux
{
	RED = COLOR_RED + ALPHA,
	ORANGE = COLOR_ORANGE + ALPHA,
	YELLOW = COLOR_YELLOW + ALPHA,
	GREEN = COLOR_GREEN + ALPHA,
	CYAN = COLOR_CYAN + ALPHA,
	BLUE = COLOR_BLUE + ALPHA,
	MAGENTA = COLOR_MAGENTA + ALPHA,
	BLACK = COLOR_BLACK + ALPHA,
	GREY = COLOR_GREY + ALPHA,
	WHITE = COLOR_WHITE + ALPHA,
	OLIVE = COLOR_OLIVE + ALPHA,
	AQUA = COLOR_AQUA + ALPHA,
	NAVY = COLOR_NAVY + ALPHA,
	DARK_GREY = COLOR_DARK_GREY + ALPHA,
	SILVER = COLOR_SILVER + ALPHA,
	TRANSPARENT = COLOR_TRANSPARENT + ALPHA,
}	t_argb_colorcode_linux;
# else
#  define ALPHA 0

typedef enum e_keycode_mac
{
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	UP_KEY = 126,
	LEFT_KEY = 123,
	DOWN_KEY = 125,
	RIGHT_KEY = 124,
	ESC_KEY = 53,
}	t_keycode_mac;

typedef enum e_argb_colorcode_mac
{
	RED = COLOR_RED,
	ORANGE = COLOR_ORANGE,
	YELLOW = COLOR_YELLOW,
	GREEN = COLOR_GREEN,
	CYAN = COLOR_CYAN,
	BLUE = COLOR_BLUE,
	MAGENTA = COLOR_MAGENTA,
	BLACK = COLOR_BLACK,
	GREY = COLOR_GREY,
	WHITE = COLOR_WHITE,
	OLIVE = COLOR_OLIVE,
	AQUA = COLOR_AQUA,
	NAVY = COLOR_NAVY,
	DARK_GREY = COLOR_DARK_GREY,
	SILVER = COLOR_SILVER,
	TRANSPARENT = COLOR_TRANSPARENT,
}	t_argb_colorcode_mac;
# endif

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

typedef enum e_imgnbr
{
	PLAYER_IMG,
	MINIMAP_IMG,
	BACKGROUND_IMG,
	WALLS_IMG,
	NORTH_IMG,
	SOUTH_IMG,
	EAST_IMG,
	WEST_IMG,
	TMP_IMG,
	IMAGES,
}	t_imgnbr;

typedef enum e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_orientation;

typedef enum e_mapchars
{
	WALL = '1',
	SPACE = '0',
	PLAYER_NORTH = 'N',
	PLAYER_SOUTH = 'S',
	PLAYER_EAST = 'E',
	PLAYER_WEST = 'W',
}	t_mapchars;

typedef enum e_errorcodes
{
	SUCCESS = -2,
	SYSTEM = -1,
	MLX,
	MLX_WIN,
	MLX_IMAGE,
	ERRORS
}	t_errorcodes;

typedef struct s_keys
{
	bool	forwards;
	bool	backwards;
	bool	leftwards;
	bool	rightwards;
	bool	turnleft;
	bool	turnright;
}	t_keys;

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	void	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	char	*path;
}	t_img;

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
}				t_player;

typedef struct s_ray
{
	int			index;
	float		x;
	float		y;
	float		mini_x;
	float		mini_y;
	float		dx;
	float		dy;
	float		angle;
	float		len;
	float		dist;
	float		line_h;
	int			orientation;
	float		tyoffset;
}	t_ray;

typedef struct s_frame
{
	int		height;
	int		width;
}	t_frame;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	rgb;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

typedef struct s_map
{
	char				**grid;
	int					height;
	int					width;
	struct s_color		floor;
	struct s_color		ceiling;
	struct s_textures	textures;
}	t_map;

typedef struct s_fps
{
	long	last_time;
	bool	first;
}	t_fps;

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
	struct s_fps	fps; //remove
	long			time; //remove
}	t_data;

t_data	*data(void);
void	read_map(char *filepath);
void	mlx(void);
int		frame_loop(t_keys *keys);
void	player_update_position(t_keys *keys);
bool	is_wall(float y, float x);
void	player_nose_draw_to_image(void);
void	rays_create(void);
t_ray	ray_calculate_vertical(float angle);
t_ray	ray_calculate_horizontal(float angle);
void	iterate_grid(t_ray *ray);
void	images_create(void);
void	textures_load(void);
int		exit_program(int errorcode);
int		exit_program_success(void);
void	walls_draw_to_image(void);
void	draw_vertical_line(t_img *img, t_point s, t_point e, int i);
void	minimap_draw_to_image(void);
//utils
void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_line_a_to_b(t_img *img, t_point a, t_point b, int color);
uint	create_rgba(int r, int g, int b, int a);
uint	create_argb(int r, int g, int b, int a);
uint	argb_color_shade(int color, float brightness);
float	radian_limits(float angle);
void	*my_new_image(void *mlx_ptr, int width, int height, t_img *img);
void	my_destroy_image(void *mlx_ptr, t_img *img);
bool	is_inside_limits(int x, int y, t_img *img);
void	image_fill(t_img *img, int color);
t_img	*image_clone(void *mlx, t_img *src, t_img *dst);
void	calculate_pos_delta(void);
//mlx
void	*mlx_new_image_alpha(void *mlx_ptr, int width, int height);
//fps
void	fps_to_window_buffer(void); //remove
void	timedifference(char *str); //remove
#endif