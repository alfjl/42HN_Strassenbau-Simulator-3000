#include "cub3d.h"
#include <errno.h>

static char	*static_exit_get_error_message(int errorcode)
{
	char	*errormessage[ERRORS];

	errormessage[MLX] = "Mlx init failed!";
	errormessage[MLX_WIN] = "Mlx new window failed!";
	errormessage[MLX_IMAGE] = "Mlx new image failed!";
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
