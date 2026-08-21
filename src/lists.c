#include <stdlib.h>
#include "sprites.h"
#include "lists.h"

Sprite_list_node *sprite_list;
Hitbox_list_node *hitbox_list;

void init_sprite_list() {
  sprite_list = malloc(sizeof(Sprite_list_node));
}

void init_hitbox_list() {
  hitbox_list = malloc(sizeof(Hitbox_list_node));
}

void add_sprite(Sprite_list_node *start_node, Object_sprite *sprite) {
  Sprite_list_node *node = start_node;

  while (node->next != NULL) {
    node = node->next;
  }

  node->sprite = sprite;
  node->next = malloc(sizeof(Sprite_list_node));
}

void add_hitbox(Hitbox_list_node *start_node, Object_hitbox *hitbox) {
  Hitbox_list_node *node = start_node;

  while (node->next != NULL) {
    node = node->next;
  }

  node->hitbox = hitbox;
  node->next = malloc(sizeof(Hitbox_list_node));
}
