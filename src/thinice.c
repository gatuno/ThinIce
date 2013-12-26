/*
 * thinice.c
 * This file is part of Thin Ice
 *
 * Copyright (C) 2013 - Félix Arreola Rodríguez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ----------------
 * LEGAL NOTICE
 * ----------------
 *
 * This game is NOT related to Club Penguin in any way. Also,
 * this game is not intended to infringe copyrights, the graphics and
 * sounds used are Copyright of Disney.
 *
 * The new SDL code is written by Gatuno, and is released under
 * the term of the GNU General Public License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>

#include "config.h"

#include "mapa1.h"
#include "mapa2.h"
#include "mapa3.h"
#include "mapa4.h"
#include "mapa5.h"
#include "mapa6.h"
#include "mapa7.h"
#include "mapa8.h"
#include "mapa9.h"
#include "mapa10.h"
#include "mapa11.h"
#include "mapa12.h"
#include "mapa13.h"
#include "mapa14.h"
#include "mapa15.h"
#include "mapa16.h"
#include "mapa17.h"
#include "mapa18.h"
#include "mapa19.h"

#define FPS (1000/18)

#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))
#define RANDOM(x) ((int) (x ## .0 * rand () / (RAND_MAX + 1.0)))

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#define TILE_HEIGHT 24
#define TILE_WIDTH 24

#define MAP_X 144
#define MAP_Y 48

/* Enumerar las imágenes */
enum {
	IMG_ARCADE,
	
	IMG_DOWN_1,
	IMG_DOWN_2,
	IMG_DOWN_3,
	
	IMG_LEFT_1,
	IMG_LEFT_2,
	IMG_LEFT_3,
	
	IMG_RIGHT_1,
	IMG_RIGHT_2,
	IMG_RIGHT_3,
	
	IMG_UP_1,
	IMG_UP_2,
	IMG_UP_3,
	
	NUM_IMAGES
};

/* Enumerar cada uno de los Tiles */
enum {
	TILE_PORTAL_1,
	TILE_PORTAL_2,
	TILE_PORTAL_3,
	TILE_PORTAL_4,
	TILE_PORTAL_5,
	TILE_PORTAL_6,
	TILE_PORTAL_7,
	TILE_PORTAL_8,
	
	TILE_KEY_1,
	TILE_KEY_2,
	TILE_KEY_3,
	TILE_KEY_4,
	TILE_KEY_5,
	TILE_KEY_6,
	TILE_KEY_7,
	TILE_KEY_8,
	TILE_KEY_9,
	TILE_KEY_10,
	TILE_KEY_11,
	TILE_KEY_12,
	TILE_KEY_13,
	TILE_KEY_14,
	TILE_KEY_15,
	TILE_KEY_16,
	
	TILE_KEY_B_1,
	TILE_KEY_B_2,
	TILE_KEY_B_3,
	TILE_KEY_B_4,
	TILE_KEY_B_5,
	TILE_KEY_B_6,
	TILE_KEY_B_7,
	TILE_KEY_B_8,
	TILE_KEY_B_9,
	TILE_KEY_B_10,
	TILE_KEY_B_11,
	TILE_KEY_B_12,
	TILE_KEY_B_13,
	TILE_KEY_B_14,
	TILE_KEY_B_15,
	TILE_KEY_B_16,
	
	TILE_KEY_C_1,
	TILE_KEY_C_2,
	TILE_KEY_C_3,
	TILE_KEY_C_4,
	TILE_KEY_C_5,
	TILE_KEY_C_6,
	TILE_KEY_C_7,
	TILE_KEY_C_8,
	TILE_KEY_C_9,
	TILE_KEY_C_10,
	TILE_KEY_C_11,
	TILE_KEY_C_12,
	TILE_KEY_C_13,
	TILE_KEY_C_14,
	TILE_KEY_C_15,
	TILE_KEY_C_16,
	
	TILE_BAG,
	TILE_GOAL,
	TILE_EMPTY,
	TILE_ICE,
	TILE_BOXSPACE,
	TILE_DOBLE,
	TILE_PORTAL_EMPTY,
	TILE_LOCK,
	
	TILE_SWITCH_A,
	TILE_SWITCH_B,
	TILE_WALL,
	TILE_BLOCK,
	
	TILE_LOSE_1,
	TILE_LOSE_2,
	TILE_LOSE_3,
	TILE_LOSE_4,
	TILE_LOSE_5,
	TILE_LOSE_6,
	TILE_LOSE_7,
	TILE_LOSE_8,
	TILE_LOSE_9,
	TILE_LOSE_10,
	TILE_LOSE_11,
	TILE_LOSE_12,
	TILE_LOSE_13,
	TILE_LOSE_14,
	TILE_LOSE_15,
	TILE_LOSE_16,
	TILE_LOSE_17,
	TILE_LOSE_18,
	TILE_LOSE_19,
	TILE_LOSE_20,
	
	TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3,
	TILE_BLACK_NORMAL_4,
	TILE_BLACK_NORMAL_5,
	TILE_BLACK_NORMAL_6,
	TILE_BLACK_NORMAL_7,
	
	TILE_BLACK_START_1,
	TILE_BLACK_START_2,
	TILE_BLACK_START_3,
	TILE_BLACK_START_4,
	TILE_BLACK_START_5,
	
