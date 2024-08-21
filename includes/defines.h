/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:04:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/21 18:14:09 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
 #define DEFINES_H

// define colors
# define RED "\033[31m"
# define RESET "\033[39m"

// Std error MSG
# define ERROR_MSG "\033[31mError\n\033[39m"

// Function return in case fail
# define FAIL -1

// program defines
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPPED 0.05
#define ROT_SPEED 0.03
#define X 0
#define Y 1
#define CURRENT 0
#define OLD_TIME 1

#endif