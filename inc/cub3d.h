#ifndef CUB3D_H
# define CUB3D_H
/* ------------------------------- INCLUDES -------------------------------- */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

//Texture paths
# define TEXTURE_FLOOR "./textures/soil.xpm"
# define TEXTURE_CEILING "./textures/dirt_04.xpm"
# define TEXTURE_SKY "./textures/sky_tiled2048x1024.xpm"
//Environment Color Theme
# define SHADE_NORTH 0.6
# define SHADE_SOUTH 1.0
# define SHADE_EAST 0.8
# define SHADE_WEST 0.8
# define SHADE_FLOOR 0.6
# define SHADE_CEILING 1.0
//Settings
# define BONUS 0
# if BONUS
#  define COLLISION_ENABLED 1
#  define MINIMAP_ENABLED 1
#  define SHADING_ENABLED 1
#  define DOORS_ENABLED 1
#  define MOUSE_ENABLED 1
#  define SPRITES_ENABLED 1
#  define FPS_ENABLED 1
#  define SPRINT_ENABLED 1
#  define CROUCH_ENABLED 1
#  define JUMP_ENABLED 1
#  define FLOOR_TEXTURE_ENABLED 1
#  define CEILING_TEXTURE_ENABLED 0
#  define SKY_ENABLED 1
# else
#  define COLLISION_ENABLED 0
#  define MINIMAP_ENABLED 0
#  define SHADING_ENABLED 0
#  define DOORS_ENABLED 0
#  define MOUSE_ENABLED 0
#  define SPRITES_ENABLED 0
#  define FPS_ENABLED 0
#  define SPRINT_ENABLED 0
#  define CROUCH_ENABLED 0
#  define JUMP_ENABLED 0
#  define FLOOR_TEXTURE_ENABLED 0
#  define CEILING_TEXTURE_ENABLED 0
#  define SKY_ENABLED 0
# endif
//mlx
# define HAS_ALPHA 0
//Parameters
# define WINDOW_HEIGHT 512
# define ANGLE_OF_VIEW_CONST 60
# define ANGLE_OF_VIEW ANGLE_OF_VIEW_CONST
# define NUMBER_OF_RAYS WINDOW_WIDTH
# define WALL_HEIGHT_RATIO 1
# define MOUSE_TURN_FACTOR 1.0
# define MOUSE_ACCELERATION_FACTOR 1.5
# define MOUSE_ACCELERATION_KICK_IN 15
//Player Parameters
# define MOVE_STEP 0.06
# define TURN_STEP 0.035
# define COLLISION_DISTANCE 0.20
# define PLAYER_HIT_RANGE 1.5
# define PLAYER_SPRINT_FACTOR 2.0
//Minimap Parameters
# define MAP_GRID_SIZE 16
# define MINIMAP_RADIUS 4
# define MINIMAP_OFFSET 10
# define MINIMAP_RAY_DENSITY_FACTOR 20
# define MINIMAP_PLAYER_SIZE 4
//Minimap Colors Theme
# define MINIMAP_SPACE_COLOR WHITE
# define MINIMAP_WALL_COLOR GREY
# define MINIMAP_GRID_COLOR BLACK
# define MINIMAP_GRID_ENABLED 1
# define MINIMAP_BACKGROUND_COLOR BLACK
# define MINIMAP_PLAYER_COLOR BLACK
# define MINIMAP_RAY_COLOR RED
//Graphics
# define TEXTURE_SIZE 512
# define SPRITE_SIZE 512
# define MAX_SPRITE_COUNT 6
# define SPRITE_SPEED 3
//Calculation constants
# define EXTRA_EDGE 0.000001
# define ONE_DEGREE_IN_RAD 0.0174533
# define BUFFER_SIZE_CUB3D 20480

typedef enum e_defines
{
	WINDOW_WIDTH = (2 * WINDOW_HEIGHT),
	DEPTH_OF_FIELD = (2 * WINDOW_HEIGHT),
	CROUCH_DELTA = - (WINDOW_HEIGHT / 4),
	JUMP_DELTA = (WINDOW_HEIGHT / 3),
	GRAVITY = JUMP_DELTA / 8,
}	t_defines;

typedef enum e_buttons
{
	LEFT_BUTTON = 1,
	RIGHT_BUTTON,
}	t_buttons;

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
	COLOR_BROWN = 0x0037271B,
	COLOR_TRANSPARENT = 0xFF000000,
}	t_argb_colorcode;