	TILE_BLACK_OFF_1,
	TILE_BLACK_OFF_2,
	TILE_BLACK_OFF_3,
	TILE_BLACK_OFF_4,
	TILE_BLACK_OFF_5,
	TILE_BLACK_OFF_6,
	TILE_BLACK_OFF_7,
	TILE_BLACK_OFF_8,
	TILE_BLACK_OFF_9,
	TILE_BLACK_OFF_10,
	TILE_BLACK_OFF_11,
	TILE_BLACK_OFF_12,
	TILE_BLACK_OFF_13,
	TILE_BLACK_OFF_14,
	TILE_BLACK_OFF_15,
	TILE_BLACK_OFF_16,
	TILE_BLACK_OFF_17,
	TILE_BLACK_OFF_18,
	TILE_BLACK_OFF_19,
	TILE_BLACK_OFF_20,
	TILE_BLACK_OFF_21,
	TILE_BLACK_OFF_22,
	TILE_BLACK_OFF_23,
	TILE_BLACK_OFF_24,
	TILE_BLACK_OFF_25,
	TILE_BLACK_OFF_26,
	TILE_BLACK_OFF_27,
	TILE_BLACK_OFF_28,
	
	TILE_MELT_1,
	TILE_MELT_2,
	TILE_MELT_3,
	TILE_MELT_4,
	TILE_MELT_5,
	TILE_MELT_6,
	TILE_MELT_7,
	TILE_MELT_8,
	TILE_MELT_9,
	TILE_MELT_10,
	TILE_MELT_11,
	TILE_MELT_12,
	TILE_MELT_13,
	TILE_MELT_14,
	TILE_MELT_15,
	TILE_MELT_16,
	TILE_MELT_17,
	TILE_MELT_18,
	TILE_MELT_19,
	TILE_MELT_20,
	TILE_MELT_21,
	TILE_MELT_22,
	TILE_MELT_23,
	TILE_MELT_24,
	TILE_MELT_25,
	TILE_MELT_26,
	TILE_MELT_27,
	TILE_MELT_28,
	TILE_MELT_29,
	TILE_MELT_30,
	TILE_MELT_31,
	TILE_MELT_32,
	TILE_MELT_33,
	TILE_MELT_34,
	TILE_MELT_35,
	TILE_MELT_36,
	TILE_MELT_37,
	TILE_MELT_38,
	TILE_MELT_39,
	TILE_MELT_40,
	TILE_MELT_41,
	TILE_MELT_42,
	TILE_MELT_43,
	TILE_MELT_44,
	TILE_MELT_45
};

const char *images_names[NUM_IMAGES] = {
	GAMEDATA_DIR "images/arcade.png",
	GAMEDATA_DIR "images/down-1.png",
	GAMEDATA_DIR "images/down-2.png",
	GAMEDATA_DIR "images/down-3.png",
	GAMEDATA_DIR "images/left-1.png",
	GAMEDATA_DIR "images/left-2.png",
	GAMEDATA_DIR "images/left-3.png",
	GAMEDATA_DIR "images/right-1.png",
	GAMEDATA_DIR "images/right-2.png",
	GAMEDATA_DIR "images/right-3.png",
	GAMEDATA_DIR "images/up-1.png",
	GAMEDATA_DIR "images/up-2.png",
	GAMEDATA_DIR "images/up-3.png"
};

#define IMG_TILE_NAME GAMEDATA_DIR "images/tiles.png"

static int tiles_frames [] = {
	1, /* 0 => 1 Portal normal */
	2, 3, /* 1 => 2, 2 => 3 */
	4, 5, /* 3 => 4, 4 => 5 */
	6, 7, /* 5 => 6, 6 => 7 */
	8, 9, /* 7 => 8, 8 => 9 */
	10, 11, 12, /* 9 => 10, 10 => 11, 11 => 12 */
	13, 14, 15, /* 12 => 13, 13 => 14, 14 => 15 */
	16, 17, 18, /* 15 => 16, 16 => 17, 17 => 18 */
	19, 20, 1,  /* 18 => 19, 19 => 20, 20 => 1 */
	
	22, /* 21 => 22 Portal Rapido */
	23, /* 22 => 23 */
	24, /* 23 => 24 */
	25, /* 24 => 25 */
	22, /* 25 => 22 */
	
	27, /* 26 => 27 Llave */
	28, 29, /* 27 => 28, 28 => 29 */
	30, 31, /* 29 => 30, 30 => 31 */
	32, 33, /* 31 => 32, 32 => 33 */
	34, 35, /* 33 => 34, 34 => 35 */
	36, 37, /* 35 => 36, 36 => 37 */
	38, 39, /* 37 => 38, 38 => 39 */
	40, 41, /* 39 => 40, 40 => 41 */
	42, 43, /* 41 => 42, 42 => 43 */
	44, 45, /* 43 => 44, 44 => 45 */
	46, 47, /* 45 => 46, 46 => 47 */
	48, 49, /* 47 => 48, 48 => 49 */
	50, 51, /* 49 => 50, 50 => 51 */
	52, 53, /* 51 => 52, 52 => 53 */
	54, 55, /* 53 => 54, 54 => 55 */
	56, 57, /* 55 => 56, 56 => 57 */
	58, 27, /* 57 => 58, 58 => 27 */
	
	59, /* 59 => 59, Goal */
	60, /* 60 => 60, Vacio */
	61, /* 61 => 61, Hielo */
	62, /* 62 => 62, Espacio para la caja */
	63, /* 63 => 63, Hielo doble */
	64, /* 64 => 64, Portal inactivo */
	65, /* 65 => 65, Candado */
	66, /* 66 => 66, Boton 1 */
	67, /* 67 => 67, Boton utilizado */
	68, /* 68 => 68, Muro */
	69, /* 69 => 69, Bloque */
	70, /* 70 => 70, Bolsa de dinero */
	
	/* Hielo derriendose, Agua moviendo */
	72, 73, 74, 75,
	76, 77, 78, 79, 80,
	81, 82, 83, 84, 85,
	86, 87, 88, 89, 90,
	91, 92, 93, 94, 95,
	96, 97, 98, 99, 100,
	101, 102, 103, 104, 105,
	106, 107, 108, 109, 110,
	111, 112, 113, 114, 115,
	116, 78,
	
	/* Torbellino */
	118, 119, 120, 121, 122,
	123, 124, 125, 126, 127, 128, 129, 130,
	131, 132, 133, 134, 135, 136, 137, 119,
	
	/* Llave 2 */
	139,
	140, 141, 142, 143,
	144, 145, 146, 147,
	148, 149, 150, 151,
	152, 153, 154, 155,
	156, 157, 158, 159,
	160, 161, 162, 163,
	164, 165, 166, 167,
	168, 169, 170, 139,
	
	/* Llave 3 */
	172,
	173, 174, 175, 176,
	177, 178, 179, 180,
	181, 182, 183, 184,
	185, 186, 187, 188,
	189, 190, 191, 192,
	193, 194, 195, 196,
	197, 198, 199, 200,
	201, 202, 203, 172
};


