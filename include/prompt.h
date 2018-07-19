/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles </var/mail/mbeilles>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:25:53 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/10 15:39:51 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include <stdint.h>

typedef struct		s_cli_param
{
	char			*param;
	uint32_t		len;
}					t_cli_param;

typedef struct		s_cli_command
{
	char			*str;
	t_cli_param		command;
	t_cli_param		*param;
	uint32_t		param_number;
}					t_cli_command;

t_cli_command		get_cli_command();
void				destroy_cli_command();

void				print_cli_command(t_cli_command cmd);

#endif
