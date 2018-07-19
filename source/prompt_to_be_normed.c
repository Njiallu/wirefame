#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <curses.h>
#include <readline/readline.h>
#include <readline/history.h>

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

t_command_head		parse_command_head(char *str, char **end)
{
	t_command_head	head;

	head = (t_command_head){NULL, 0};
	while (*str)
	{
		if (!isspace(*str))
		{
			// Header found
			head.str = str;
			while (*str && !isspace(*str++))
				++head.length;
			break ;
		}
		++str;
	}
	*end = str;
	return (head);
}

t_command_arg		*create_command_arg(char *str, uint32_t length)
{
	t_command_arg	*arg;

	if (!(arg = (t_command_arg*)malloc(sizeof(t_command_arg))))
		return (arg);
	*arg = (t_command_arg){str, length, NULL};
	return (arg);
}

t_command_arg		*parse_command_arg(char *str, char **end)
{
	t_command_arg	*arg;
	t_command_arg	*tmp_arg;
	t_command_arg	*first_arg;

	first_arg = NULL;
	while (*str)
	{
		if (!isspace(*str))
		{
			// Arg found
			tmp_arg = create_command_arg(str, 0);
			while (*str && !isspace(*str++))
				++tmp_arg->length;
			if (!first_arg)
			{
				first_arg = tmp_arg;
				arg = first_arg;
			}
			else
			{
				arg->next = tmp_arg;
				arg = tmp_arg;
			}
		}
		else
			++str;
	}
	return (first_arg);
}

t_command			parse_command(char *str)
{
	t_command		cmd = (t_command){str, (t_command_head){NULL, 0}, NULL};

	// Getting Header
	cmd.head = parse_command_head(str, &str);
	// Getting arguments
	cmd.args = parse_command_arg(str, &str);
	return (cmd);
}

void				print_command(t_command cmd)
{
	t_command_arg	*arg;

	printf("original cmd: \'%s\'\ncommand name: %.*s\n % 4d args\n", cmd.original_str, cmd.head.length, cmd.head.str, cmd.arg_number);
	arg = cmd.args;
	while (arg)
	{
		printf(" < \'%-10.*s\' length: %-5u >\n", arg->length, arg->str, arg->length);
		arg = arg->next;
	}
}

int					main (void) {

	// Display the prompt and read the input
	char *input = readline("Command tester v0.75.1");

	// Ingest and parse the input
	t_command cmd = parse_command(input);

	// Use the input to make a command
	print_command(cmd);
	return 0;
}