static int tiles_outputs [] = {
	TILE_PORTAL_1,
	TILE_PORTAL_1, TILE_PORTAL_1,
	TILE_PORTAL_2, TILE_PORTAL_2,
	TILE_PORTAL_3, TILE_PORTAL_3,
	TILE_PORTAL_4, TILE_PORTAL_4,
	TILE_PORTAL_1, TILE_PORTAL_1, TILE_PORTAL_1,
	TILE_PORTAL_2, TILE_PORTAL_2, TILE_PORTAL_2,
	TILE_PORTAL_3, TILE_PORTAL_3, TILE_PORTAL_3,
	TILE_PORTAL_4, TILE_PORTAL_4, TILE_PORTAL_4,
	
	TILE_PORTAL_5,
	TILE_PORTAL_5,
	TILE_PORTAL_6,
	TILE_PORTAL_7,
	TILE_PORTAL_8,
	
	TILE_KEY_1,
	TILE_KEY_1, TILE_KEY_1,
	TILE_KEY_2, TILE_KEY_2,
	TILE_KEY_3, TILE_KEY_3,
	TILE_KEY_4, TILE_KEY_4,
	TILE_KEY_5, TILE_KEY_5,
	TILE_KEY_6, TILE_KEY_6,
	TILE_KEY_7, TILE_KEY_7,
	TILE_KEY_8, TILE_KEY_8,
	TILE_KEY_9, TILE_KEY_9,
	TILE_KEY_10, TILE_KEY_10,
	TILE_KEY_11, TILE_KEY_11,
	TILE_KEY_12, TILE_KEY_12,
	TILE_KEY_13, TILE_KEY_13,
	TILE_KEY_14, TILE_KEY_14,
	TILE_KEY_15, TILE_KEY_15,
	TILE_KEY_16, TILE_KEY_16,
	
	TILE_GOAL,
	TILE_EMPTY,
	TILE_ICE,
	TILE_BOXSPACE,
	TILE_DOBLE,
	TILE_PORTAL_EMPTY,
	TILE_LOCK,
	TILE_SWITCH_A,
	TILE_SWITCH_B,
	TILE_WALL,
	TILE_BLOCK,
	TILE_BAG,
	
	TILE_MELT_1,
	TILE_MELT_1, TILE_MELT_2, TILE_MELT_3, TILE_MELT_4, TILE_MELT_5,
	TILE_MELT_6, TILE_MELT_7, TILE_MELT_8, TILE_MELT_9, TILE_MELT_10,
	TILE_MELT_11, TILE_MELT_12, TILE_MELT_13, TILE_MELT_14, TILE_MELT_15,
	TILE_MELT_16, TILE_MELT_17, TILE_MELT_18, TILE_MELT_19, TILE_MELT_20,
	TILE_MELT_21, TILE_MELT_22, TILE_MELT_23, TILE_MELT_24, TILE_MELT_25,
	TILE_MELT_26, TILE_MELT_27, TILE_MELT_28, TILE_MELT_29, TILE_MELT_30,
	TILE_MELT_31, TILE_MELT_32, TILE_MELT_33, TILE_MELT_34, TILE_MELT_35,
	TILE_MELT_36, TILE_MELT_37, TILE_MELT_38, TILE_MELT_39, TILE_MELT_40,
	TILE_MELT_41, TILE_MELT_42, TILE_MELT_43, TILE_MELT_44, TILE_MELT_45,
	
	TILE_LOSE_1,
	TILE_LOSE_1, TILE_LOSE_2, TILE_LOSE_3, TILE_LOSE_4,
	TILE_LOSE_5, TILE_LOSE_6, TILE_LOSE_7, TILE_LOSE_8,
	TILE_LOSE_9, TILE_LOSE_10, TILE_LOSE_11, TILE_LOSE_12,
	TILE_LOSE_13, TILE_LOSE_14, TILE_LOSE_15, TILE_LOSE_16,
	TILE_LOSE_17, TILE_LOSE_18, TILE_LOSE_19, TILE_LOSE_20,
	
	TILE_KEY_B_1,
	TILE_KEY_B_1, TILE_KEY_B_1,
	TILE_KEY_B_2, TILE_KEY_B_2,
	TILE_KEY_B_3, TILE_KEY_B_3,
	TILE_KEY_B_4, TILE_KEY_B_4,
	TILE_KEY_B_5, TILE_KEY_B_5,
	TILE_KEY_B_6, TILE_KEY_B_6,
	TILE_KEY_B_7, TILE_KEY_B_7,
	TILE_KEY_B_8, TILE_KEY_B_8,
	TILE_KEY_B_9, TILE_KEY_B_9,
	TILE_KEY_B_10, TILE_KEY_B_10,
	TILE_KEY_B_11, TILE_KEY_B_11,
	TILE_KEY_B_12, TILE_KEY_B_12,
	TILE_KEY_B_13, TILE_KEY_B_13,
	TILE_KEY_B_14, TILE_KEY_B_14,
	TILE_KEY_B_15, TILE_KEY_B_15,
	TILE_KEY_B_16, TILE_KEY_B_16,
	
	TILE_KEY_C_1,
	TILE_KEY_C_1, TILE_KEY_C_1,
	TILE_KEY_C_2, TILE_KEY_C_2,
	TILE_KEY_C_3, TILE_KEY_C_3,
	TILE_KEY_C_4, TILE_KEY_C_4,
	TILE_KEY_C_5, TILE_KEY_C_5,
	TILE_KEY_C_6, TILE_KEY_C_6,
	TILE_KEY_C_7, TILE_KEY_C_7,
	TILE_KEY_C_8, TILE_KEY_C_8,
	TILE_KEY_C_9, TILE_KEY_C_9,
	TILE_KEY_C_10, TILE_KEY_C_10,
	TILE_KEY_C_11, TILE_KEY_C_11,
	TILE_KEY_C_12, TILE_KEY_C_12,
	TILE_KEY_C_13, TILE_KEY_C_13,
	TILE_KEY_C_14, TILE_KEY_C_14,
	TILE_KEY_C_15, TILE_KEY_C_15,
	TILE_KEY_C_16, TILE_KEY_C_16
};

