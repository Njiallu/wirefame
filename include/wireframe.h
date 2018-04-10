/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles </var/mail/mbeilles>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:18:44 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/10 16:40:07 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIREFRAME_H
# define WIREFRAME_H

# include <SDL.h>

/*
** =============================================================================
** 							Printing strings
** =============================================================================
** =========================== Variables =======================================
*/

# define	NAME		"Wireframe"
# define	NICK		"Wifm"

/*
** ============================= Colors ========================================
*/

# define	C_RED		"\033[38;2;193;68;40m"
# define	C_ORA		"\033[38;2;193;101;40m"
# define	C_YEL		"\033[38;2;204;183;46m"
# define	C_GRN		"\033[38;2;100;193;50m"
# define	C_TEA		"\033[38;2;50;193;111m"
# define	C_CYA		"\033[38;2;50;193;190m"
# define	C_BLU		"\033[38;2;50;140;193m"
# define	C_PUR		"\033[38;2;135;50;193m"
# define	C_PIK		"\033[38;2;193;50;133m"

# define	C_WHI		"\033[38;2;220;220;220m"
# define	C_LGR		"\033[38;2;190;190;190m"
# define	C_MGR		"\033[38;2;150;150;150m"
# define	C_DGR		"\033[38;2;90;90;90m"
# define	C_BLA		"\033[38;2;40;40;40m"

# define	C_PRJ		C_GRN
# define	C_NRM		"\033[0m"

/*
** ============================== Utils ========================================
*/

# define	HEADER		C_DGR "[" C_PRJ NAME C_DGR "] " C_NRM
# define	STR_ERR_HD	HEADER C_DGR "[" C_PUR "x" C_PUR "] " C_NRM
# define	STR_WRN_HD	HEADER C_DGR "[" C_RED "!" C_RED "] " C_NRM
# define	STR_INF_HD	HEADER C_ORA "[" C_YEL "i" C_ORA "] " C_NRM

# define	STR_ERR(s)	STR_ERR_HD C_WHI s C_NRM
# define	STR_WRN(s)	STR_WRN_HD C_LGR s C_NRM
# define	STR_INF(s)	STR_INF_HD C_MGR s C_NRM

#endif
