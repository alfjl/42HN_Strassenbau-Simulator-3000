#include "cub3d.h"
#include <errno.h>

static char	*static_exit_get_error_message(int errorcode)
{
	char	*errormessage[ERRORS];

	errormessage[MLX] = "Mlx init failed!";
	errormessage[MLX_WIN] = "Mlx new window failed!";
	errormessage[MLX_IMAGE] = "Mlx new image failed!";
	errormessage[ARGUMENT_NR] = "Incorrect number of arguments: only 1 allowed";
	errormessage[WRONG_FILETYPE] = "Wrong filetype";
	errormessage[FILE_NOT_OPEN] = "No such file or directory";
	errormessage[PROBLEM_READING_CONFIG] = "Problem reading from config file";
	errormessage[PROBLEM_READING_TEXTURE] = "Problem reading from texture file";
	errormessage[WRONG_CONFIG_ARGS] = "Config file contains wrong arguments";
	errormessage[WRONG_RGB_VALUES] = "RGB value not correct";
	errormessage[INVALID_MAP] = "No valid map found";
	return (errormessage[errorcode]);
}

int	exit_end_program_success(void)
{	
	free_all();
	exit(EXIT_SUCCESS);
}

int	exit_end_program_error(int errorcode)
{	
	free_all();
	if (errorcode == SYSTEM)
		ft_printf_stderr("Error\n%s\n", strerror(errno));
	else
		ft_printf_stderr("Error\n%s\n", static_exit_get_error_message(errorcode));
	exit(EXIT_FAILURE);
}
