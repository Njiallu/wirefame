#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <curses.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "prompt.h"

/*
** Parses only the head of the command (not the first argument)
*/
t_command_head		parse_command_head(char *str, char **end)
{
	t_command_head	head;

	head = (t_command_head){NULL, 0};
	while (*str)
	{
		if (!isspace(*str))
		{
			head.str = str;
			while (*str && !isspace(*str++))
				++head.length;
			break ;
		}
		str++;
	}
	*end = str;
	return (head);
}

/*
** Creates a new arg node.
*/
t_command_arg		*create_command_arg(char *str, uint32_t length)
{
	t_command_arg	*arg;

	if (!(arg = (t_command_arg*)malloc(sizeof(t_command_arg))))
		return (arg);
	*arg = (t_command_arg){str, length, NULL};
	return (arg);
}

/*
** Parse all arguments from the string.
** 		Str should not be null. You are trying to parse a string.
** 		When it encounter something that is not a separator, it creates an
** 		argument and place the start of it to the actual position on str.
** 		Then procedes to count the number of char. And returns the start of
** 		the arg linked list.
*/
t_command_arg		*parse_command_arg(char *str, char **end, int *nbr)
{
	t_command_arg	*tmp_arg;
	t_command_arg	*last_arg;
	t_command_arg	*first_arg;

	first_arg = NULL;
	while (*str)
		if (!isspace(*str))
		{
			tmp_arg = create_command_arg(str, 0);
			while (*str && !isspace(*str++))
				++tmp_arg->length;
			if (!first_arg && ++(*nbr))
			{
				first_arg = tmp_arg;
				last_arg = first_arg;
			}
			else
			{
				last_arg->next = tmp_arg;
				last_arg = tmp_arg;
			}
		}
		else
			str++;
	return (first_arg);
}

/*
** Get command head and arguments to assemble the command.
** 		Head cannot be null by definition but it can be empty so it can be
** 		handeled by the state machine without checking for special cases
** 		appart for emptyness, which is fair in my opinion.
**
** 	Command
** 		Head -> t_command_head is empty (typically length 0) or have string.
** 		Args -> t_command_arg  is a null terminated linked list.
** 		Str  -> string used to generate and is pointed by head and args.
** 		Nbr  -> number of args in the command;
*/
t_command			parse_command(char *str)
{
	t_command		cmd = (t_command){str, (t_command_head){NULL, 0}, NULL, 0};

	// Getting Header
	cmd.head = parse_command_head(str, &str);
	// Getting arguments
	cmd.args = parse_command_arg(str, &str, &cmd.arg_number);
	return (cmd);
}

/*
** Print command data
*/
void				print_command(t_command cmd)
{
	t_command_arg	*arg;

	printf("original cmd: \'%s\'\ncommand name: %.*s\n % 4d args\n"
			, cmd.original_str, cmd.head.length, cmd.head.str, cmd.arg_number);
	arg = cmd.args;
	while (arg)
	{
		printf(" < \'%-10.*s\' length: %-5u >\n", arg->length, arg->str
				, arg->length);
		arg = arg->next;
	}
}

/*
** Wow such comments needed. Nice.
*/
int					main (void) {

	char			*input;
	t_command		cmd;

	input = readline("Command tester v0.75.1");
	cmd = parse_command(input);
	print_command(cmd);
	return 0;
}