# if defined(__linux__)
#  define LINUX 1
#  define ALPHA 0xFF000000

//showkey -a
typedef enum e_keycode_linux
{
	A_KEY = 97,
	D_KEY = 100,
	E_KEY,
	Q_KEY = 113,
	S_KEY = 115,
	W_KEY = 119,
	LEFT_KEY = 65361,
	UP_KEY,
	RIGHT_KEY,
	DOWN_KEY,
	ESC_KEY = 65307,
	CTRL_KEY = 65507,
	SHIFT_KEY = 65505,
	SPACE_KEY = 32,
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
	BROWN = COLOR_BROWN + ALPHA,
	TRANSPARENT = COLOR_TRANSPARENT + ALPHA,
}	t_argb_colorcode_linux;
# else
#  define LINUX 0
#  define ALPHA 0

typedef enum e_keycode_mac
{
	A_KEY = 0,
	S_KEY,
	D_KEY,
	Q_KEY = 12,
	W_KEY,
	E_KEY,
	LEFT_KEY = 123,
	RIGHT_KEY,
	DOWN_KEY,
	UP_KEY,
	ESC_KEY = 53,
	CTRL_KEY = 256,
	SHIFT_KEY,
	SPACE_KEY = 49,
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
	BROWN = COLOR_BROWN,
	TRANSPARENT = COLOR_TRANSPARENT,
}	t_argb_colorcode_mac;
# endif

typedef enum e_x11_events
{
	KeyPress = 2,
	KeyRelease = 3,
	MotionNotify = 6,
	DestroyNotify = 17,
}	t_x11_events;

typedef enum e_x11_masks
{
	KeyPressMask = 1L << 0,
	KeyReleaseMask = 1L << 1,
	PointerMotionMask = 1L << 6,
	StructureNotifyMask = 1L << 17,
}	t_x11_masks;

typedef enum e_sprite_nbr
{
	SHOVEL_SPRITE,
	SHOVEL_WALK_SPRITE,
	SHOVEL_HIT_SPRITE,
	SPRITE_NBR,
}	t_sprite_nbr;

typedef enum e_img_nbr
{
	PLAYER_IMG,
	MINIMAP_IMG,
	BACKGROUND_IMG,
	WALLS_IMG,
	NORTH_IMG,
	SOUTH_IMG,
	EAST_IMG,
	WEST_IMG,
	FLOOR_IMG,
	CEILING_IMG,
	SKY_IMG,
	TMP_IMG,
	IMG_NBR,
}	t_img_nbr;

typedef enum e_player_status
{
	IDLE =	SHOVEL_SPRITE,
	WALKING = SHOVEL_WALK_SPRITE,
	HITTING = SHOVEL_HIT_SPRITE,
}	t_player_status;

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
	VOID = 'X',
	PLAYER_NORTH = 'N',
	PLAYER_SOUTH = 'S',
	PLAYER_EAST = 'E',
	PLAYER_WEST = 'W',
}	t_mapchars;

typedef enum e_errorcodes
{
	MLX = 0,
	MLX_WIN,
	MLX_IMAGE,
	ARGUMENT_NR,
	WRONG_FILETYPE,
	FILE_NOT_OPEN,
	PROBLEM_READING_CONFIG,
	PROBLEM_READING_TEXTURE,
	WRONG_CONFIG_ARGS,
	WRONG_RGB_VALUES,
	INVALID_MAP,
	SYSTEM,
	ERRORS,
}	t_errorcodes;

typedef enum e_arguments
{
	NO,
	SO,
	WE,
	EA,
	CEILING,
	FLOOR
}	t_arguments;

typedef struct s_temp_buffer
{
	char		buffer[BUFFER_SIZE_CUB3D];
	int			read_head;
	int			write_head;
}			t_temp_buffer;

typedef struct s_stringbuilder
{
	char			*buffer;
	int				read_head;
	int				write_head;
}			t_stringbuilder;

typedef struct s_reader
{
	char			*string;
	char			*string_end;
	char			*current;
}			t_reader;

typedef struct s_config_file
{
	bool			map_reached;
	bool			player_position;
	char			*buffer;
	int				read_head;
	int				write_head;
	int				errorcode;
	unsigned int	north;
	unsigned int	south;
	unsigned int	east;
	unsigned int	west;
	unsigned int	ceiling;
	unsigned int	floor;
}			t_config_file;

