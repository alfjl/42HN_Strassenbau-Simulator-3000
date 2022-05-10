/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:55:53 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:55:54 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
/* ------------------------------- INCLUDES -------------------------------- */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include "stringbuilder.h"

/* ------------------------------- DEFINES --------------------------------- */
typedef struct s_reader
{
	char			*string;
	char			*string_end;
	char			*current;
}			t_reader;

/* ------------------------------- reader_1.c ------------------------------ */
void				reader_init(t_reader *reader, char *string);
char				*reader_get_current(t_reader *reader);
void				reader_increment(t_reader *reader);
char				*reader_get_current(t_reader *reader);
void				reader_decrement(t_reader *reader);

/* ------------------------------- reader_2.c ------------------------------ */
void				reader_increment_stepsize(t_reader *reader,
						unsigned int steps);
void				reader_decrement_stepsize(t_reader *reader,
						unsigned int steps);
char				reader_peek_char(t_reader *reader);
char				reader_read_char(t_reader *reader);
bool				reader_peek_string(t_reader *reader, const char *string);

/* ------------------------------- reader_3.c ------------------------------ */
unsigned int		reader_skip_whitespace(t_reader *reader);
bool				reader_detect_empty_line(t_reader *reader);
char				*reader_read_to_newline(t_reader *reader);
void				reader_skip_rest_of_line(t_reader *reader);
void				reader_skip_newline(t_reader *reader);

/* ------------------------------- reader_4.c ------------------------------ */
bool				reader_has_content(t_reader *reader);
bool				reader_read_unsigned_integer(t_reader *reader,
						unsigned int *target);

#endif
