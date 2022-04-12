# include "cub3d.h"
#include <errno.h>

static char	*get_error_message(int errorcode)
{
	char	*errormessage[ERRORS];

	errormessage[CUSTOM] = "Too many arguments!";
	return (errormessage[errorcode]);
}

static void free_all(void)
{
	return ;
}

int	exit_program(int errorcode)
{	
	free_all();
	if (errorcode == SUCCESS)
		exit(EXIT_SUCCESS);
	else if (errorcode == SYSTEM)
	{
		ft_printf_stderr("Error: %s\n", strerror(errno));
	}
	else
		ft_printf_stderr("Error: %s\n", get_error_message(errorcode));
	exit(EXIT_FAILURE);
}
