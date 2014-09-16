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
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

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

#include "cp-button.h"
#include "draw-text.h"

#define FPS (1000/18)
#define MAX_RECTS 16

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
	IMG_PUFFLE_ON_ICE,
	
	IMG_PUFFLE_EXPLAIN,
	IMG_EXPLAIN_1,
	IMG_EXPLAIN_2,
	
	IMG_MONEY_BAG,
	
	IMG_BUTTON_1_UP,
	IMG_BUTTON_1_OVER,
	IMG_BUTTON_1_DOWN,
	
	IMG_BUTTON_2_UP,
	IMG_BUTTON_2_OVER,
	IMG_BUTTON_2_DOWN,
	
	IMG_BUTTON_3_UP,
	IMG_BUTTON_3_OVER,
	IMG_BUTTON_3_DOWN,
	
	IMG_BUTTON_CLOSE_UP,
	IMG_BUTTON_CLOSE_OVER,
	IMG_BUTTON_CLOSE_DOWN,
	
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
	
	IMG_FIRE_1,
	IMG_FIRE_2,
	IMG_FIRE_3,
	IMG_FIRE_4,
	IMG_FIRE_5,
	IMG_FIRE_6,
	IMG_FIRE_7,
	IMG_FIRE_8,
	IMG_FIRE_9,
	IMG_FIRE_10,
	
	IMG_KEYS1,
	IMG_KEYS2,
	
	IMG_PUFFLE_BLACK_1,
	IMG_PUFFLE_BLACK_2,
	IMG_PUFFLE_BLACK_3,
	IMG_PUFFLE_BLACK_4,
	IMG_PUFFLE_BLACK_5,
	IMG_PUFFLE_BLACK_6,
	IMG_PUFFLE_BLACK_7,
	IMG_PUFFLE_BLACK_8,
	IMG_PUFFLE_BLACK_9,
	IMG_PUFFLE_BLACK_10,
	IMG_PUFFLE_BLACK_11,
	IMG_PUFFLE_BLACK_12,
	IMG_PUFFLE_BLACK_13,
	IMG_PUFFLE_BLACK_14,
	IMG_PUFFLE_BLACK_15,
	IMG_PUFFLE_BLACK_16,
	IMG_PUFFLE_BLACK_END1_1,
	IMG_PUFFLE_BLACK_END1_2,
	IMG_PUFFLE_BLACK_END1_3,
	IMG_PUFFLE_BLACK_END1_4,
	IMG_PUFFLE_BLACK_END2_1,
	IMG_PUFFLE_BLACK_END2_2,
	IMG_PUFFLE_BLACK_END2_3,
	IMG_PUFFLE_BLACK_END2_4,
	IMG_PUFFLE_BLACK_END3_1,
	IMG_PUFFLE_BLACK_END3_2,
	IMG_PUFFLE_BLACK_END3_3,
	IMG_PUFFLE_BLACK_END3_4,
	
	IMG_PUFFLE_OFF_1,
	IMG_PUFFLE_OFF_2,
	IMG_PUFFLE_OFF_3,
	IMG_PUFFLE_OFF_4,
	IMG_PUFFLE_OFF_5,
	IMG_PUFFLE_OFF_6,
	IMG_PUFFLE_OFF_7,
	IMG_PUFFLE_OFF_8,
	IMG_PUFFLE_OFF_9,
	IMG_PUFFLE_OFF_10,
	
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
	GAMEDATA_DIR "images/puffle-on-ice.png",
	
	GAMEDATA_DIR "images/puffle-explain.png",
	GAMEDATA_DIR "images/explain1.png",
	GAMEDATA_DIR "images/explain2.png",
	
	GAMEDATA_DIR "images/moneybag.png",
	
	GAMEDATA_DIR "images/boton-ui-1-up.png",
	GAMEDATA_DIR "images/boton-ui-1-over.png",
	GAMEDATA_DIR "images/boton-ui-1-down.png",
	
	GAMEDATA_DIR "images/boton-ui-2-up.png",
	GAMEDATA_DIR "images/boton-ui-2-over.png",
	GAMEDATA_DIR "images/boton-ui-2-down.png",
	
	GAMEDATA_DIR "images/boton-ui-3-up.png",
	GAMEDATA_DIR "images/boton-ui-3-over.png",
	GAMEDATA_DIR "images/boton-ui-3-down.png",
	
	GAMEDATA_DIR "images/boton-close-up.png",
	GAMEDATA_DIR "images/boton-close-over.png",
	GAMEDATA_DIR "images/boton-close-down.png",
	
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
	GAMEDATA_DIR "images/up-3.png",
	
	GAMEDATA_DIR "images/fire1.png",
	GAMEDATA_DIR "images/fire2.png",
	GAMEDATA_DIR "images/fire3.png",
	GAMEDATA_DIR "images/fire4.png",
	GAMEDATA_DIR "images/fire5.png",
	GAMEDATA_DIR "images/fire6.png",
	GAMEDATA_DIR "images/fire7.png",
	GAMEDATA_DIR "images/fire8.png",
	GAMEDATA_DIR "images/fire9.png",
	GAMEDATA_DIR "images/fire10.png",
	
	GAMEDATA_DIR "images/keys1.png",
	GAMEDATA_DIR "images/keys2.png",
	
	GAMEDATA_DIR "images/puffle_black_1.png",
	GAMEDATA_DIR "images/puffle_black_2.png",
	GAMEDATA_DIR "images/puffle_black_3.png",
	GAMEDATA_DIR "images/puffle_black_4.png",
	GAMEDATA_DIR "images/puffle_black_5.png",
	GAMEDATA_DIR "images/puffle_black_6.png",
	GAMEDATA_DIR "images/puffle_black_7.png",
	GAMEDATA_DIR "images/puffle_black_8.png",
	GAMEDATA_DIR "images/puffle_black_9.png",
	GAMEDATA_DIR "images/puffle_black_10.png",
	GAMEDATA_DIR "images/puffle_black_11.png",
	GAMEDATA_DIR "images/puffle_black_12.png",
	GAMEDATA_DIR "images/puffle_black_13.png",
	GAMEDATA_DIR "images/puffle_black_14.png",
	GAMEDATA_DIR "images/puffle_black_15.png",
	GAMEDATA_DIR "images/puffle_black_16.png",
	GAMEDATA_DIR "images/puffle_black_end1_1.png",
	GAMEDATA_DIR "images/puffle_black_end1_2.png",
	GAMEDATA_DIR "images/puffle_black_end1_3.png",
	GAMEDATA_DIR "images/puffle_black_end1_4.png",
	GAMEDATA_DIR "images/puffle_black_end2_1.png",
	GAMEDATA_DIR "images/puffle_black_end2_2.png",
	GAMEDATA_DIR "images/puffle_black_end2_3.png",
	GAMEDATA_DIR "images/puffle_black_end2_4.png",
	GAMEDATA_DIR "images/puffle_black_end3_1.png",
	GAMEDATA_DIR "images/puffle_black_end3_2.png",
	GAMEDATA_DIR "images/puffle_black_end3_3.png",
	GAMEDATA_DIR "images/puffle_black_end3_4.png",
	
	GAMEDATA_DIR "images/puffle_off1.png",
	GAMEDATA_DIR "images/puffle_off2.png",
	GAMEDATA_DIR "images/puffle_off3.png",
	GAMEDATA_DIR "images/puffle_off4.png",
	GAMEDATA_DIR "images/puffle_off5.png",
	GAMEDATA_DIR "images/puffle_off6.png",
	GAMEDATA_DIR "images/puffle_off7.png",
	GAMEDATA_DIR "images/puffle_off8.png",
	GAMEDATA_DIR "images/puffle_off9.png",
	GAMEDATA_DIR "images/puffle_off10.png"
};

#define IMG_TILE_NAME GAMEDATA_DIR "images/tiles.png"

enum {
	SND_START,
	SND_ICE,
	SND_DOUBLE_ICE,
	SND_DROWN,
	SND_MONEY,
	SND_KEY,
	SND_MOVE,
	SND_WARP,
	SND_COMPLETE,
	
	SND_BUTTON,
	
	NUM_SOUNDS
};

const char *sound_names[NUM_SOUNDS] = {
	GAMEDATA_DIR "sounds/start.wav",
	GAMEDATA_DIR "sounds/ice.wav",
	GAMEDATA_DIR "sounds/double.wav",
	GAMEDATA_DIR "sounds/drown.wav",
	GAMEDATA_DIR "sounds/money.wav",
	GAMEDATA_DIR "sounds/key.wav",
	GAMEDATA_DIR "sounds/move.wav",
	GAMEDATA_DIR "sounds/warp.wav",
	GAMEDATA_DIR "sounds/complete.wav",
	
	GAMEDATA_DIR "sounds/button-1.wav"
};

#define MUS_INTRO GAMEDATA_DIR "music/thinice1.ogg"
#define MUS_THINICE GAMEDATA_DIR "music/thinice2.ogg"

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

static int arcade_frames[4] = {
	0,
	2,
	3,
	0
};

