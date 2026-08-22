#ifndef LISTS_H
#define LISTS_H

#include "sprites.h"
#include "hitboxes.h"

typedef struct Sprite_list_node {
  Object_sprite *sprite;
  struct Sprite_list_node *next;
} Sprite_list_node;

typedef struct Hitbox_list_node {
  Object_hitbox *hitbox;
  struct Hitbox_list_node *next;
} Hitbox_list_node;

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

extern Sprite_list_node *sprite_list;
extern Hitbox_list_node *hitbox_list;

void init_lists(void);

void add_sprite(Object_sprite *sprite);

void delete_sprite(Object_sprite *sprite);

#endif
