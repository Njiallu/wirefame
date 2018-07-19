/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles </var/mail/mbeilles>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:25:53 by mbeilles          #+#    #+#             */
/*   Updated: 2018/07/19 09:18:01 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include <stdint.h>
# include <stdlib.h>

typedef struct				s_command_head {
	char					*str;
	uint32_t				length;
}							t_command_head;

typedef struct				s_command_arg {
	char					*str;
	uint32_t				length;
	struct s_command_arg	*next;
}							t_command_arg;

typedef struct				s_command {
	char					*original_str;
	t_command_head			head;
	t_command_arg			*args;
	uint32_t				arg_number;
}							t_command;

/*
** Usage of this short lib:
**
**	// Display the prompt and read the input
**	char *input = readline("Command tester v0.75.1");
**
**	// Ingest and parse the input
**	t_command cmd = parse_command(input);
**
**	// Use the input to print the command debug
**	print_command(cmd);
**
*/

t_command_arg		*create_command_arg(char *str, uint32_t length);
t_command_arg		*parse_command_arg(char *str, char **end, int *nbr);
t_command_head		parse_command_head(char *str, char **end);
t_command			parse_command(char *str);
void				print_command(t_command cmd);

#endif