static int arcade_outputs [4] = {
	IMG_DOWN_1,
	IMG_DOWN_2,
	IMG_DOWN_2,
	IMG_DOWN_3
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

enum {
	BUTTON_NONE = 0,
	BUTTON_CLOSE,
	
	BUTTON_START,
	BUTTON_PLAY,
	BUTTON_PREV,
	BUTTON_NEXT,
	
	BUTTON_RESET,
	
	BUTTON_GET_COINS,
	
	NUM_BUTTONS
};

enum {
	TEXT_EXPLAIN_1,
	TEXT_EXPLAIN_2,
	TEXT_EXPLAIN_3,
	TEXT_EXPLAIN_4,
	TEXT_EXPLAIN_5,
	
	NUM_TEXTS
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
int game_intro (void);
int game_explain (void);
int game_loop (void);
int game_finish (void);
void setup (void);
SDL_Surface * set_video_mode(unsigned);
void copy_tile (SDL_Rect *rect, int tile);
void load_map (int nivel, int (*mapa)[19], int (*frames)[19], int *goal, int r, int last_solved, Warp *warps, Punto *movible);
void area_secreta (int (*mapa)[19], int (*frames)[19], int solved_stages);
int map_button_in_opening (int x, int y);
int map_button_in_explain (int x, int y, int escena);
int map_button_in_game (int x, int y);
int map_button_in_finish (int x, int y);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * image_tiles;
SDL_Surface * images [NUM_IMAGES];

SDL_Color blanco = {0xff, 0xff, 0xff};
SDL_Color azul = {0x00, 0x66, 0xcc};

int use_sound;
Mix_Chunk * sounds[NUM_SOUNDS];
Mix_Music * music_intro;
Mix_Music * music_thinice;

SDL_Rect rects[MAX_RECTS];
int num_rects = 0;

TTF_Font *ttf13_burbank_bold;
TTF_Font *ttf13_big_black;
TTF_Font *ttf13_burbank_small;

int first_try_count, solved_stages, save_bonus_point, save_tiles_flipped, score, timepoints = 0;

int main (int argc, char *argv[]) {
	setup ();
	
	cp_registrar_botones (NUM_BUTTONS);
	cp_registrar_boton (BUTTON_START, IMG_BUTTON_1_UP);
	cp_registrar_boton (BUTTON_CLOSE, IMG_BUTTON_CLOSE_UP);
	cp_registrar_boton (BUTTON_PLAY, IMG_BUTTON_1_UP);
	cp_registrar_boton (BUTTON_NEXT, IMG_BUTTON_1_UP);
	cp_registrar_boton (BUTTON_PREV, IMG_BUTTON_1_UP);
	cp_registrar_boton (BUTTON_RESET, IMG_BUTTON_2_UP);
	cp_registrar_boton (BUTTON_GET_COINS, IMG_BUTTON_3_UP);
	cp_button_start ();
	
	do {
		if (game_intro () == GAME_QUIT) break;
		if (game_explain () == GAME_QUIT) break;
		if (game_loop () == GAME_QUIT) break;
		if (game_finish () == GAME_QUIT) break;
	} while (1 == 0);
	
	SDL_Quit ();
	return EXIT_SUCCESS;
}

int game_intro (void) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	int map;
	SDL_Surface *play_text_button;
	
	play_text_button = TTF_RenderUTF8_Blended (ttf13_big_black, "PLAY", blanco);
	
	SDL_BlitSurface (images[IMG_ARCADE], NULL, screen, NULL);
	
	rect.x = 184; rect.y = 93;
	rect.w = images[IMG_PUFFLE_ON_ICE]->w; rect.h = images[IMG_PUFFLE_ON_ICE]->h;
	
	SDL_BlitSurface (images[IMG_PUFFLE_ON_ICE], NULL, screen, &rect);
	
	rect.x = 324; rect.y = 382;
	rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_1_UP], NULL, screen, &rect);
	
	rect.x = 324 + (rect.w - play_text_button->w) / 2;
	rect.y = 382 + (rect.h - play_text_button->h) / 2;
	rect.w = play_text_button->w; rect.h = play_text_button->h;
	
	SDL_BlitSurface (play_text_button, NULL, screen, &rect);
	
	rect.x = 663; rect.y = 24;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	SDL_BlitSurface (images[IMG_BUTTON_CLOSE_UP], NULL, screen, &rect);
	
	/* Botones de arcade */
	rect.x = 230; rect.y = 446;
	rect.w = images[IMG_LEFT_1]->w;
	rect.h = images[IMG_LEFT_1]->h;
	SDL_BlitSurface (images[IMG_LEFT_1], NULL, screen, &rect);
	
	rect.x = 423;
	SDL_BlitSurface (images[IMG_RIGHT_1], NULL, screen, &rect);
	
	rect.x = 328; rect.y = 435;
	rect.w = images[IMG_UP_1]->w;
	rect.h = images[IMG_UP_1]->h;
	SDL_BlitSurface (images[IMG_UP_1], NULL, screen, &rect);
	
	rect.x = 324; rect.y = 457;
	rect.w = images[IMG_DOWN_1]->w;
	rect.h = images[IMG_DOWN_1]->h;
	SDL_BlitSurface (images[IMG_DOWN_1], NULL, screen, &rect);
	
	/* Titulo
	rect.x = 227; rect.y = 37*/
	
	SDL_Flip (screen);
	
	Mix_PlayMusic (music_intro, 1);
	
	do {
		last_time = SDL_GetTicks ();
		num_rects = 0;
		
		if (music_intro != NULL) {
			if (!Mix_PlayingMusic ()) {
				Mix_PlayMusic (music_thinice, -1);
				Mix_FreeMusic (music_intro);
				music_intro = NULL;
			}
		}
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEMOTION:
					map = map_button_in_opening (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONDOWN:
					map = map_button_in_opening (event.button.x, event.button.y);
					cp_button_down (map);
					if (map == BUTTON_START) {
						if (use_sound) Mix_PlayChannel (-1, sounds[SND_BUTTON], 0);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					map = map_button_in_opening (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_START:
							done = GAME_CONTINUE;
							break;
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
					}
					break;
			}
		}
		
		if (cp_button_refresh[BUTTON_START]) {
			rect.x = 324; rect.y = 382;
			rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_START]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			
			rect.x = 324 + (rect.w - play_text_button->w) / 2;
			rect.y = 382 + (rect.h - play_text_button->h) / 2;
			rect.w = play_text_button->w; rect.h = play_text_button->h;
			
			SDL_BlitSurface (play_text_button, NULL, screen, &rect);
			
			cp_button_refresh[BUTTON_START] = 0;
		}
		
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 663; rect.y = 24;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		SDL_UpdateRects (screen, num_rects, rects);
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
	} while (!done);
	
	SDL_FreeSurface (play_text_button);
	
	return done;
}

