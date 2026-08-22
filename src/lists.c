#include <stdio.h>
#include <stdlib.h>
#include "sprites.h"
#include "lists.h"

Sprite_list_node *sprite_list;
Hitbox_list_node *hitbox_list;

void init_lists() {
  sprite_list = malloc(sizeof(Sprite_list_node));
  hitbox_list = malloc(sizeof(Hitbox_list_node));
}

void add_node(Node *start_node, void *data, int data_size) {
  Node *node = start_node;

  while (node->next != NULL) {
    node = node->next;
  }

  node->data = data;
  node->next = malloc(data_size);
}

void add_sprite(Object_sprite *sprite) {
  add_node((Node *)sprite_list, sprite, sizeof(Sprite_list_node));
}

void delete_sprite(Object_sprite *sprite) {
  Sprite_list_node **current = &sprite_list;

  while ((*current)->next != NULL) {
    Sprite_list_node *node = *current;

    if (node->sprite == sprite) {
      *current = node->next;

      free(node->sprite->figure_sprite_t.sprite_arr);
      free(node->sprite);
      free(node);

      return;
    }

    current = &node->next;
  }
}
