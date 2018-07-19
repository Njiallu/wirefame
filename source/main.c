/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles </var/mail/mbeilles>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:07:40 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/12 13:40:49 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <SDL.h>
#include "wireframe.h"
#include "cli.h"
#include "libft.h"

void					leave(char *str, uint32_t exit_code)
{
	if (str)
		ft_putstr(str);
	ft_putstr(STR_INF("Exiting "NAME".\n"));
	exit(exit_code);
}

int						main(int c, char **v)
{
	SDL_Window			*window;
	SDL_Event			e;
	t_cli				cli;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		leave(STR_ERR(""), EXIT_FAILURE);

	if ((window = SDL_CreateWindow(
					"An SDL2 window",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					1920,
					1080,
					SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
					| SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
					)) == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	while (42)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return (0);
			if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
				printf(STR_INF("Window is resized: %d %d\n"), e.window.data1, e.window.data2);
		}
		if ((cli = get_cli()).command.str)
		{
			print_cli_command(cli.command);
			destroy_cli_command(cli.command);
			print_cli_prompt(cli);
		}
	}
	SDL_Delay(3000);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return (0);
}