typedef struct s_controls
{
	bool	forwards;
	bool	backwards;
	bool	leftwards;
	bool	rightwards;
	bool	turnleft;
	bool	turnright;
	bool	mouse_left;
	bool	mouse_right;
}	t_controls;

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

typedef struct s_sprite
{
	char		*name;
	int			count;
	int			counter;
	int			speed;
	int			sign;
	t_img		sequence[MAX_SPRITE_COUNT];
}	t_sprite;

typedef struct s_player
{
	float		x;
	float		y;
	float		step_size;
	float		turn_speed;
	float		dx;
	float		dy;
	float		dz;
	float		angle;
	int			status;
	bool		is_jumping;
	bool		is_crouching;
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
	bool		is_infinite;
	float		len;
	float		dist;
	float		line_h;
	int			orientation;
	float		tyoffset;
	int			screen_x;
	int			start_y;
	int			end_y;
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
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
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
	bool				empty_line_flag;
	char				**grid;
	char				walls[2];
	char				player_pos[5];
	unsigned int		height;
	unsigned int		width;
	unsigned int		spaces;
	struct s_color		ceiling;
	struct s_color		floor;
	struct s_textures	textures;
}				t_map;

typedef struct s_fps
{
	long	last_time;
	bool	first;
}	t_fps;

typedef struct s_data
{
	t_config_file	config_file;
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
	t_img			imgs[IMG_NBR];
	int				img_size;
	t_sprite		sprites[SPRITE_NBR];
	struct s_player	player;
	struct s_ray	rays[NUMBER_OF_RAYS];
}	t_data;

void				map_read(char *filepath);
void				images_create(void);
void				mlx(void);
void				controls_mouse(t_controls *controls);
void				controls_keyboard(t_controls *controls);
int					frame(t_controls *keys);
void				textures_load(void);
void				sprites_load(void);
void				rays_create(void);
t_ray				rays_calculate_vertical(float angle);
t_ray				rays_calculate_horizontal(float angle);
void				rays_iterate_grid(t_ray *ray);
void				minimap_draw_to_image(void);
void				walls_draw_to_image(void);
void				walls_draw_segment(t_data *data, t_img *img, t_ray *ray);
void				doors_open_door(void);
void				doors_close_door(void);
void				player_update_position(t_controls *keys);
void				player_update_z_position(void);
int					exit_end_program_error(int errorcode);
int					exit_end_program_success(void);
void				free_all(void);
int					get_sky_color(t_ray *ray, int y);
int					get_ceiling_color(t_ray *ray, int y);
int					get_floor_color(t_ray *ray, int y);
//utils
void				my_pixel_put(t_img *img, int x, int y, int color);
void				draw_line_a_to_b(t_img *img, t_point a, t_point b,
						int color);
unsigned int		rgba_create(int r, int g, int b, int a);
unsigned int		argb_create(int r, int g, int b, int a);
unsigned int		argb_shade_color(int color, float brightness);

t_data				*data(void);
float				radian_limits(float angle);
void				*my_new_image(void *mlx_ptr, int width, int height,
						t_img *img);
void				*my_xpm_file_to_image(void *mlx_ptr, char *path,
						t_img *img);
void				my_destroy_image(void *mlx_ptr, t_img *img);
int					my_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x,
						int *y);
int					my_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
int					my_mouse_hide(void *mlx_ptr, void *win_ptr);
int					my_mouse_show(void *mlx_ptr, void *win_ptr);
bool				is_inside_image_limits(int x, int y, t_img *img);
void				image_fill(t_img *img, int color);
t_img				*image_clone(void *mlx, t_img *src, t_img *dst);
void				image_overlay(t_img *src, t_img *dst, int dst_x, int dst_y);
int					get_pixel_color(t_img *img, int x, int y);
void				calculate_pos_delta(void);
double				pythagoras_hypotenuse(double a, double b);
int					my_abs(int a, int b);
//mlx
void				*mlx_new_image_alpha(void *mlx_ptr, int width, int height);
//fps
void				fps_to_window_buffer(void); //remove

/* ------------------------------- parsing.c ------------------------------- */
t_data				*data(void);
int					exit_program(int errorcode);

/* ------------------------------- utils_1.c ------------------------------- */
unsigned long long	ft_atoull(const char *str);

/* ------------------------------- utils_2.c ------------------------------- */
void				*ft_memset(void *b, int c, size_t len);
char				*read_fd(char *path);

