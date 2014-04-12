#include "pebble.h"
#include "character.h"
#include "battle.h"

Window* window;
  
Window* create_battle_window(){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_battle_window
    });
  
  Character enemy = (Character)generate_enemy();
  return window;
}

Character generate_enemy(){
  Character enemy;
  return enemy;
}