static int tiles_start [] = {
	-1,
	60,
	61,
	62,
	63,
	59,
	26,
	70,
	138,
	171,
	69,
	64,
	117,
	68,
	66,
	67,
	0,
	21,
	-1,
	-1,
	68,
	65,
	71
};

enum {
	PLAYER_NORMAL = 0,
	PLAYER_IGNITE,
	PLAYER_DROWN,
	NUM_PLAYER_STATES
};

static int player_frames [] = {
	1,    /* Jugador normal 0 => 1 */
	2, 3, /* 1 => 2, 2 => 3 */
	4, 5, /* 3 => 4, 4 => 5 */
	6, 7, /* 5 => 6, 6 => 7 */
	8, 9, /* 7 => 8, 8 => 9 */
	10, 11, /*  9 => 10, 10 => 11 */
	12, 13, /* 11 => 12, 12 => 13 */
	
	14, 15,
	16, 17,
	18, 19,
	20, 21,
	
	22, 23,
	24, 25,
	26, 27,
	
	28, 29,
	30, 31,
	32, 33,
	
	34, 35,
	36, 37,
	38, 39,
	
	40, 41,
	42, 43,
	44, 45,
	
	46, 47,
	48, 49,
	50,  1,
	
	52, /* Jugador prendiendo fuego 51 => 52 */
	53, 54, 55, 56,
	57, 58,
	59, 60,
	61, 62,
	63,  1,
	
	65,
	66, 67, 68, 69,
	70, 71, 72, 73,
	74, 75, 76, 77,
	78, 79, 80, 81,
	82, 83, 84, 85,
	86, 87, 88, 89,
	90, 91, 92, 92
};

static int player_outputs [] = {
	TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	
	TILE_BLACK_NORMAL_4, TILE_BLACK_NORMAL_4,
	TILE_BLACK_NORMAL_5, TILE_BLACK_NORMAL_5,
	TILE_BLACK_NORMAL_6, TILE_BLACK_NORMAL_6,
	TILE_BLACK_NORMAL_7, TILE_BLACK_NORMAL_7,
	
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	TILE_BLACK_NORMAL_1, TILE_BLACK_NORMAL_1,
	TILE_BLACK_NORMAL_2, TILE_BLACK_NORMAL_2,
	TILE_BLACK_NORMAL_3, TILE_BLACK_NORMAL_3,
	
	TILE_BLACK_START_1,
	TILE_BLACK_START_1, TILE_BLACK_START_1,
	TILE_BLACK_START_1, TILE_BLACK_START_1,
	TILE_BLACK_START_2, TILE_BLACK_START_2,
	TILE_BLACK_START_3, TILE_BLACK_START_3,
	TILE_BLACK_START_4, TILE_BLACK_START_4,
	TILE_BLACK_START_5, TILE_BLACK_START_5,
	
	TILE_BLACK_OFF_1,
	TILE_BLACK_OFF_1, TILE_BLACK_OFF_2, TILE_BLACK_OFF_3, TILE_BLACK_OFF_4,
	TILE_BLACK_OFF_5, TILE_BLACK_OFF_6, TILE_BLACK_OFF_7, TILE_BLACK_OFF_8,
	TILE_BLACK_OFF_9, TILE_BLACK_OFF_10, TILE_BLACK_OFF_11, TILE_BLACK_OFF_12,
	TILE_BLACK_OFF_13, TILE_BLACK_OFF_14, TILE_BLACK_OFF_15, TILE_BLACK_OFF_16,
	TILE_BLACK_OFF_17, TILE_BLACK_OFF_18, TILE_BLACK_OFF_19, TILE_BLACK_OFF_20,
	TILE_BLACK_OFF_21, TILE_BLACK_OFF_22, TILE_BLACK_OFF_23, TILE_BLACK_OFF_24,
	TILE_BLACK_OFF_25, TILE_BLACK_OFF_26, TILE_BLACK_OFF_27, TILE_BLACK_OFF_28
};

static int player_start [NUM_PLAYER_STATES] = {
	0,
	51,
	64
};

/* Codigos de salida */
enum {
	GAME_NONE = 0, /* No usado */
	GAME_CONTINUE,
	GAME_QUIT
};

enum {
	UP = 0x01,
	DOWN = 0x02,
	LEFT = 0x04,
	RIGHT = 0x08
};

/* Estructuras */
typedef struct {
	int x, y;
} Punto;

typedef struct {
	int x, y;
	int *frame;
} Warp;