/* ------------------------------- data.c ---------------------------------- */
void				data_init(void);

/* ------------------------------- data_utils_1.c -------------------------- */
void				config_file_destroy(t_config_file *config_file);
void				map_destroy(t_map *map);
void				player_set_values(t_player *player, t_map *map,
						int x, int y);

/* ------------------------------- data_utils_2.c -------------------------- */
void				color_init(t_color *color);
void				textures_init(t_textures *textures);
void				textures_destroy(t_textures *textures);

/* ------------------------------- stringbuilder.c ------------------------- */
void				stringbuilder_init(t_stringbuilder *builder);
void				stringbuilder_destroy(t_stringbuilder *builder);
bool				stringbuilder_append_char(t_stringbuilder *builder,
						const char c);
bool				stringbuilder_trim_buffer(t_stringbuilder *builder);

/* ------------------------------- stringbuilder_2.c ----------------------- */
char				*stringbuilder_return_buffer(t_stringbuilder *builder);
int					stringbuilder_return_read_head(t_stringbuilder *builder);
int					stringbuilder_return_write_head(t_stringbuilder *builder);
char				*stringbuilder_trim_and_return_buffer(
						t_stringbuilder *builder);

/* ------------------------------- reader.c -------------------------------- */
void				reader_init(t_reader *reader, char *string);
char				*reader_get_current(t_reader *reader);
void				reader_increment(t_reader *reader);
void				reader_decrement(t_reader *reader);
void				reader_increment_stepsize(t_reader *reader,
						unsigned int steps);
void				reader_decrement_stepsize(t_reader *reader,
						unsigned int steps);
char				reader_peek_char(t_reader *reader);
char				reader_read_char(t_reader *reader);
bool				reader_peek_string(t_reader *reader, const char *string);
unsigned int		reader_skip_whitespace(t_reader *reader);
bool				reader_detect_empty_line(t_reader *reader);
char				*reader_read_to_newline(t_reader *reader);
void				reader_skip_newline(t_reader *reader);
bool				reader_has_content(t_reader *reader);
bool				reader_read_unsigned_integer(t_reader *reader,
						unsigned int *target);

/* ------------------------------- temp_buffer.c --------------------------- */
void				temp_buffer_init(t_temp_buffer *temp);

/* ------------------------------- config.c -------------------------------- */
void				config_parse(t_config_file *config, t_map *map);

/* ------------------------------- config_header_parse.c ------------------- */
unsigned int		config_header_parse(t_config_file *config, t_map *map,
						t_reader *reader);

/* ------------------------------- config_header_validate.c ---------------- */
void				config_header_validate(t_config_file *config, t_map *map,
						int *errorcode);

/* ------------------------------- config_map_parse_1.c -------------------- */
void				config_map_parse(t_config_file *config, t_map *map,
						t_reader *reader, unsigned int spaces);

/* ------------------------------- config_map_parse_2.c -------------------- */
void				config_map_parse_set_null(t_map *map, unsigned int o,
						unsigned int *p);
void				config_map_parse_set_char(t_map *map, unsigned int o,
						unsigned int *p, char c);
void				config_map_parse_set_width(t_map *map, unsigned int width);

/* ------------------------------- config_map_validate_1.c ----------------- */
void				config_map_validate(t_config_file *config, t_map *map,
						int *errorcode);

/* ------------------------------- config_map_validate_2.c ----------------- */
bool				config_map_validate_char(t_config_file *config, t_map *map,
						unsigned int x, unsigned int y);

/* ------------------------------- config_map_validate_3.c ----------------- */
bool				config_map_validate_char_walls(t_map *map,
						char potential_wall);
bool				config_map_validate_char_playerpositions(t_map *map,
						char position);
bool				config_map_validate_char_space_neighbours(t_map *map,
						char neighbour);
bool				config_map_validate_char_player_neighbours(t_map *map,
						unsigned int x, unsigned int y);

/* ------------------------------- validation_utils.c ---------------------- */
bool				validation_typecheck_cub(const char *path);
bool				validation_typecheck_xpm(const char *path);
bool				validation_check_boolian(bool boolian, int *errorcode,
						int code);
unsigned int		calculate_rgb_value(unsigned int *rgb, unsigned int r,
						unsigned int g, unsigned int b);

/* ------------------------------- player.c -------------------------------- */
float				player_calculate_angle(char direction);

#endif