int game_explain (void) {
	int done = 0, g, h;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	int map;
	
	int mapa[3][12];
	int escena = 1;
	int frame;
	int refresh_escena = 0;
	int puffle_frame = player_start [PLAYER_NORMAL];
	SDL_Rect puffle;
	SDL_Surface *texts[NUM_TEXTS];
	SDL_Surface *play_text_button, *prev_text_button, *next_text_button;
	
	play_text_button = TTF_RenderUTF8_Blended (ttf13_big_black, "PLAY", blanco);
	prev_text_button = TTF_RenderUTF8_Blended (ttf13_big_black, "BACK", blanco);
	next_text_button = TTF_RenderUTF8_Blended (ttf13_big_black, "NEXT", blanco);
	
	/* Cadenas traducibles */
	const char * text_strings[NUM_TEXTS] = {	
		"Melt ice on your way through each maze. Once the ice is melted you\ncan't walk back. Melt all the ice to solve the stage",
		"Use the arrow keys to move your\ncharacter around.",
		"Make your way to the red exit to finish the level.",
		"More points are earned by walking over all ice in the\nstage.",
		"Earn more points by solving each level on your first try. Also, coin\nbags will appear if you are solving levels."
	};
	
	for (g = 0; g < NUM_TEXTS; g++) {
		texts[g] = draw_text (ttf13_burbank_bold, text_strings [g], azul, (g == 1) ? ALIGN_LEFT : ALIGN_CENTER, 8);
	}
	
	puffle.w = TILE_WIDTH;
	puffle.h = TILE_HEIGHT;
	
	SDL_BlitSurface (images[IMG_ARCADE], NULL, screen, NULL);
	
	/* Imagen principal */
	rect.x = 164; rect.y = 189;
	rect.w = images[IMG_PUFFLE_EXPLAIN]->w; rect.h = images[IMG_PUFFLE_EXPLAIN]->h;
	SDL_BlitSurface (images[IMG_PUFFLE_EXPLAIN], NULL, screen, &rect);
	
	rect.x = MAP_X + (456 - texts[TEXT_EXPLAIN_1]->w) / 2;;
	rect.y = 115;
	rect.w = texts[TEXT_EXPLAIN_1]->w; rect.h = texts[IMG_EXPLAIN_1]->h;
	
	SDL_BlitSurface (texts[TEXT_EXPLAIN_1], NULL, screen, &rect);
	
	/* Boton de play */
	rect.x = 158; rect.y = 382;
	rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
	SDL_BlitSurface (images[IMG_BUTTON_1_UP], NULL, screen, &rect);
	
	rect.x = 158 + (rect.w - play_text_button->w) / 2;
	rect.y = 382 + (rect.h - play_text_button->h) / 2;
	rect.w = play_text_button->w; rect.h = play_text_button->h;
	
	SDL_BlitSurface (play_text_button, NULL, screen, &rect);
	
	/* Boton de cierre */
	rect.x = 663; rect.y = 24;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	SDL_BlitSurface (images[IMG_BUTTON_CLOSE_UP], NULL, screen, &rect);
	
	/* Boton de siguiente */
	rect.x = 496; rect.y = 382;
	rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
	SDL_BlitSurface (images[IMG_BUTTON_1_UP], NULL, screen, &rect);
	
	rect.x = 496 + (rect.w - next_text_button->w) / 2;
	rect.y = 382 + (rect.h - next_text_button->h) / 2;
	rect.w = next_text_button->w; rect.h = next_text_button->h;
	
	SDL_BlitSurface (next_text_button, NULL, screen, &rect);
	
	/* Botones de arcade */
	rect.x = 230; rect.y = 446;
	rect.w = images[IMG_LEFT_1]->w;
	rect.h = images[IMG_LEFT_1]->h;
	SDL_BlitSurface (images[IMG_LEFT_1], NULL, screen, &rect);
	
	rect.x = 423;
	SDL_BlitSurface (images[IMG_RIGHT_1], NULL, screen, &rect);
	
	rect.x = 328; rect.y = 435;
	rect.w = images[IMG_UP_1]->w;
	rect.h = images[IMG_UP_1]->h;
	SDL_BlitSurface (images[IMG_UP_1], NULL, screen, &rect);
	
	rect.x = 324; rect.y = 457;
	rect.w = images[IMG_DOWN_1]->w;
	rect.h = images[IMG_DOWN_1]->h;
	SDL_BlitSurface (images[IMG_DOWN_1], NULL, screen, &rect);
	
	/* Titulo
	rect.x = 227; rect.y = 37*/
	
	SDL_Flip (screen);
	
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		if (music_intro != NULL) {
			if (!Mix_PlayingMusic ()) {
				Mix_PlayMusic (music_thinice, -1);
				Mix_FreeMusic (music_intro);
				music_intro = NULL;
			}
		}
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEMOTION:
					map = map_button_in_explain (event.motion.x, event.motion.y, escena);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONDOWN:
					map = map_button_in_explain (event.button.x, event.button.y, escena);
					cp_button_down (map);
					if (map != BUTTON_NONE && map != BUTTON_CLOSE) {
						if (use_sound) Mix_PlayChannel (-1, sounds[SND_BUTTON], 0);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					map = map_button_in_explain (event.button.x, event.button.y, escena);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_PLAY:
							done = GAME_CONTINUE;
							break;
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
						case BUTTON_NEXT:
							escena++;
							refresh_escena = 1;
							break;
						case BUTTON_PREV:
							escena--;
							refresh_escena = 1;
							break;
					}
					break;
			}
		}
		
		if (refresh_escena) {
			frame = 0;
			
			/* Borrar la explicación */
			rect.x = MAP_X;
			rect.y = MAP_Y;
			rect.w = 456;
			rect.h = 384;
			
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			/* Redibujar las botones */
			cp_button_refresh[BUTTON_PLAY] = 1;
			cp_button_refresh[BUTTON_PREV] = 1;
			cp_button_refresh[BUTTON_NEXT] = 1;
			
			puffle_frame = player_start [PLAYER_NORMAL];
			
			if (escena == 1) {
				/* Imagen principal */
				rect.x = 164; rect.y = 189;
				rect.w = images[IMG_PUFFLE_EXPLAIN]->w; rect.h = images[IMG_PUFFLE_EXPLAIN]->h;
				SDL_BlitSurface (images[IMG_PUFFLE_EXPLAIN], NULL, screen, &rect);
				
				rect.x = MAP_X + (456 - texts[TEXT_EXPLAIN_1]->w) / 2;
				rect.y = 115;
				rect.w = texts[TEXT_EXPLAIN_1]->w; rect.h = texts[TEXT_EXPLAIN_1]->h;
				
				SDL_BlitSurface (texts[TEXT_EXPLAIN_1], NULL, screen, &rect);
			} else if (escena == 2) {
				rect.x = 317;
				rect.y = 129;
				rect.w = texts[TEXT_EXPLAIN_2]->w; rect.h = texts[TEXT_EXPLAIN_2]->h;
				
				SDL_BlitSurface (texts[TEXT_EXPLAIN_2], NULL, screen, &rect);
				
				rect.x = MAP_X + (456 - texts[TEXT_EXPLAIN_3]->w) / 2;;
				rect.y = 308;
				rect.w = texts[TEXT_EXPLAIN_3]->w; rect.h = texts[TEXT_EXPLAIN_3]->h;
				
				SDL_BlitSurface (texts[TEXT_EXPLAIN_3], NULL, screen, &rect);
				
				rect.x = 192;
				rect.y = 136;
				rect.w = images[IMG_KEYS1]->w; rect.h = images[IMG_KEYS1]->h;
				
				SDL_BlitSurface (images[IMG_KEYS1], NULL, screen, &rect);
			} else if (escena == 3) {
				rect.x = MAP_X + (456 - texts[TEXT_EXPLAIN_4]->w) / 2;;
				rect.y = 120;
				rect.w = texts[TEXT_EXPLAIN_4]->w; rect.h = texts[TEXT_EXPLAIN_4]->h;
				
				SDL_BlitSurface (texts[TEXT_EXPLAIN_4], NULL, screen, &rect);
			} else if (escena == 4) {
				rect.x = MAP_X + (456 - texts[TEXT_EXPLAIN_5]->w) / 2;;
				rect.y = 114;
				rect.w = texts[TEXT_EXPLAIN_5]->w; rect.h = texts[TEXT_EXPLAIN_5]->h;
				
				SDL_BlitSurface (texts[TEXT_EXPLAIN_5], NULL, screen, &rect);
				
				rect.x = 284;
				rect.y = 196;
				rect.w = images[IMG_MONEY_BAG]->w;
				rect.h = images[IMG_MONEY_BAG]->h;
				
				SDL_BlitSurface (images[IMG_MONEY_BAG], NULL, screen, &rect);
				if (use_sound) Mix_PlayChannel (-1, sounds[SND_MONEY], 0);
			}
			refresh_escena = 0;
		}
		
		if (escena == 2) {
			rect.x = rect.y = 192;
			rect.w = images[IMG_EXPLAIN_1]->w;
			rect.h = images[IMG_EXPLAIN_1]->h;
		
			SDL_BlitSurface (images[IMG_EXPLAIN_1], NULL, screen, &rect);
			switch (frame) {
				case 0:
					/* Preparar la segunda escena */
					for (g = 0; g < 3; g++) {
						for (h = 0; h < 12; h++) {
							mapa[g][h] = -1;
						}
					}
					
					puffle.x = 216;
					puffle.y = 240;
					break;
				case 16:
					mapa[1][0] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 17:
				case 18:
					puffle.x += 8;
					break;
				case 21:
					mapa[1][1] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 22:
				case 23:
					puffle.x += 8;
					break;
				case 26:
					mapa[1][2] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 27:
				case 28:
					puffle.x += 8;
					break;
				case 31:
					mapa[1][3] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 32:
				case 33:
					puffle.x += 8;
					break;
				case 36:
					mapa[1][4] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 37:
				case 38:
					puffle.x += 8;
					break;
				case 41:
					mapa[1][5] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 42:
				case 43:
					puffle.x += 8;
					break;
				case 46:
					mapa[1][6] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 47:
				case 48:
					puffle.x += 8;
					break;
				case 51:
					mapa[1][7] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 52:
				case 53:
					puffle.x += 8;
					break;
				case 56:
					mapa[1][8] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 57:
				case 58:
					puffle.x += 8;
					break;
				case 61:
					mapa[1][9] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 62:
				case 63:
					puffle.x += 8;
					break;
				case 66:
					mapa[1][10] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 67:
				case 68:
					puffle.x += 8;
					break;
				case 71:
					mapa[1][11] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 72:
				case 73:
					puffle.x += 8;
					break;
				case 74:
					if (use_sound) Mix_PlayChannel (-1, sounds[SND_COMPLETE], 0);
					break;
			}
			
			if (frame > 14 && frame < 75) {
				g = frame - 15;
				if ((g % 5) == 1 || (g % 5) == 2) {
					rect.x = 192;
					rect.y = 136;
					rect.w = images[IMG_KEYS2]->w; rect.h = images[IMG_KEYS2]->h;
				
					SDL_BlitSurface (images[IMG_KEYS2], NULL, screen, &rect);
				} else {
					rect.x = 192;
					rect.y = 136;
					rect.w = images[IMG_KEYS1]->w; rect.h = images[IMG_KEYS1]->h;
				
					SDL_BlitSurface (images[IMG_KEYS1], NULL, screen, &rect);
				}
			}
		} else if (escena == 3) {
			rect.x = rect.y = 192;
			rect.w = images[IMG_EXPLAIN_2]->w;
			rect.h = images[IMG_EXPLAIN_2]->h;
			
			SDL_BlitSurface (images[IMG_EXPLAIN_2], NULL, screen, &rect);
			switch (frame) {
				case 0:
					for (g = 0; g < 3; g++) {
						for (h = 0; h < 12; h++) {
							mapa[g][h] = -1;
						}
					}
					puffle.x = 216;
					puffle.y = 240;
					break;
				case 16:
					mapa[1][0] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 17:
				case 18:
					puffle.x += 8;
					break;
				case 21:
					mapa[1][1] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 22:
				case 23:
					puffle.x += 8;
					break;
				case 26:
					mapa[1][2] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 27:
				case 28:
					puffle.x += 8;
					break;
				case 31:
					mapa[1][3] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 32:
				case 33:
					puffle.x += 8;
					break;
				case 36:
					mapa[1][4] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 37:
				case 38:
					puffle.x += 8;
					break;
				case 41:
					mapa[1][5] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 42:
				case 43:
					puffle.x += 8;
					break;
				case 46:
					mapa[1][6] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 47:
				case 48:
					puffle.x += 8;
					break;
				case 51:
					mapa[1][7] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 52:
				case 53:
					puffle.y -= 8;
					break;
				case 56:
					mapa[0][7] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 57:
				case 58:
					puffle.x += 8;
					break;
				case 61:
					mapa[0][8] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 62:
				case 63:
					puffle.x += 8;
					break;
				case 66:
					mapa[0][9] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 67:
				case 68:
					puffle.y += 8;
					break;
				case 71:
					mapa[1][9] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 72:
				case 73:
					puffle.x -= 8;
					break;
				case 76:
					mapa[1][8] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 77:
				case 78:
					puffle.y += 8;
					break;
				case 81:
					mapa[2][8] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 82:
				case 83:
					puffle.x += 8;
					break;
				case 86:
					mapa[2][9] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 87:
				case 88:
					puffle.x += 8;
					break;
				case 91:
					mapa[2][10] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 92:
				case 93:
					puffle.y -= 8;
					break;
				case 96:
					mapa[1][10] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 97:
				case 98:
					puffle.x += 8;
					break;
				case 101:
					mapa[1][11] = tiles_start[22];
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
				case 102:
				case 103:
					puffle.x += 8;
					break;
				case 104:
					if (use_sound) Mix_PlayChannel (-1, sounds[SND_COMPLETE], 0);
					break;
			}
		}
		
		if (escena == 2 || escena == 3) {
			for (g = 0; g < 3; g++) {
				for (h = 0; h < 12; h++) {
					if (mapa[g][h] != -1) {
						mapa[g][h] = tiles_frames[mapa[g][h]];
						
						/* Dibujar */
						rect.x = 216 + (h * TILE_WIDTH);
						rect.y = 216 + (g * TILE_HEIGHT);
						
						copy_tile (&rect, tiles_outputs [mapa[g][h]]);
					}
				}
			}
			frame++;
			if (escena == 2 && frame >= 105) frame = 0;
			if (escena == 3 && frame >= 143) frame = 0;
			
			puffle_frame = player_frames [puffle_frame];
			copy_tile (&puffle, player_outputs[puffle_frame]);
		}
		
		if (cp_button_refresh[BUTTON_PLAY]) {
			rect.x = 158; rect.y = 382;
			rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_PLAY]], NULL, screen, &rect);
			
			rect.x = 158 + (rect.w - play_text_button->w) / 2;
			rect.y = 382 + (rect.h - play_text_button->h) / 2;
			rect.w = play_text_button->w; rect.h = play_text_button->h;
			
			SDL_BlitSurface (play_text_button, NULL, screen, &rect);
			cp_button_refresh[BUTTON_PLAY] = 0;
		}
		
		if (escena > 1 && cp_button_refresh[BUTTON_PREV]) {
			rect.x = 396; rect.y = 382;
			rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_PREV]], NULL, screen, &rect);
			
			rect.x = 396 + (rect.w - prev_text_button->w) / 2;
			rect.y = 382 + (rect.h - prev_text_button->h) / 2;
			rect.w = prev_text_button->w; rect.h = prev_text_button->h;
			
			SDL_BlitSurface (prev_text_button, NULL, screen, &rect);
			cp_button_refresh[BUTTON_PREV] = 0;
		}
		
		if (escena < 4 && cp_button_refresh[BUTTON_NEXT]) {
			rect.x = 496; rect.y = 382;
			rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_NEXT]], NULL, screen, &rect);
			rect.x = 496 + (rect.w - next_text_button->w) / 2;
			rect.y = 382 + (rect.h - next_text_button->h) / 2;
			rect.w = next_text_button->w; rect.h = next_text_button->h;
			
			SDL_BlitSurface (next_text_button, NULL, screen, &rect);
			cp_button_refresh[BUTTON_NEXT] = 0;
		}
		
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 663; rect.y = 24;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		rect.x = MAP_X;
		rect.y = MAP_Y;
		rect.w = 456;
		rect.h = 384;
		
		rects[num_rects++] = rect;
		
		SDL_UpdateRects (screen, num_rects, rects);
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
	} while (!done);
	
	/* Liberar los textos rederizados */
	for (g = 0; g < NUM_TEXTS; g++) {
		SDL_FreeSurface (texts[g]);
	}
	
	SDL_FreeSurface (play_text_button);
	SDL_FreeSurface (prev_text_button);
	SDL_FreeSurface (next_text_button);
	
	return done;
}