/* Prototipos de función */
int game_loop (void);
void setup (void);
SDL_Surface * set_video_mode(unsigned);
void copy_tile (SDL_Rect *rect, int tile);
void load_map (int nivel, int (*mapa)[19], int (*frames)[19], int *goal, int r, int last_solved, Warp *warps, Punto *movible);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * image_tiles;
SDL_Surface * images [NUM_IMAGES];

int main (int argc, char *argv[]) {
	
	setup ();
	
	do {
		if (game_loop () == GAME_QUIT) break;
	} while (1 == 0);
	
	SDL_Quit ();
	return EXIT_SUCCESS;
}

int game_loop (void) {
	int done = 0, g, h;
	SDL_Event event;
	int last_key;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	
	int mapa[15][19];
	int frames[15][19];
	int nivel = 1;
	int puffle_frame;
	int tiles_flipped, save_tiles_flipped, snow_melted, save_snow_melted;
	int player_moving, slide_moving;
	int wall_up, wall_down, wall_left, wall_right;
	int movible_wall_up, movible_wall_down, movible_wall_left, movible_wall_right;
	int *tile_up, *tile_down, *tile_left, *tile_right, *tile_actual;
	int llave;
	int goal;
	int player_die;
	int random = RANDOM (2);
	int last_solved = FALSE;
	int warp_enable = FALSE;
	int warp_wall = FALSE;
	int slide_block;
	Punto player, save_player, next_player, movible, old_movible;
	Warp warps[2];
	
	puffle_frame = player_start[PLAYER_IGNITE];
	tiles_flipped = save_tiles_flipped = snow_melted = save_snow_melted = 0;
	player_moving = slide_moving = 0;
	wall_up = wall_down = wall_left = wall_right = FALSE;
	movible_wall_up = movible_wall_down = movible_wall_left = movible_wall_right = FALSE;
	slide_block = llave = 0;
	player_die = FALSE;
	last_key = 0;
	
	player.x = save_player.x = 14;
	player.y = save_player.y = 10;
	
	SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	
	SDL_BlitSurface (images[IMG_ARCADE], NULL, screen, NULL);
	load_map (nivel, mapa, frames, &goal, random, FALSE, warps, &movible);
	
	SDL_Flip (screen);
	do {
		last_time = SDL_GetTicks ();
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_DOWN) {
						last_key |= DOWN;
					} else if (event.key.keysym.sym == SDLK_UP) {
						last_key |= UP;
					} else if (event.key.keysym.sym == SDLK_LEFT) {
						last_key |= LEFT;
					} else if (event.key.keysym.sym == SDLK_RIGHT) {
						last_key |= RIGHT;
					}
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_DOWN) {
						last_key &= ~DOWN;
					} else if (event.key.keysym.sym == SDLK_UP) {
						last_key &= ~UP;
					} else if (event.key.keysym.sym == SDLK_LEFT) {
						last_key &= ~LEFT;
					} else if (event.key.keysym.sym == SDLK_RIGHT) {
						last_key &= ~RIGHT;
					}
					break;
			}
		}
		
		tile_actual = &mapa[player.y][player.x];
		tile_up = &mapa[player.y - 1][player.x];
		tile_down = &mapa[player.y + 1][player.x];
		tile_left = &mapa[player.y][player.x - 1];
		tile_right = &mapa[player.y][player.x + 1];
		
		if (*tile_up >= 20) {
			wall_up = TRUE;
			
			if (*tile_up == 21 && llave > 0) {
				/* Convertir la puerta a hielo */
				llave--;
				mapa[player.y - 1][player.x] = 2;
				frames[player.y - 1][player.x] = tiles_start[2];
				/* TODO: Reproducir sonido */
				wall_up = FALSE;
			}
		} else if (movible.y + 1 == player.y && movible.x == player.x && movible_wall_up) {
			wall_up = TRUE;
		} else {
			wall_up = FALSE;
		}
		
		if (*tile_down >= 20) {
			wall_down = TRUE;
			
			if (*tile_down == 21 && llave > 0) {
				/* Convertir la puerta a hielo */
				llave--;
				mapa[player.y + 1][player.x] = 2;
				frames[player.y + 1][player.x] = tiles_start[2];
				/* TODO: Reproducir sonido */
				wall_down = FALSE;
			}
		} else if (movible.y - 1 == player.y && movible.x == player.x && movible_wall_down) {
			wall_down = TRUE;
		} else {
			wall_down = FALSE;
		}
		
		if (*tile_left >= 20) {
			wall_left = TRUE;
			
			if (*tile_left == 21 && llave > 0) {
				/* Convertir la puerta a hielo */
				llave--;
				mapa[player.y][player.x - 1] = 2;
				frames[player.y][player.x - 1] = tiles_start[2];
				/* TODO: Reproducir sonido */
				wall_left = FALSE;
			}
		} else if (movible.y == player.y && movible.x + 1 == player.x && movible_wall_left) {
			wall_left = TRUE;
		} else {
			wall_left = FALSE;
		}
		
		if (*tile_right >= 20) {
			wall_right = TRUE;
			
			if (*tile_right == 21 && llave > 0) {
				/* Convertir la puerta a hielo */
				llave--;
				mapa[player.y][player.x + 1] = 2;
				frames[player.y][player.x + 1] = tiles_start[2];
				/* TODO: Reproducir sonido */
				wall_right = FALSE;
			}
		} else if (movible.y == player.y && movible.x - 1 == player.x && movible_wall_right) {
			wall_right = TRUE;
		} else {
			wall_right = FALSE;
		}
		
		if (warps[0].x == player.x && warps[0].y == player.y && warp_enable && player_moving == 0) {
			/* TODO: Reproducir sonido */
			wall_up = wall_down = wall_left = wall_right = TRUE;
			player.x = warps[1].x;
			player.y = warps[1].y;
			*warps[0].frame = tiles_start [11];
			*warps[1].frame = tiles_start [11];
			warp_enable = FALSE;
		} else if (warps[1].x == player.x && warps[1].y == player.y && warp_enable && player_moving == 0) {
			/* TODO: Reproducir sonido */
			wall_up = wall_down = wall_left = wall_right = TRUE;
			player.x = warps[0].x;
			player.y = warps[0].y;
			*warps[0].frame = tiles_start [11];
			*warps[1].frame = tiles_start [11];
			warp_enable = FALSE;
		} else if (wall_up && wall_down && wall_left && wall_right && player_moving == 0 && *tile_actual != 5 && !player_die) {
			/* Matar al puffle */
			puffle_frame = player_start[PLAYER_DROWN];
			player_die = TRUE;
			mapa[player.y][player.x] = 12;
			frames[player.y][player.x] = tiles_start[12];
		}
		
		/* Verificar colisiones de la caja */
		if (mapa[movible.y - 1][movible.x] >= 20) {
			movible_wall_up = TRUE;
		} else {
			movible_wall_up = FALSE;
		}
		
		if (mapa[movible.y + 1][movible.x] >= 20) {
			movible_wall_down = TRUE;
		} else {
			movible_wall_down = FALSE;
		}
		
		if (mapa[movible.y][movible.x - 1] >= 20) {
			movible_wall_left = TRUE;
		} else {
			movible_wall_left = FALSE;
		}
		
		if (mapa[movible.y][movible.x + 1] >= 20) {
			movible_wall_right = TRUE;
		} else {
			movible_wall_right = FALSE;
		}
		
		if (warp_enable) {
			if (*tile_up == 11 || *tile_down == 11 || *tile_left == 11 || *tile_right == 11) {
				if (*warps[0].frame < 22) {
					frames[warps[0].y][warps[0].x] = tiles_start[17];
					frames[warps[1].y][warps[1].x] = tiles_start[17];
				}
			} else {
				if (*warps[0].frame > 21) {
					frames[warps[0].y][warps[0].x] = tiles_start[16];
					frames[warps[1].y][warps[1].x] = tiles_start[16];
				}
			}
		}
		
		if (*tile_actual == 7) { /* Bolsa de dinero */
			mapa[player.y][player.x] = 2;
			frames[player.y][player.x] = tiles_start[2];
			/* Sumar bonus point */
			
			/* if (savebonuspoint + bonuspoint) {
				Disparar estampa
			   } */
		} else if (*tile_actual == 8) {
			mapa[player.y][player.x] = 3;
			frames[player.y][player.x] = tiles_start[3];
			llave++;
			/* TODO: Reproducir sonido de llave */
		} else if (*tile_actual == 9) {
			mapa[player.y][player.x] = 4;
			frames[player.y][player.x] = tiles_start[4];
			llave++;
			/* TODO: Reproducir sonido de llave */
		} else if (*tile_actual == 6) {
			mapa[player.y][player.x] = 2;
			frames[player.y][player.x] = tiles_start[2];
			llave++;
			/* TODO: Reproducir sonido de llave */
		} else if (*tile_actual == 5 && player_moving == 0 && nivel < 19) {
			save_player.x = player.x;
			save_player.y = player.y;
			nivel++;
			
			if (tiles_flipped == goal) {
				/* Sumar puntos por completo */
				last_solved = TRUE;
				/* if (nivel != 19) TODO: Reproducir sonido */
				/* if (tries == 1) {
					Sumar puntos por hacerlo a la primera
				   }
				*/
			} else {
				last_solved = FALSE;
			}
			/* if (nivel == 19) {
				Calcular puntos de tiempo
				if (niveles_resueltos == 19) disparar estampa
			   }
			*/
			save_tiles_flipped += tiles_flipped;
			tiles_flipped = 0;
			save_snow_melted += snow_melted;
			snow_melted = 0;
			slide_block = 0;
			random = RANDOM(2);
			/* tries == 1 */
			if (nivel != 20) {
				load_map (nivel, mapa, frames, &goal, random, last_solved, warps, &movible);
				if (nivel >= 17) warp_enable = TRUE;
				if (nivel >= 13) warp_wall = TRUE;
			} else {
				/* Poner en blanco la pantalla y salir del gameloop */
				return GAME_QUIT; /* FIXME: Pantalla de salida */
			}
		}
		
		if (player_moving == 0) {
			if (last_key & DOWN && !wall_down) {
				next_player.y = player.y + 1;
				next_player.x = player.x;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x == player.x && movible.y - 1 == player.y && !movible_wall_down) {
					/* Empujar el bloque hacia abajo */
					slide_block = DOWN;
					/* TODO: Reproducir sonido */
				}
			} else if (last_key & UP && !wall_up) {
				next_player.y = player.y - 1;
				next_player.x = player.x;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x == player.x && movible.y + 1 == player.y && !movible_wall_up) {
					/* Empujar el bloque hacia arriba */
					slide_block = UP;
					/* TODO: Reproducir sonido */
				}
			} else if (last_key & LEFT && !wall_left) {
				next_player.y = player.y;
				next_player.x = player.x - 1;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x + 1 == player.x && movible.y == player.y && !movible_wall_left) {
					/* Empujar el bloque hacia arriba */
					slide_block = LEFT;
					/* TODO: Reproducir sonido */
				}
			} else if (last_key & RIGHT && !wall_right) {
				next_player.y = player.y;
				next_player.x = player.x + 1;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x - 1 == player.x && movible.y == player.y && !movible_wall_right) {
					/* Empujar el bloque hacia arriba */
					slide_block = RIGHT;
					/* TODO: Reproducir sonido */
				}
			}
			
			if (player_moving != 0) {
				if (*tile_actual == 2) {
					mapa[player.y][player.x] = 22;
					frames[player.y][player.x] = tiles_start [22];
					tiles_flipped++;
					snow_melted++;
					
					/* if (save_snow_melted + snow_melted == 480) {
						Disparar estampa
					} */
				} else if (*tile_actual == 4) {
					mapa[player.y][player.x] = 2;
					frames[player.y][player.x] = tiles_start [2];
					tiles_flipped++;
					/* TODO: Reproducir sonido */
				} else if (*tile_actual == 14) {
					/* TODO: El area secreta */
				}
			}
		}
		
		/* Dibujado del mapa */
		for (g = 0; g < 15; g++) {
			for (h = 0; h < 19; h++) {
				frames[g][h] = tiles_frames[frames[g][h]];
				
				rect.x = MAP_X + (h * TILE_WIDTH);
				rect.y = MAP_Y + (g * TILE_HEIGHT);
				
				copy_tile (&rect, tiles_outputs [frames[g][h]]);
			}
		}
		
		if (player_moving > 0) {
			player_moving--;
			
			rect.x = MAP_X + (next_player.x * TILE_WIDTH) + ((player.x - next_player.x) * 8 * player_moving);
			rect.y = MAP_Y + (next_player.y * TILE_HEIGHT) + ((player.y - next_player.y) * 8 * player_moving);
			
			if (player_moving == 0) {
				player.x = next_player.x;
				player.y = next_player.y;
			}
		} else {
			rect.x = MAP_X + (player.x * TILE_WIDTH);
			rect.y = MAP_Y + (player.y * TILE_HEIGHT);
		}
		
		puffle_frame = player_frames [puffle_frame];
		copy_tile (&rect, player_outputs[puffle_frame]);
		
		/* Colisiones de la caja contra el portal, luego continuar su movimiento */
		if (movible.x == warps[0].x && movible.y == warps[0].y && warp_wall && slide_moving == 0) {
			warp_wall = FALSE;
			
			movible.x = warps[1].x;
			movible.y = warps[1].y;
		} else if (movible.x == warps[1].x && movible.y == warps[1].y && warp_wall && slide_moving == 0) {
			warp_wall = FALSE;
			
			movible.x = warps[0].x;
			movible.y = warps[0].y;
		} else if (slide_block & UP && slide_moving == 0) {
			if (!movible_wall_up) {
				old_movible = movible;
				movible.y = movible.y - 1;
				slide_moving = 3;
			} else {
				slide_block = 0;
			}
		} else if (slide_block & DOWN && slide_moving == 0) {
			if (!movible_wall_down) {
				old_movible = movible;
				movible.y = movible.y + 1;
				slide_moving = 3;
			} else {
				slide_block = 0;
			}
		} else if (slide_block & LEFT && slide_moving == 0) {
			if (!movible_wall_left) {
				old_movible = movible;
				movible.x = movible.x - 1;
				slide_moving = 3;
			} else {
				slide_block = 0;
			}
		} else if (slide_block & RIGHT && slide_moving == 0) {
			if (!movible_wall_right) {
				old_movible = movible;
				movible.x = movible.x + 1;
				slide_moving = 3;
			} else {
				slide_block = 0;
			}
		}
		
		if (slide_moving > 0) {
			slide_moving--;
			
			rect.x = MAP_X + (movible.x * TILE_WIDTH) + ((old_movible.x - movible.x) * 8 * slide_moving);
			rect.y = MAP_Y + (movible.y * TILE_HEIGHT) + ((old_movible.y - movible.y) * 8 * slide_moving);
		} else {
			rect.x = MAP_X + (movible.x * TILE_WIDTH);
			rect.y = MAP_Y + (movible.y * TILE_HEIGHT);
		}
		
		copy_tile (&rect, TILE_BLOCK);
		
		/* Actualizar la pantalla */
		rect.x = MAP_X;
		rect.y = MAP_Y;
		rect.w = 456;
		rect.h = 360;
		SDL_UpdateRects (screen, 1, &rect);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
		if (player_die && puffle_frame == 92) {
			tiles_flipped = 0;
			snow_melted = 0;
			
			player.y = save_player.y;
			player.x = save_player.x;
			puffle_frame = player_start [PLAYER_IGNITE];
			slide_block = llave = 0;
			load_map (nivel, mapa, frames, &goal, random, last_solved, warps, &movible);
			if (nivel >= 17) warp_enable = TRUE;
			if (nivel >= 13) warp_wall = TRUE;
			player_die = FALSE;
		}
	} while (!done);
	
	return done;
}

