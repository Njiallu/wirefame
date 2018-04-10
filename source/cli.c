/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles </var/mail/mbeilles>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:21:55 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/10 23:05:05 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include "wireframe.h"
#include "libft.h"

static inline uint32_t			get_param_number(char *str)
{
	uint32_t				i;
	uint32_t				word;
	uint32_t				in_word;

	i = 0;
	word = 0;
	in_word = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) && !in_word)
		{
			in_word = 1;
			word++;
		}
		else
			in_word = 0;
		i++;
	}
	return (word);
}

static inline t_cli_param		get_param(char **str, int *found)
{
	t_cli_param					p;

	if (!*str)
		return (*found = 0, p);
	while(**str && ft_isspace(**str))
		++*str;
	p = (t_cli_param){*str, 0};
	while ((*str)[p.len] && !ft_isspace((*str)[p.len]))
		p.len++;
	*str += p.len;
	*found = 1;
	return (p);
}

static inline t_cli_command		parse_cli_command(char *str, uint32_t len)
{
	t_cli_command				cmd;
	t_cli_param					param;
	int32_t						found;
	uint32_t					i;

	cmd = (t_cli_command){str, (t_cli_param){NULL, 0}, NULL, 0};
	i = 0;
	cmd.command = get_param(&str, &found);
	cmd.param_number = get_param_number(str);
	if (!(cmd.param = (t_cli_param*)malloc(sizeof(t_cli_param) * cmd.param_number)))
		exit(EXIT_FAILURE);
	while ((param = get_param(&str, &found)), found && i < cmd.param_number)
		cmd.param[i++] = param;
	return (cmd);
}

t_cli_command					get_cli_command(void)
{
	char						*str;

	while (get_next_line(0, &str) <= 0);
	return (parse_cli_command(str, ft_strlen(str)));
}

void							print_cli_command(t_cli_command cmd)
{
	uint32_t				i;

	printf(STR_INF("Command issued > \'%.*s\' [%d]:"), cmd.command.len
								, cmd.command.param, cmd.param_number);
	i = ~0U;
	while(++i < cmd.param_number)
		printf(C_MGR" \'%.*s\'"C_NRM, cmd.param[i].len, cmd.param[i].param);
	printf("\n");
}

void							destroy_cli_command(t_cli_command cmd)
{
	free(cmd.str);
	free(cmd.param);
}

void							display_cli_prompt
