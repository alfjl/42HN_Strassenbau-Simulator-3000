/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:55:56 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:55:57 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGBUILDER_H
# define STRINGBUILDER_H
/* ------------------------------- INCLUDES -------------------------------- */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

/* ------------------------------- DEFINES --------------------------------- */
# define BUFFER_SIZE_BUILDER 20480

typedef struct s_stringbuilder
{
	char			*buffer;
	int				read_head;
	int				write_head;
}			t_stringbuilder;

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

#endif