/* Set video mode: */
/* Mattias Engdegard <f91-men@nada.kth.se> */
SDL_Surface * set_video_mode (unsigned flags) {
	/* Prefer 16bpp, but also prefer native modes to emulated 16bpp. */

	int depth;

	depth = SDL_VideoModeOK (760, 480, 16, flags);
	return depth ? SDL_SetVideoMode (760, 480, depth, flags) : NULL;
}

void setup (void) {
	SDL_Surface * image;
	int g;
	
	/* Inicializar el Video SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"Error: Can't initialize the video subsystem\n"
			"The error returned by SDL is:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	/* Crear la pantalla de dibujado */
	screen = set_video_mode (0);
	
	if (screen == NULL) {
		fprintf (stderr,
			"Error: Can't setup 760x480 video mode.\n"
			"The error returned by SDL is:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	for (g = 0; g < NUM_IMAGES; g++) {
		image = IMG_Load (images_names[g]);
		
		if (image == NULL) {
			fprintf (stderr,
				"Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n", images_names[g], SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		images[g] = image;
		/* TODO: Mostrar la carga de porcentaje */
	}
	
	/* Cargar los tiles */
	image_tiles = IMG_Load (IMG_TILE_NAME);
	
	if (image_tiles == NULL) {
		fprintf (stderr,
				"Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n", images_names[g], SDL_GetError());
			SDL_Quit ();
			exit (1);
	}
	
	srand (SDL_GetTicks ());
}

void copy_tile (SDL_Rect *rect, int tile) {
	SDL_Rect r_tile;
	
	rect->w = r_tile.w = TILE_WIDTH;
	rect->h = r_tile.h = TILE_HEIGHT;
	r_tile.x = (tile % 8) * TILE_WIDTH;
	r_tile.y = (tile / 8) * TILE_HEIGHT;
	
	SDL_BlitSurface (image_tiles, &r_tile, screen, rect);
}

void load_map (int nivel, int (*mapa)[19], int (*frames)[19], int *goal, int r, int last_solved, Warp *warps, Punto *movible) {
	const int (*copiar)[19];
	int g, h;
	
	movible->x = -1;
	movible->y = -1;
	switch (nivel) {
		case 1:
			copiar = mapa_1;
			*goal = mapa_1_goal;
			break;
		case 2:
			if (r) {
				copiar = mapa_2_1;
			} else {
				copiar = mapa_2_2;
			}
			*goal = mapa_2_goal;
			break;
		case 3:
			if (r) {
				copiar = mapa_3_1;
			} else {
				copiar = mapa_3_2;
			}
			*goal = mapa_3_goal;
			break;
		case 4:
			if (r) {
				copiar = mapa_4_1;
			} else {
				copiar = mapa_4_2;
			}
			*goal = mapa_4_goal;
			break;
		case 5:
			if (r) {
				copiar = mapa_5_1;
			} else {
				copiar = mapa_5_2;
			}
			*goal = mapa_5_goal;
			break;
		case 6:
			if (r) {
				copiar = mapa_6_1;
			} else {
				copiar = mapa_6_2;
			}
			*goal = mapa_6_goal;
			break;
		case 7:
			if (r) {
				copiar = mapa_7_1;
			} else {
				copiar = mapa_7_2;
			}
			*goal = mapa_7_goal;
			break;
		case 8:
			if (r) {
				copiar = mapa_8_1;
			} else {
				copiar = mapa_8_2;
			}
			*goal = mapa_8_goal;
			break;
		case 9:
			if (r) {
				copiar = mapa_9_1;
			} else {
				copiar = mapa_9_2;
			}
			*goal = mapa_9_goal;
			break;
		case 10:
			if (r) {
				copiar = mapa_10_1;
			} else {
				copiar = mapa_10_2;
			}
			*goal = mapa_10_goal;
			break;
		case 11:
			if (r) {
				copiar = mapa_11_1;
			} else {
				copiar = mapa_11_2;
			}
			*goal = mapa_11_goal;
			break;
		case 12:
			if (r) {
				copiar = mapa_12_1;
			} else {
				copiar = mapa_12_2;
			}
			*goal = mapa_12_goal;
			break;
		case 13:
			if (r) {
				copiar = mapa_13_1;
			} else {
				copiar = mapa_13_2;
			}
			*goal = mapa_13_goal;
			
			movible->x = 5;
			movible->y = 9;
			break;
		case 14:
			if (r) {
				copiar = mapa_14_1;
			} else {
				copiar = mapa_14_2;
			}
			*goal = mapa_14_goal;
			
			movible->x = 7;
			movible->y = 8;
			break;
		case 15:
			if (r) {
				copiar = mapa_15_1;
			} else {
				copiar = mapa_15_2;
			}
			*goal = mapa_15_goal;
			
			movible->x = 5;
			movible->y = 8;
			break;
		case 16:
			if (r) {
				copiar = mapa_16_1;
			} else {
				copiar = mapa_16_2;
			}
			*goal = mapa_16_goal;
			
			movible->x = 14;
			movible->y = 5;
			break;
		case 17:
			if (r) {
				copiar = mapa_17_1;
			} else {
				copiar = mapa_17_2;
			}
			*goal = mapa_17_goal;
			
			movible->x = 5;
			movible->y = 11;
			break;
		case 18:
			if (r) {
				copiar = mapa_18_1;
			} else {
				copiar = mapa_18_2;
			}
			*goal = mapa_18_goal;
			
			movible->x = 16;
			movible->y = 10;
			break;
		case 19:
			if (r) {
				copiar = mapa_19_1;
			} else {
				copiar = mapa_19_2;
			}
			*goal = mapa_19_goal;
			
			movible->x = 12;
			movible->y = 7;
			break;
	}
	
	memcpy (mapa, copiar, sizeof (int[15][19]));
	
	if (last_solved) {
		switch (nivel) {
			case 4:
				mapa[7][7] = 7;
				break;
			case 5:
				mapa[10][9] = 7;
				break;
			case 6:
				mapa[11][10] = 7;
				break;
			case 7:
				mapa[9][11] = 7;
				break;
			case 8:
				mapa[10][2] = 7;
				break;
			case 9:
				mapa[3][6] = 7;
				break;
			case 10:
				mapa[5][14] = 7;
				break;
			case 11:
				mapa[13][8] = 7;
				break;
			case 12:
				mapa[7][10] = 7;
				break;
			case 13:
				mapa[7][9] = 7;
				break;
			case 14:
				mapa[3][6] = 7;
				break;
			case 15:
				mapa[5][9] = 7;
				break;
			case 16:
				mapa[9][5] = 7;
				break;
			case 17:
				mapa[5][7] = 7;
				break;
			case 18:
				mapa[1][17] = 7;
				break;
		}
	}
	
	warps[0].x = warps[0].y = warps[1].x = warps[1].y = -1;
	
	r = 0;
	for (g = 0; g < 15; g++) {
		for (h = 0; h < 19; h++) {
			frames[g][h] = tiles_start [mapa[g][h]];
			
			if (mapa[g][h] == 11) {
				warps[r].x = h;
				warps[r].y = g;
				warps[r].frame = &frames[g][h];
				frames[g][h] = tiles_start[16];
				r++;
			}
		}
	}
}

