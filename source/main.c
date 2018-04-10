/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles </var/mail/mbeilles>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:07:40 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/10 15:44:29 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <SDL.h>
#include "wireframe.h"
#include "cli.h"

int						main(int c, char **v)
{
	SDL_Window			*window;
	SDL_Event			e;
	t_cli_command		cmd;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
			"An SDL2 window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1920,
			1080,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
			SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS
			);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return (0);
		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
			printf("Window is resized: %d %d\n", e.window.data1, e.window.data2);
		if ((cmd = get_cli_command()).str)
		{
			print_cli_command(cmd);
			destroy_cli_command(cmd);
		}
	}

	SDL_Delay(3000);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return (0);
}