int game_loop (void) {
	int done = 0, g, h;
	SDL_Event event;
	int last_key;
	Uint32 last_time, now_time;
	Uint32 timer;
	SDL_Rect rect;
	int map;
	SDL_Surface *text;
	char buf[20];
	int update_text;
	int tiles_text_x;
	
	/* tiles_flipped representa los tiles pisados. Se guardan por nivel
	 * y se acumulan en save_tiles_flipped
	 * save_snow_melted representa los bloques derretidos. Se guardan por nivel
	 * y se acumulan en save_snow_melted.
	 * bonus_point representa la cantidad de bolsas de dinero. Se acumulan en
	 * save_bonus_point
	 * solved_stages representa los niveles completados correctamente.
	 * tries cantidad de intentos por nivel
	 * First_try_points suma los tiles_flipped si el nivel se resolvió en el
	 * primer intento.
	 * First_try_count cuando la cantidad de niveles resueltos en el primer
	 * intento.
	 */
	int tiles_flipped, snow_melted, save_snow_melted;
	int bonus_point, solved_points;
	int tries, first_try_points;
	int tally;
	
	int mapa[15][19];
	int frames[15][19];
	int nivel = 1;
	int puffle_frame;
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
	SDL_Surface *reset_text_button;
	
	int arcade_button_left = 0, arcade_button_right = 0, arcade_button_up = 0, arcade_button_down = 0;
	
	tiles_flipped = save_tiles_flipped = snow_melted = save_snow_melted = 0;
	solved_points = bonus_point = save_bonus_point = solved_stages = 0;
	first_try_points = first_try_count = 0;
	tries = 1;
	
	puffle_frame = player_start[PLAYER_IGNITE];
	player_moving = slide_moving = 0;
	wall_up = wall_down = wall_left = wall_right = FALSE;
	movible_wall_up = movible_wall_down = movible_wall_left = movible_wall_right = FALSE;
	slide_block = llave = 0;
	player_die = FALSE;
	last_key = 0;
	score = tally = 0;
	
	player.x = save_player.x = 14;
	player.y = save_player.y = 10;
	
	SDL_BlitSurface (images[IMG_ARCADE], NULL, screen, NULL);
	load_map (nivel, mapa, frames, &goal, random, FALSE, warps, &movible);
	
	/* Predibujar el boton de cierre */
	rect.x = 663; rect.y = 24;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_CLOSE_UP], NULL, screen, &rect);
	
	reset_text_button = TTF_RenderUTF8_Blended (ttf13_big_black, "RESET", blanco);
	
	/* Predibujar el botón de reset */
	rect.x = 155; rect.y = 410;
	rect.w = images[IMG_BUTTON_2_UP]->w; rect.h = images[IMG_BUTTON_2_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_2_UP], NULL, screen, &rect);
	
	rect.x = 155 + (rect.w - reset_text_button->w) / 2;
	rect.y = 411 + (rect.h - reset_text_button->h) / 2;
	rect.w = reset_text_button->w; rect.h = reset_text_button->h;
	
	SDL_BlitSurface (reset_text_button, NULL, screen, &rect);
	
	/* Botones de arcade */
	rect.x = 230; rect.y = 446;
	rect.w = images[IMG_LEFT_1]->w;
	rect.h = images[IMG_LEFT_1]->h;
	SDL_BlitSurface (images[IMG_LEFT_1], NULL, screen, &rect);
	
	rect.x = 423;
	SDL_BlitSurface (images[IMG_RIGHT_1], NULL, screen, &rect);
	
	rect.x = 328; rect.y = 435;
	rect.w = images[IMG_UP_1]->w;
	rect.h = images[IMG_UP_1]->h;
	SDL_BlitSurface (images[IMG_UP_1], NULL, screen, &rect);
	
	rect.x = 324; rect.y = 457;
	rect.w = images[IMG_DOWN_1]->w;
	rect.h = images[IMG_DOWN_1]->h;
	SDL_BlitSurface (images[IMG_DOWN_1], NULL, screen, &rect);
	
	/* Textos estáticos en la pantalla */
	TTF_SetFontStyle (ttf13_burbank_bold,  TTF_STYLE_BOLD);
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "LEVEL", azul);
	rect.x = MAP_X - 4 + ((TILE_WIDTH * 4) - text->w);
	rect.y = 30;
	rect.w = text->w; rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, screen, &rect);
	SDL_FreeSurface (text);
	
	/* Nieveles resueltos */
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "SOLVED", azul);
	rect.x = MAP_X - 8 + ((TILE_WIDTH * 17) - text->w);
	rect.y = 30;
	rect.w = text->w; rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, screen, &rect);
	SDL_FreeSurface (text);
	
	/* Puntos */
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "POINTS", azul);
	rect.x = MAP_X - 12 + ((TILE_WIDTH * 17) - text->w);
	rect.y = 413;
	rect.w = text->w; rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, screen, &rect);
	SDL_FreeSurface (text);
	
	/* La "/" */
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "/", azul);
	tiles_text_x = rect.x = MAP_X + ((TILE_WIDTH * 10) - text->w);
	rect.y = 30;
	rect.w = text->w; rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, screen, &rect);
	SDL_FreeSurface (text);
	
	/* El goal */
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "12", azul);
	rect.x = MAP_X + (TILE_WIDTH * 10);
	rect.y = 30;
	rect.w = text->w; rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, screen, &rect);
	SDL_FreeSurface (text);
	
	/* El 1 de nivel 1 */
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "1", azul);
	
	rect.h = text->h;
	rect.w = text->w;
	rect.x = MAP_X + (TILE_WIDTH * 4);
	rect.y = 30;
	SDL_BlitSurface (text, NULL, screen, &rect);
	SDL_FreeSurface (text);
	
	/* Los múltiples 0 iniciales */
	text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "0", azul);
	
	rect.h = text->h;
	rect.w = text->w;
	rect.x = MAP_X + (TILE_WIDTH * 17);
	SDL_BlitSurface (text, NULL, screen, &rect);
	
	rect.y = 413;
	SDL_BlitSurface (text, NULL, screen, &rect);
	
	rect.y = 30;
	rect.x = tiles_text_x - rect.w;
	SDL_BlitSurface (text, NULL, screen, &rect);
	
	SDL_FreeSurface (text);
	
	SDL_Flip (screen);
	timer = SDL_GetTicks ();
	if (use_sound) Mix_PlayChannel (-1, sounds[SND_START], 0);
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		if (music_intro != NULL) {
			if (!Mix_PlayingMusic ()) {
				Mix_PlayMusic (music_thinice, -1);
				Mix_FreeMusic (music_intro);
				music_intro = NULL;
			}
		}
		
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
				case SDL_MOUSEMOTION:
					map = map_button_in_game (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONDOWN:
					map = map_button_in_game (event.button.x, event.button.y);
					cp_button_down (map);
					
					switch (map) {
						case BUTTON_RESET:
							/* Reiniciar el nivel */
							tiles_flipped = 0;
							snow_melted = 0;
							bonus_point = 0;
							tries++;
							player.y = save_player.y;
							player.x = save_player.x;
							puffle_frame = player_start [PLAYER_IGNITE];
							player_moving = slide_block = llave = 0;
							load_map (nivel, mapa, frames, &goal, random, last_solved, warps, &movible);
							if (nivel >= 17) warp_enable = TRUE;
							if (nivel >= 13) warp_wall = TRUE;
							if (use_sound) Mix_PlayChannel (-1, sounds[SND_DROWN], 0);
							
							/* Actualizar los tiles flipped */
							text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "0", azul);
							rect.y = 30;
							rect.w = TILE_WIDTH * 2;
							rect.x = tiles_text_x - rect.w;
							rect.h = text->h;
							num_rects = 0;
							rects[num_rects++] = rect;
							SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
							
							rect.w = text->w;
							rect.x = tiles_text_x - rect.w;
							
							SDL_BlitSurface (text, NULL, screen, &rect);
							SDL_FreeSurface (text);
							SDL_Flip (screen);
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					map = map_button_in_game (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
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
				if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
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
				if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
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
				if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
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
				if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
				wall_right = FALSE;
			}
		} else if (movible.y == player.y && movible.x - 1 == player.x && movible_wall_right) {
			wall_right = TRUE;
		} else {
			wall_right = FALSE;
		}
		
		if (warps[0].x == player.x && warps[0].y == player.y && warp_enable && player_moving == 0) {
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_WARP], 0);
			wall_up = wall_down = wall_left = wall_right = TRUE;
			player.x = warps[1].x;
			player.y = warps[1].y;
			*warps[0].frame = tiles_start [11];
			*warps[1].frame = tiles_start [11];
			warp_enable = FALSE;
		} else if (warps[1].x == player.x && warps[1].y == player.y && warp_enable && player_moving == 0) {
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_WARP], 0);
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
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_DROWN], 0);
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
			bonus_point++;
			
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_MONEY], 0);
			/*
			int suma_bolsas = save_bonus_point + bonus_point;
			if (suma_bolsas == 1) {
				Disparar estampa 63
			} else if (suma_bolsas == 3) {
				Disparar estampa 64
			} else if (suma_bolsas == 6) {
				Disparar estampa 65
			} else if (suma_bolsas == 10) {
				Disparar estampa 67
			} else if (suma_bolsas == 33) {
				Disparar estampa 70
			}*/
		} else if (*tile_actual == 8) {
			mapa[player.y][player.x] = 3;
			frames[player.y][player.x] = tiles_start[3];
			llave++;
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
		} else if (*tile_actual == 9) {
			mapa[player.y][player.x] = 4;
			frames[player.y][player.x] = tiles_start[4];
			llave++;
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
		} else if (*tile_actual == 6) {
			mapa[player.y][player.x] = 2;
			frames[player.y][player.x] = tiles_start[2];
			llave++;
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_KEY], 0);
		} else if (*tile_actual == 5 && player_moving == 0 && nivel < 20) {
			save_player.x = player.x;
			save_player.y = player.y;
			nivel++;
			
			/* Actualizar el nivel */
			sprintf (buf, "%i", nivel);
			
			text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buf, azul);
			rect.y = 30;
			rect.x = MAP_X + (TILE_WIDTH * 4);
			rect.h = text->h;
			rect.w = TILE_WIDTH * 2;
			rects[num_rects++] = rect;
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			rect.w = text->w;
			SDL_BlitSurface (text, NULL, screen, &rect);
			SDL_FreeSurface (text);
			
			if (tiles_flipped == goal) {
				solved_points += tiles_flipped;
				last_solved = TRUE;
				solved_stages++;
				sprintf (buf, "%i", solved_stages);
				
				/* Actualizar la cantidad de stages resueltos */
				text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buf, azul);
				rect.y = 30;
				rect.x = MAP_X + (TILE_WIDTH * 17);
				rect.h = text->h;
				rect.w = TILE_WIDTH * 2;
				rects[num_rects++] = rect;
				SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
				
				rect.w = text->w;
				SDL_BlitSurface (text, NULL, screen, &rect);
				SDL_FreeSurface (text);
				
				if (nivel != 19) if (use_sound) Mix_PlayChannel (-1, sounds[SND_COMPLETE], 0);
				if (tries == 1) {
					first_try_points += tiles_flipped;
					first_try_count++;
				}
			} else {
				last_solved = FALSE;
			}
			
			if (solved_stages == 19) {
				timepoints = ((SDL_GetTicks () - timer) / 1000) * 6;
				/* Disparar estampa 71 */
			}
			
			save_tiles_flipped += tiles_flipped;
			tiles_flipped = 0;
			save_snow_melted += snow_melted;
			snow_melted = 0;
			save_bonus_point += bonus_point;
			bonus_point = 0;
			slide_block = 0;
			random = RANDOM(2);
			tries = 1;
			if (nivel != 20) {
				load_map (nivel, mapa, frames, &goal, random, last_solved, warps, &movible);
				if (nivel >= 17) warp_enable = TRUE;
				if (nivel >= 13) warp_wall = TRUE;
			} else {
				/* Poner en blanco la pantalla y salir del gameloop */
				score = tiles_flipped + save_tiles_flipped + solved_points + (bonus_point * 100) + save_bonus_point * 100 + first_try_points + timepoints;
				return GAME_CONTINUE;
			}
			
			/* Actualizar los tiles flipped */
			text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "0", azul);
			rect.y = 30;
			rect.w = TILE_WIDTH * 2;
			rect.x = tiles_text_x - rect.w;
			rect.h = text->h;
			rects[num_rects++] = rect;
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			rect.w = text->w;
			rect.x = tiles_text_x - rect.w;
			
			SDL_BlitSurface (text, NULL, screen, &rect);
			SDL_FreeSurface (text);
			
			/* Actualizar el texto del goal */
			sprintf (buf, "%i", goal);
			
			text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buf, azul);
			rect.y = 30;
			rect.x = MAP_X + (TILE_WIDTH * 10);
			rect.h = text->h;
			rect.w = TILE_WIDTH * 2;
			rects[num_rects++] = rect;
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			rect.w = text->w;
			
			SDL_BlitSurface (text, NULL, screen, &rect);
			SDL_FreeSurface (text);
			
		} else if (*tile_actual == 14) {
			area_secreta (mapa, frames, solved_stages);
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_WARP], 0);
		}
		
		if (player_moving == 0) {
			if (last_key & DOWN && !wall_down) {
				next_player.y = player.y + 1;
				next_player.x = player.x;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x == player.x && movible.y - 1 == player.y && !movible_wall_down && slide_block == 0) {
					/* Empujar el bloque hacia abajo */
					slide_block = DOWN;
					if (use_sound) Mix_PlayChannel (-1, sounds[SND_MOVE], 0);
				}
			} else if (last_key & UP && !wall_up) {
				next_player.y = player.y - 1;
				next_player.x = player.x;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x == player.x && movible.y + 1 == player.y && !movible_wall_up && slide_block == 0) {
					/* Empujar el bloque hacia arriba */
					slide_block = UP;
					if (use_sound) Mix_PlayChannel (-1, sounds[SND_MOVE], 0);
				}
			} else if (last_key & LEFT && !wall_left) {
				next_player.y = player.y;
				next_player.x = player.x - 1;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x + 1 == player.x && movible.y == player.y && !movible_wall_left && slide_block == 0) {
					/* Empujar el bloque hacia arriba */
					slide_block = LEFT;
					if (use_sound) Mix_PlayChannel (-1, sounds[SND_MOVE], 0);
				}
			} else if (last_key & RIGHT && !wall_right) {
				next_player.y = player.y;
				next_player.x = player.x + 1;
				player_moving = 3;
				
				/* Empujar el bloque */
				if (movible.x - 1 == player.x && movible.y == player.y && !movible_wall_right && slide_block == 0) {
					/* Empujar el bloque hacia arriba */
					slide_block = RIGHT;
					if (use_sound) Mix_PlayChannel (-1, sounds[SND_MOVE], 0);
				}
			}
			
			if (player_moving != 0) {
				if (*tile_actual == 2) {
					mapa[player.y][player.x] = 22;
					frames[player.y][player.x] = tiles_start [22];
					tiles_flipped++;
					snow_melted++;
					if (use_sound) Mix_PlayChannel (0, sounds[SND_ICE], 0);
					/* if (save_snow_melted + snow_melted == 480) {
						Disparar estampa
					} */
					
					/* Actualizar los tiles flipped */
					sprintf (buf, "%i", tiles_flipped);
					text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buf, azul);
					rect.y = 30;
					rect.w = TILE_WIDTH * 2;
					rect.x = tiles_text_x - rect.w;
					rect.h = text->h;
					rects[num_rects++] = rect;
					SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
					rect.w = text->w;
					rect.x = tiles_text_x - rect.w;
			
					SDL_BlitSurface (text, NULL, screen, &rect);
					SDL_FreeSurface (text);
				} else if (*tile_actual == 4) {
					mapa[player.y][player.x] = 2;
					frames[player.y][player.x] = tiles_start [2];
					tiles_flipped++;
					if (use_sound) Mix_PlayChannel (0, sounds[SND_DOUBLE_ICE], 0);
					/* Actualizar los tiles flipped */
					
					sprintf (buf, "%i", tiles_flipped);
					text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buf, azul);
					rect.y = 30;
					rect.w = TILE_WIDTH * 2;
					rect.x = tiles_text_x - rect.w;
					rect.h = text->h;
					rects[num_rects++] = rect;
					SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
					rect.w = text->w;
					rect.x = tiles_text_x - rect.w;
			
					SDL_BlitSurface (text, NULL, screen, &rect);
					SDL_FreeSurface (text);
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
			copy_tile (&rect, TILE_BLOCK);
		} else if (movible.x != -1) {
			rect.x = MAP_X + (movible.x * TILE_WIDTH);
			rect.y = MAP_Y + (movible.y * TILE_HEIGHT);
			copy_tile (&rect, TILE_BLOCK);
		}
		
		/* Redibujar los puntos */
		score = tiles_flipped + save_tiles_flipped + solved_points + (bonus_point * 100) + save_bonus_point * 100 + first_try_points;// + timepoints;
		update_text = 0;
		if (tally < score - 110) {
			update_text = 1;
			tally = tally + 110;
		} else if (tally < score - 11) {
			update_text = 1;
			tally = tally + 11;
		} else if (tally < score) {
			update_text = 1;
			tally = tally + 1;
		} else if (tally > score) {
			update_text = 1;
			tally = score;
		}
		
		if (update_text) {
			sprintf (buf, "%i", tally);
			text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buf, azul);
			rect.y = 413;
			rect.x = MAP_X + (TILE_WIDTH * 17);
			rect.h = text->h;
			rect.w = TILE_WIDTH * 4;
			rects[num_rects++] = rect;
			
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			rect.w = text->w;
			
			SDL_BlitSurface (text, NULL, screen, &rect);
			SDL_FreeSurface (text);
		}
		
		if (last_key & DOWN) {
			arcade_button_down = 1;
		}
		arcade_button_down = arcade_frames[arcade_button_down];
		if (last_key & UP) {
			arcade_button_up = 1;
		}
		arcade_button_up = arcade_frames[arcade_button_up];
		if (last_key & LEFT) {
			arcade_button_left = 1;
		}
		arcade_button_left = arcade_frames[arcade_button_left];
		if (last_key & RIGHT) {
			arcade_button_right = 1;
		}
		arcade_button_right = arcade_frames[arcade_button_right];
		
		rect.x = 229;
		rect.y = 433;
		rect.w = 286;
		rect.h = 48;
		SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
		
		rect.x = 230; rect.y = 446;
		rect.w = images[IMG_LEFT_1]->w;
		rect.h = images[IMG_LEFT_1]->h;
		SDL_BlitSurface (images[3 + arcade_outputs[arcade_button_left]], NULL, screen, &rect);
		
		rect.x = 423;
		SDL_BlitSurface (images[6 + arcade_outputs[arcade_button_right]], NULL, screen, &rect);
		
		rect.x = 328; rect.y = 435;
		rect.w = images[IMG_UP_1]->w;
		rect.h = images[IMG_UP_1]->h;
		SDL_BlitSurface (images[9 + arcade_outputs[arcade_button_up]], NULL, screen, &rect);
		
		rect.x = 324; rect.y = 457;
		rect.w = images[IMG_DOWN_1]->w;
		rect.h = images[IMG_DOWN_1]->h;
		SDL_BlitSurface (images[arcade_outputs[arcade_button_down]], NULL, screen, &rect);
		
		/* El botón de cierre */
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 663; rect.y = 24;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		/* El botón de reinicio */
		if (cp_button_refresh[BUTTON_RESET]) {
			rect.x = 155; rect.y = 410;
			rect.w = images[IMG_BUTTON_2_UP]->w; rect.h = images[IMG_BUTTON_2_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_RESET]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			
			rect.x = 155 + (rect.w - reset_text_button->w) / 2;
			rect.y = 411 + (rect.h - reset_text_button->h) / 2;
			rect.w = reset_text_button->w; rect.h = reset_text_button->h;
			
			SDL_BlitSurface (reset_text_button, NULL, screen, &rect);
			cp_button_refresh[BUTTON_RESET] = 0;
		}
		
		/* Actualizar la pantalla */
		rect.x = MAP_X;
		rect.y = MAP_Y;
		rect.w = 456;
		rect.h = 432;
		rects[num_rects++] = rect;
		
		SDL_UpdateRects (screen, num_rects, rects);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
		if (player_die && puffle_frame >= 92) {
			tiles_flipped = 0;
			snow_melted = 0;
			bonus_point = 0;
			tries++;
			player.y = save_player.y;
			player.x = save_player.x;
			puffle_frame = player_start [PLAYER_IGNITE];
			slide_block = llave = 0;
			load_map (nivel, mapa, frames, &goal, random, last_solved, warps, &movible);
			if (nivel >= 17) warp_enable = TRUE;
			if (nivel >= 13) warp_wall = TRUE;
			player_die = FALSE;
			if (use_sound) Mix_PlayChannel (-1, sounds[SND_START], 0);
			
			/* Actualizar los tiles flipped */
			text = TTF_RenderUTF8_Blended (ttf13_burbank_bold, "0", azul);
			rect.y = 30;
			rect.w = TILE_WIDTH * 2;
			rect.x = tiles_text_x - rect.w;
			rect.h = text->h;
			num_rects = 0;
			rects[num_rects++] = rect;
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			rect.w = text->w;
			rect.x = tiles_text_x - rect.w;
			
			SDL_BlitSurface (text, NULL, screen, &rect);
			SDL_FreeSurface (text);
			SDL_UpdateRects (screen, num_rects, rects);
		}
	} while (!done);
	
	SDL_FreeSurface (reset_text_button);
	return done;
}

