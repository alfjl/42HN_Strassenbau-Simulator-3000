#include "cub3d.h"
#include <errno.h>

static char	*static_get_error_message(int errorcode)
{
	char	*errormessage[ERRORS];

	errormessage[MLX] = "Mlx init failed!";
	errormessage[MLX_WIN] = "Mlx new window failed!";
	errormessage[MLX_IMAGE] = "Mlx new image failed!";
	return (errormessage[errorcode]);
}

static void	static_free_all(void)
{
	return ;
}

int	exit_program(int errorcode)
{	
	static_free_all();
	if (errorcode == SUCCESS)
		exit(EXIT_SUCCESS);
	else if (errorcode == SYSTEM)
		ft_printf_stderr("Error\n%s\n", strerror(errno));
	else
		ft_printf_stderr("Error\n%s\n", static_get_error_message(errorcode));
	exit(EXIT_FAILURE);
}
