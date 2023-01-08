#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <zmq.h>
#include <stdint.h>

#define WRONG_TURN -1

typedef enum 
{
    A,
    B,
    nothing
} point_t;

typedef enum side 
{
    top,
    right,
    bottom,
    left
} side_t;

typedef struct cell 
{
    unsigned char edges[4];
    point_t type;
} cell_t;

typedef struct turn 
{
    uint8_t x, y;
    side_t side;
} turn_t;

typedef struct field 
{
    cell_t** regiment;
    uint8_t size;
    char end;
} field_t;

typedef struct Message 
{
    turn_t turn;
    int id, req;
    point_t point;
    uint8_t size;
} Message_t;

field_t gen_field(uint8_t size);
void destroy_field(field_t F);

void show_field(field_t f);
int fix_field(point_t player, field_t* f);

void get_turn(uint8_t x, uint8_t y, side_t side, field_t f);
int try_turn(field_t* f, turn_t choice, point_t player);

void send_field(field_t field, void* requester);
void get_field(field_t* field, void* resiever);

#endif 