//int first_try_count, solved_stages, bonus_point, tiles_flipped, score;
/* TODO: La secuencia de salida está poco optimazada con respecto a los refrescos en pantalla */
int game_finish (void) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	int map;
	int end, image, coins;
	int timing = 1;
	float temp = 372.2, temp2 = 14.02;
	char buf[30];
	SDL_Surface *texts_finish[7], *get_coins_text_button;
	SDL_Surface *numero[7];
	char *texts_finish_string[7] = {
		"Levels solved",
		"Levels solved on first try",
		"Coins bags collected",
		"Total ice melted",
		"Solved game quickly bonus",
		"Total points",
		"Coins earned"
	};
	
	if (solved_stages < 4) {
		end = 1;
	} else if (solved_stages < 18) {
		end = 2;
	} else {
		end = 3;
	}
	
	/* Generar los textos */
	for (image = 0; image < 7; image++) {
		texts_finish[image] = TTF_RenderUTF8_Blended (ttf13_burbank_small, texts_finish_string[image], azul);
	}
	
	/* Generar los puntos */
	sprintf (buf, "%i", solved_stages);
	numero[0] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	sprintf (buf, "%i", first_try_count);
	numero[1] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	sprintf (buf, "%i", save_bonus_point);
	numero[2] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	sprintf (buf, "%i tiles", save_tiles_flipped);
	numero[3] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	sprintf (buf, "%i points", timepoints);
	numero[4] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	sprintf (buf, "%i", score);
	numero[5] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	coins = (int) round (score * 0.10);
	
	sprintf (buf, "%i", coins);
	numero[6] = TTF_RenderUTF8_Blended (ttf13_burbank_small, buf, azul);
	
	SDL_BlitSurface (images[IMG_ARCADE], NULL, screen, NULL);
	
	/* Predibujar el boton de cierre */
	rect.x = 663; rect.y = 24;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	SDL_BlitSurface (images[IMG_BUTTON_CLOSE_UP], NULL, screen, &rect);
	
	get_coins_text_button = TTF_RenderUTF8_Blended (ttf13_big_black, "GET COINS", blanco);
	
	/* Predibujar el botón de get coins */
	rect.x = 455; rect.y = 400;
	rect.w = images[IMG_BUTTON_3_UP]->w; rect.h = images[IMG_BUTTON_3_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_3_UP], NULL, screen, &rect);
	
	rect.x = 455 + (rect.w - get_coins_text_button->w) / 2;
	rect.y = 400 + (rect.h - get_coins_text_button->h) / 2;
	rect.w = get_coins_text_button->w; rect.h = get_coins_text_button->h;
	
	SDL_BlitSurface (get_coins_text_button, NULL, screen, &rect);
	
	/* Botones de arcade */
	rect.x = 230; rect.y = 446;
	rect.w = images[IMG_LEFT_1]->w;
	rect.h = images[IMG_LEFT_1]->h;
	SDL_BlitSurface (images[IMG_LEFT_1], NULL, screen, &rect);
	
	rect.x = 423;
	SDL_BlitSurface (images[IMG_RIGHT_1], NULL, screen, &rect);
	
	rect.x = 328; rect.y = 435;
	rect.w = images[IMG_UP_1]->w;
	rect.h = images[IMG_UP_1]->h;
	SDL_BlitSurface (images[IMG_UP_1], NULL, screen, &rect);
	
	rect.x = 324; rect.y = 457;
	rect.w = images[IMG_DOWN_1]->w;
	rect.h = images[IMG_DOWN_1]->h;
	SDL_BlitSurface (images[IMG_DOWN_1], NULL, screen, &rect);
	
	SDL_Flip (screen);
	
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEMOTION:
					map = map_button_in_finish (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONDOWN:
					map = map_button_in_finish (event.button.x, event.button.y);
					cp_button_down (map);
					break;
				case SDL_MOUSEBUTTONUP:
					map = map_button_in_finish (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
						case BUTTON_GET_COINS:
							done = GAME_QUIT;
							break;
					}
					break;
			}
		}
		
		rect.x = MAP_X;
		rect.y = MAP_Y - 32;
		rect.w = 456;
		rect.h = 376;
		SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
		rects[num_rects++] = rect;
		
		/* Hacer el dibujado de fuego común a los 3 finales */
		if (timing <= 60) {
			rect.x = MAP_X;
			rect.y = MAP_Y;
			rect.w = 456;
			rect.h = 432;
	
			SDL_SetClipRect (screen, &rect);
			
			rect.x = 376 - (int) temp;
			rect.y = 170;
			image = IMG_FIRE_1 + (timing % 10);
			
			rect.w = images[image]->w;
			rect.h = images[image]->h;
			
			SDL_BlitSurface (images[image], NULL, screen, &rect);
			
			if (timing == 60) {
				rect.x = 362;
				rect.y = 258;
				rect.w = images[IMG_PUFFLE_OFF_1]->w;
				rect.h = images[IMG_PUFFLE_OFF_1]->h;
				
				SDL_BlitSurface (images[IMG_PUFFLE_OFF_1], NULL, screen, &rect);
			}
			
			if (timing <= 40) {
				rect.x = (int) temp2;
				rect.y = 281;
				image = IMG_PUFFLE_BLACK_1 + (timing % 8);
				
				rect.w = images[image]->w;
				rect.h = images[image]->h;
				
				SDL_BlitSurface (images[image], NULL, screen, &rect);
				
				if ((int) temp2 < 319) {
					temp2 += 7.82;
				}
			} else {
				rect.x = 325;
				rect.y = 296;
				rect.w = images[IMG_PUFFLE_BLACK_9]->w;
				rect.h = images[IMG_PUFFLE_BLACK_9]->h;
				
				SDL_BlitSurface (images[IMG_PUFFLE_BLACK_9], NULL, screen, &rect);
			}
			
			if ((int) temp > 68) {
				temp -= 7.8;
			}
			
			SDL_SetClipRect (screen, NULL);
		} else if (timing <= 240 || (end != 3 && timing <= 244)) {
			rect.x = 309;
			rect.y = 246;
			if (timing >= 64 && timing <= 70) {
				rect.w = images[IMG_PUFFLE_BLACK_13]->w;
				rect.h = images[IMG_PUFFLE_BLACK_13]->h;
				
				SDL_BlitSurface (images[IMG_PUFFLE_BLACK_13], NULL, screen, &rect);
			} else if (timing >= 71 && timing <= 102) {
				rect.w = images[IMG_PUFFLE_BLACK_14]->w;
				rect.h = images[IMG_PUFFLE_BLACK_14]->h;
				
				SDL_BlitSurface (images[IMG_PUFFLE_BLACK_14], NULL, screen, &rect);
			} else if (timing >= 103 && timing <= 106) {
				rect.w = images[IMG_PUFFLE_BLACK_15]->w;
				rect.h = images[IMG_PUFFLE_BLACK_15]->h;
				
				SDL_BlitSurface (images[IMG_PUFFLE_BLACK_15], NULL, screen, &rect);
			} else if (timing >= 107 && timing <= 244) {
				rect.w = images[IMG_PUFFLE_BLACK_16]->w;
				rect.h = images[IMG_PUFFLE_BLACK_16]->h;
				
				SDL_BlitSurface (images[IMG_PUFFLE_BLACK_16], NULL, screen, &rect);
			}
			
			switch (timing) {
				case 61:
					rect.x = 309;
					rect.y = 246;
					rect.w = images[IMG_PUFFLE_BLACK_10]->w;
					rect.h = images[IMG_PUFFLE_BLACK_10]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_10], NULL, screen, &rect);
					
					rect.x = 358;
					rect.y = 230;
					rect.w = images[IMG_PUFFLE_OFF_2]->w;
					rect.h = images[IMG_PUFFLE_OFF_2]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_2], NULL, screen, &rect);
					break;
				case 62:
					rect.x = 309;
					rect.y = 246;
					rect.w = images[IMG_PUFFLE_BLACK_11]->w;
					rect.h = images[IMG_PUFFLE_BLACK_11]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_11], NULL, screen, &rect);
					
					rect.x = 358;
					rect.y = 230;
					rect.w = images[IMG_PUFFLE_OFF_2]->w;
					rect.h = images[IMG_PUFFLE_OFF_2]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_2], NULL, screen, &rect);
					break;
				case 63:
					rect.x = 309;
					rect.y = 246;
					rect.w = images[IMG_PUFFLE_BLACK_12]->w;
					rect.h = images[IMG_PUFFLE_BLACK_12]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_12], NULL, screen, &rect);
					
					rect.x = 364;
					rect.y = 216;
					rect.w = images[IMG_PUFFLE_OFF_3]->w;
					rect.h = images[IMG_PUFFLE_OFF_3]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_3], NULL, screen, &rect);
					break;
				case 64:
					rect.x = 364;
					rect.y = 216;
					rect.w = images[IMG_PUFFLE_OFF_3]->w;
					rect.h = images[IMG_PUFFLE_OFF_3]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_3], NULL, screen, &rect);
					break;
				case 65:
				case 66:
					rect.x = 364;
					rect.y = 210;
					rect.w = images[IMG_PUFFLE_OFF_4]->w;
					rect.h = images[IMG_PUFFLE_OFF_4]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_4], NULL, screen, &rect);
					break;
				case 67:
				case 68:
					rect.x = 364;
					rect.y = 204;
					rect.w = images[IMG_PUFFLE_OFF_5]->w;
					rect.h = images[IMG_PUFFLE_OFF_5]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_5], NULL, screen, &rect);
					break;
				case 69:
				case 70:
					rect.x = 362;
					rect.y = 192;
					rect.w = images[IMG_PUFFLE_OFF_6]->w;
					rect.h = images[IMG_PUFFLE_OFF_6]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_6], NULL, screen, &rect);
					break;
				case 71:
				case 72:
					rect.x = 366;
					rect.y = 192;
					rect.w = images[IMG_PUFFLE_OFF_7]->w;
					rect.h = images[IMG_PUFFLE_OFF_7]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_7], NULL, screen, &rect);
					break;
				case 73:
				case 74:
					rect.x = 362;
					rect.y = 186;
					rect.w = images[IMG_PUFFLE_OFF_8]->w;
					rect.h = images[IMG_PUFFLE_OFF_8]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_8], NULL, screen, &rect);
					break;
				case 75:
				case 76:
					rect.x = 358;
					rect.y = 182;
					rect.w = images[IMG_PUFFLE_OFF_9]->w;
					rect.h = images[IMG_PUFFLE_OFF_9]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_9], NULL, screen, &rect);
					break;
				case 77:
				case 78:
					rect.x = 360;
					rect.y = 178;
					rect.w = images[IMG_PUFFLE_OFF_10]->w;
					rect.h = images[IMG_PUFFLE_OFF_10]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_OFF_10], NULL, screen, &rect);
					break;
			}
		} else {
			rect.x = 309;
			rect.y = 246;
			if (end != 3) {
				image = (end == 1) ? IMG_PUFFLE_BLACK_END1_1 : IMG_PUFFLE_BLACK_END2_1;
				if (timing >= 245 && timing <= 247) {
					rect.w = images[image + 0]->w;
					rect.h = images[image + 0]->h;
					
					SDL_BlitSurface (images[image + 0], NULL, screen, &rect);
				} else if (timing >= 248 && timing <= 277) {
					rect.w = images[image + 1]->w;
					rect.h = images[image + 1]->h;
					
					SDL_BlitSurface (images[image + 1], NULL, screen, &rect);
				} else if (timing == 278 || timing == 279) {
					rect.w = images[image + 2]->w;
					rect.h = images[image + 2]->h;
					
					SDL_BlitSurface (images[image + 2], NULL, screen, &rect);
				} else {
					rect.w = images[image + 3]->w;
					rect.h = images[image + 3]->h;
					
					SDL_BlitSurface (images[image + 3], NULL, screen, &rect);
				}
			} else if (end == 3) {
				if (timing >= 240 && timing <= 242) {
					rect.w = images[IMG_PUFFLE_BLACK_END3_1]->w;
					rect.h = images[IMG_PUFFLE_BLACK_END3_1]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_END3_1], NULL, screen, &rect);
				} else if (timing >= 243 && timing <= 272) {
					rect.w = images[IMG_PUFFLE_BLACK_END3_2]->w;
					rect.h = images[IMG_PUFFLE_BLACK_END3_2]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_END3_2], NULL, screen, &rect);
				} else if (timing >= 273 && timing <= 277) {
					rect.w = images[IMG_PUFFLE_BLACK_END3_3]->w;
					rect.h = images[IMG_PUFFLE_BLACK_END3_3]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_END3_3], NULL, screen, &rect);
				} else {
					rect.w = images[IMG_PUFFLE_BLACK_END3_4]->w;
					rect.h = images[IMG_PUFFLE_BLACK_END3_4]->h;
					
					SDL_BlitSurface (images[IMG_PUFFLE_BLACK_END3_4], NULL, screen, &rect);
				}
			}
		}
		
		/* Dibujar los textos */
		if (timing > 91) {
			rect.x = 158;
			rect.y = 32;
			rect.w = texts_finish[0]->w;
			rect.h = texts_finish[0]->h;
			
			SDL_BlitSurface (texts_finish[0], NULL, screen, &rect);
			
			rect.x = 410 + (175 - numero[0]->w);
			rect.y = 32;
			rect.w = numero[0]->w;
			rect.h = numero[0]->h;
			
			SDL_BlitSurface (numero[0], NULL, screen, &rect);
		}
		
		if (timing > 111) {
			rect.x = 158;
			rect.y = 57;
			rect.w = texts_finish[1]->w;
			rect.h = texts_finish[1]->h;
			
			SDL_BlitSurface (texts_finish[1], NULL, screen, &rect);
			
			rect.x = 410 + (175 - numero[1]->w);
			rect.y = 57;
			rect.w = numero[1]->w;
			rect.h = numero[1]->h;
			
			SDL_BlitSurface (numero[1], NULL, screen, &rect);
		}
		
		if (timing > 131) {
			rect.x = 158;
			rect.y = 82;
			rect.w = texts_finish[2]->w;
			rect.h = texts_finish[2]->h;
			
			SDL_BlitSurface (texts_finish[2], NULL, screen, &rect);
			
			rect.x = 410 + (175 - numero[2]->w);
			rect.y = 82;
			rect.w = numero[2]->w;
			rect.h = numero[2]->h;
			
			SDL_BlitSurface (numero[2], NULL, screen, &rect);
		}
		
		if (timing > 151) {
			rect.x = 158 + (427 - texts_finish[3]->w) / 2;
			rect.y = 132;
			rect.w = texts_finish[3]->w;
			rect.h = texts_finish[3]->h;
			
			SDL_BlitSurface (texts_finish[3], NULL, screen, &rect);
			
			rect.x = 158 + (427 - numero[3]->w) / 2;
			rect.y = 156;
			rect.w = numero[3]->w;
			rect.h = numero[3]->h;
			
			SDL_BlitSurface (numero[3], NULL, screen, &rect);
		}
		
		if (timing > 171) {
			rect.x = 158;
			rect.y = 288;
			rect.w = texts_finish[5]->w;
			rect.h = texts_finish[5]->h;
			
			SDL_BlitSurface (texts_finish[5], NULL, screen, &rect);
			
			rect.x = 410 + (175 - numero[5]->w);
			rect.y = 288;
			rect.w = numero[5]->w;
			rect.h = numero[5]->h;
			
			SDL_BlitSurface (numero[5], NULL, screen, &rect);
		}
		
		if (timing > 191) {
			rect.x = 158;
			rect.y = 314;
			rect.w = texts_finish[6]->w;
			rect.h = texts_finish[6]->h;
			
			SDL_BlitSurface (texts_finish[6], NULL, screen, &rect);
			
			rect.x = 410 + (175 - numero[6]->w);
			rect.y = 314;
			rect.w = numero[6]->w;
			rect.h = numero[6]->h;
			
			SDL_BlitSurface (numero[6], NULL, screen, &rect);
		}
		
		if (end == 3 && timing > 211) {
			rect.x = 158 + (427 - texts_finish[4]->w) / 2;
			rect.y = 205;
			rect.w = texts_finish[4]->w;
			rect.h = texts_finish[4]->h;
			
			SDL_BlitSurface (texts_finish[4], NULL, screen, &rect);
			
			rect.x = 158 + (427 - numero[4]->w) / 2;
			rect.y = 230;
			rect.w = numero[4]->w;
			rect.h = numero[4]->h;
			
			SDL_BlitSurface (numero[4], NULL, screen, &rect);
		}
		
		timing++;
		/* El botón de cierre */
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 663; rect.y = 24;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images[IMG_ARCADE], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		/* El botón de get coins */
		if (cp_button_refresh[BUTTON_GET_COINS]) {
			rect.x = 455; rect.y = 400;
			rect.w = images[IMG_BUTTON_3_UP]->w; rect.h = images[IMG_BUTTON_3_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_GET_COINS]], NULL, screen, &rect);
			rects[num_rects++] = rect;
			
			rect.x = 455 + (rect.w - get_coins_text_button->w) / 2;
			rect.y = 400 + (rect.h - get_coins_text_button->h) / 2;
			rect.w = get_coins_text_button->w; rect.h = get_coins_text_button->h;

			SDL_BlitSurface (get_coins_text_button, NULL, screen, &rect);
			cp_button_refresh[BUTTON_GET_COINS] = 0;
		}
		
		SDL_UpdateRects (screen, num_rects, rects);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
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
	
	use_sound = 1;
	if (SDL_InitSubSystem (SDL_INIT_AUDIO) < 0) {
		fprintf (stdout,
			"Warning: Can't initialize the audio subsystem\n"
			"Continuing...\n");
		use_sound = 0;
	}
	
	if (use_sound) {
		/* Inicializar el sonido */
		if (Mix_OpenAudio (22050, AUDIO_S16, 2, 4096) < 0) {
			fprintf (stdout,
				"Warning: Can't initialize the SDL Mixer library\n");
			use_sound = 0;
		} else {
			Mix_AllocateChannels (3);
		}
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
	
	if (use_sound) {
		for (g = 0; g < NUM_SOUNDS; g++) {
			sounds[g] = Mix_LoadWAV (sound_names [g]);
			
			if (sounds[g] == NULL) {
				fprintf (stderr,
					"Failed to load data file:\n"
					"%s\n"
					"The error returned by SDL is:\n"
					"%s\n", sound_names [g], SDL_GetError ());
				SDL_Quit ();
				exit (1);
			}
			Mix_VolumeChunk (sounds[g], MIX_MAX_VOLUME / 2);
		}
		
		/* Cargar la música */
		music_intro = Mix_LoadMUS (MUS_INTRO);
		music_thinice = Mix_LoadMUS (MUS_THINICE);
		
		if (music_intro == NULL || music_thinice == NULL) {
			fprintf (stderr,
				"Failed to load a music file.\n"
				"The error returned by SDL is:\n"
				"%s\n", SDL_GetError ());
			SDL_Quit ();
			exit (1);
		}
	}
	
	if (TTF_Init () < 0) {
		fprintf (stderr,
			"Error: Can't initialize the SDL TTF library\n"
			"%s\n", TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	ttf13_burbank_bold = TTF_OpenFont (GAMEDATA_DIR "burbanksb.ttf", 13);
	
	if (!ttf13_burbank_bold) {
		fprintf (stderr,
			"Failed to load font file 'Burbank Small Bold'\n"
			"The error returned by SDL is:\n"
			"%s\n", TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	TTF_SetFontHinting (ttf13_burbank_bold, TTF_HINTING_LIGHT);
	
	ttf13_burbank_small = TTF_OpenFont (GAMEDATA_DIR "burbanksb.ttf", 13);
	
	if (!ttf13_burbank_small) {
		fprintf (stderr,
			"Failed to load font file 'Burbank Small Bold'\n"
			"The error returned by SDL is:\n"
			"%s\n", TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	TTF_SetFontStyle (ttf13_burbank_bold, TTF_STYLE_BOLD);
	
	ttf13_big_black = TTF_OpenFont (GAMEDATA_DIR "burbankbgbk.ttf", 13);
	
	if (!ttf13_big_black) {
		fprintf (stderr,
			"Failed to load font file 'Burbank Big Regular Black'\n"
			"The error returned by SDL is:\n"
			"%s\n", TTF_GetError ());
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

void area_secreta (int (*mapa)[19], int (*frames)[19], int solved_stages) {
	/* Muro */
	mapa[2][13] = mapa[11][16] = mapa[11][18] = mapa[10][18] =
	mapa[9][18] = mapa[8][18] = mapa[7][18] = 20;
	frames[2][13] = frames[11][16] = frames[11][18] = frames[10][18] =
	frames[9][18] = frames[8][18] = frames[7][18] = tiles_start[20];
	
	/* Hielo */
	mapa[3][13] = mapa[9][14] = mapa[7][14] = mapa[5][14] = mapa[3][14] =
	mapa[1][14] = mapa[10][15] = mapa[8][15] = mapa[6][15] = mapa[4][15] =
	mapa[2][15] = mapa[10][16] = mapa[9][16] = mapa[7][16] = mapa[5][16] =
	mapa[3][16] = mapa[1][16] = mapa[12][17] = mapa[11][17] = mapa[10][17] =
	mapa[8][17] = mapa[6][17] = mapa[4][17] = mapa[2][17] = 2;
	frames[3][13] = frames[9][14] = frames[7][14] = frames[5][14] = frames[3][14] =
	frames[1][14] = frames[10][15] = frames[8][15] = frames[6][15] = frames[4][15] =
	frames[2][15] = frames[10][16] = frames[9][16] = frames[7][16] = frames[5][16] =
	frames[3][16] = frames[1][16] = frames[12][17] = frames[11][17] = frames[10][17] =
	frames[8][17] = frames[6][17] = frames[4][17] = frames[2][17] = tiles_start[2];
	
	/* El boton */
	mapa[13][17] = 3;
	frames[13][17] = tiles_start[15];
	
	/* Bolsas de dinero */
	if (solved_stages >= 1) {
		mapa[8][14] = 7;
		frames[8][14] = tiles_start[7];
	} else {
		mapa[8][14] = 2;
		frames[8][14] = tiles_start[2];
	}
	if (solved_stages >= 2) {
		mapa[6][14] = 7;
		frames[6][14] = tiles_start[7];
	} else {
		mapa[6][14] = 2;
		frames[6][14] = tiles_start[2];
	}
	if (solved_stages >= 3) {
		mapa[4][14] = 7;
		frames[4][14] = tiles_start[7];
	} else {
		mapa[4][14] = 2;
		frames[4][14] = tiles_start[2];
	}
	if (solved_stages >= 4) {
		mapa[2][14] = 7;
		frames[2][14] = tiles_start[7];
	} else {
		mapa[2][14] = 2;
		frames[2][14] = tiles_start[2];
	}
	if (solved_stages >= 9) {
		mapa[9][15] = 7;
		frames[9][15] = tiles_start[7];
	} else {
		mapa[9][15] = 2;
		frames[9][15] = tiles_start[2];
	}
	if (solved_stages >= 8) {
		mapa[7][15] = 7;
		frames[7][15] = tiles_start[7];
	} else {
		mapa[7][15] = 2;
		frames[7][15] = tiles_start[2];
	}
	if (solved_stages >= 7) {
		mapa[5][15] = 7;
		frames[5][15] = tiles_start[7];
	} else {
		mapa[5][15] = 2;
		frames[5][15] = tiles_start[2];
	}
	if (solved_stages >= 6) {
		mapa[3][15] = 7;
		frames[3][15] = tiles_start[7];
	} else {
		mapa[3][15] = 2;
		frames[3][15] = tiles_start[2];
	}
	if (solved_stages >= 5) {
		mapa[1][15] = 7;
		frames[1][15] = tiles_start[7];
	} else {
		mapa[1][15] = 2;
		frames[1][15] = tiles_start[2];
	}
	if (solved_stages >= 10) {
		mapa[8][16] = 7;
		frames[8][16] = tiles_start[7];
	} else {
		mapa[8][16] = 2;
		frames[8][16] = tiles_start[2];
	}
	if (solved_stages >= 11) {
		mapa[6][16] = 7;
		frames[6][16] = tiles_start[7];
	} else {
		mapa[6][16] = 2;
		frames[6][16] = tiles_start[2];
	}
	if (solved_stages >= 12) {
		mapa[4][16] = 7;
		frames[4][16] = tiles_start[7];
	} else {
		mapa[4][16] = 2;
		frames[4][16] = tiles_start[2];
	}
	if (solved_stages >= 13) {
		mapa[2][16] = 7;
		frames[2][16] = tiles_start[7];
	} else {
		mapa[2][16] = 2;
		frames[2][16] = tiles_start[2];
	}
	if (solved_stages >= 18) {
		mapa[9][17] = 7;
		frames[9][17] = tiles_start[7];
	} else {
		mapa[9][17] = 2;
		frames[9][17] = tiles_start[2];
	}
	if (solved_stages >= 17) {
		mapa[7][17] = 7;
		frames[7][17] = tiles_start[7];
	} else {
		mapa[7][17] = 2;
		frames[7][17] = tiles_start[2];
	}
	if (solved_stages >= 16) {
		mapa[5][17] = 7;
		frames[5][17] = tiles_start[7];
	} else {
		mapa[5][17] = 2;
		frames[5][17] = tiles_start[2];
	}
	if (solved_stages >= 15) {
		mapa[3][17] = 7;
		frames[3][17] = tiles_start[7];
	} else {
		mapa[3][17] = 2;
		frames[3][17] = tiles_start[2];
	}
	if (solved_stages >= 14) {
		mapa[1][17] = 7;
		frames[1][17] = tiles_start[7];
	} else {
		mapa[1][17] = 2;
		frames[1][17] = tiles_start[2];
	}
}

int map_button_in_opening (int x, int y) {
	if (x >= 324 && x < 421 && y >= 382 && y < 411) return BUTTON_START;
	if (x >= 663 && x < 692 && y >= 24 && y < 53) return BUTTON_CLOSE;
	return BUTTON_NONE;
}

int map_button_in_explain (int x, int y, int escena) {
	if (x >= 663 && x < 692 && y >= 24 && y < 53) return BUTTON_CLOSE;
	if (x >= 158 && x < 255 && y >= 382 && y < 411) return BUTTON_PLAY;
	if (escena > 1 && x >= 396 && x < 493 && y >= 382 && y < 411) return BUTTON_PREV;
	if (escena < 4 && x >= 496 && x < 592 && y >= 382 && y < 411) return BUTTON_NEXT;
	return BUTTON_NONE;
}

int map_button_in_game (int x, int y) {
	if (x >= 663 && x < 692 && y >= 24 && y < 53) return BUTTON_CLOSE;
	if (x >= 155 && x < 244 && y >= 410 && y < 429) return BUTTON_RESET;
	return BUTTON_NONE;
}

int map_button_in_finish (int x, int y) {
	if (x >= 663 && x < 692 && y >= 24 && y < 53) return BUTTON_CLOSE;
	if (x >= 455 && x < 597 && y >= 400 && y < 429) return BUTTON_GET_COINS;
	return BUTTON_NONE;
}
