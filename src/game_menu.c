#include "pebble.h"
#include "main_menu.h"
#include "game_menu.h"
#include "character.h"
  
#define NUM_GAME_MENU_SECTIONS 1
#define NUM_GAME_MENU_ITEMS 4
#define NUM_CLASS_MENU_SECTIONS 1
#define NUM_CLASS_MENU_ITEMS 3
#define CLASS 678
#define LEVEL 679
#define HEALTH 680
#define MANA 681
#define P 682
#define D 683
#define S 684
  
Window *window;
Window *character_window;
Window *train_window;

int counter;
TextLayer* train_text_layer;

SimpleMenuLayer *game_menu_layer;
SimpleMenuSection game_menu_sections[NUM_GAME_MENU_SECTIONS];
static SimpleMenuItem game_menu_items[NUM_GAME_MENU_ITEMS];

TextLayer* character_text_layer;
ScrollLayer* scroll;
SimpleMenuLayer *class_menu_layer;
SimpleMenuSection class_menu_sections[NUM_CLASS_MENU_SECTIONS];
SimpleMenuItem class_menu_items[NUM_CLASS_MENU_ITEMS];

Character character;


void accel_tap_handler(AccelAxisType axis, int32_t direction) {
    character.xp += 1;
    //layer_mark_dirty(text_layer_get_layer(train_text_layer));
    //APP_LOG(0, "%d", character.level);
}

void accel_data_handler(AccelData *data, uint32_t num_samples) {
    counter+=1;
  if(counter == 100) {
    counter = 0;
    character.xp+=1;
    if(character.xp == 10*(character.level+1)){
      levelUp(&character);
      character.xp = 0;
    }
    //APP_LOG(0, "%d", character.xp);
  }
    //layer_mark_dirty(text_layer_get_layer(train_text_layer));
    
}

void game_menu_select_callback(int index, void *ctx) {
  //Train
  if(index == 0){
    //Train by walking around in the real world
    //Accelerometer
    train_window = window_create();
    window_set_window_handlers(train_window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_train_window,
    });
    train_text_layer = text_layer_create(GRect(0,0,144,154));
    char* h = (char*)malloc(128*sizeof(char));
    snprintf(h, 128, "\n\nTRAINING");
    
    text_layer_set_text(train_text_layer, h);
	  text_layer_set_font(train_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	  text_layer_set_text_alignment(train_text_layer, GTextAlignmentCenter);
    
    //layer_set_update_proc(text_layer_get_layer(train_text_layer), train_update_proc);
    
    layer_add_child(window_get_root_layer(train_window), text_layer_get_layer(train_text_layer));
    
    counter = 0;
    
    accel_data_service_subscribe(1, accel_data_handler);
    accel_tap_service_subscribe(accel_tap_handler);
    
    free(h);
    
    window_stack_push(train_window, true);
  }
  //Battle
  else if(index == 1){
    //Fight a randomly generated enemy based on the current difficulty
    //Character enemy;
    //enemy.class
  }
  //Character
  else if(index == 2){    
    //Display character stats
    character_window = window_create();
    TextLayer *character_text_layer = text_layer_create(GRect(0, 0, 144, 154));
    Layer *window_layer = window_get_root_layer(character_window);
    GRect bounds = layer_get_frame(window_layer);
    GRect max_text_bounds = GRect(0, 0, bounds.size.w, 2000);
    
    ScrollLayer *scroll = scroll_layer_create(bounds);
    scroll_layer_set_click_config_onto_window(scroll, character_window);
    
    character_text_layer = text_layer_create(max_text_bounds);
    char* h = (char*)malloc(256*sizeof(char));
    snprintf(h, 256, "ME\n%s-%d\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d \nDam: %d \n------------------------\nAbilities: \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s", 
             setClassname(character), character.level, character.health, character.mana, character.p, character.d, character.s,
             character.ac, character.damage,
             getSkill(character, 0), getSkill(character, 1), getSkill(character, 2), getSkill(character, 3), getSkill(character, 4), 
             getSkill(character, 5), getSkill(character, 6), getSkill(character, 7), getSkill(character, 8), getSkill(character, 9));
    text_layer_set_text(character_text_layer, h);
    text_layer_set_font(character_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	  text_layer_set_text_alignment(character_text_layer, GTextAlignmentLeft);
    
    GSize max_size = text_layer_get_content_size(character_text_layer);
    text_layer_set_size(character_text_layer, max_size);
    scroll_layer_set_content_size(scroll, GSize(bounds.size.w, max_size.h + 4));
    scroll_layer_add_child(scroll, text_layer_get_layer(character_text_layer));

	  layer_add_child(window_get_root_layer(character_window), scroll_layer_get_layer(scroll));
    
    window_set_window_handlers(character_window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_character_window,
    });

    window_stack_push(character_window, true);
  }
  //Settings
  else if(index == 3){
    //launch new window
    //come up with some settings
    
  }
  else{
    
  }
}


void game_menu_create(){  
  GRect bounds = layer_get_frame(window_get_root_layer(window));
  int num_a_items = 0;
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Train",
    .callback = game_menu_select_callback,
  };
  // The menu items appear in the order saved in the menu items array
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Battle",
    .callback = game_menu_select_callback,
  };
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Character",
    .callback = game_menu_select_callback,
  };
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Travel",
    .callback = game_menu_select_callback,
  };
  
  game_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_GAME_MENU_ITEMS,
    .items = game_menu_items,
  };

  game_menu_layer = simple_menu_layer_create(bounds, window, game_menu_sections, NUM_GAME_MENU_SECTIONS, NULL);
}

void class_menu_select_callback(int index, void *ctx){
  character = (Character){index, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  levelUp(&character);
  simple_menu_layer_destroy(class_menu_layer);
  game_menu_create();    
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(game_menu_layer));
}

void class_menu_create(){
  GRect bounds = layer_get_frame(window_get_root_layer(window));
  int num_a_items = 0;
  
  class_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Fighter",
    .callback = class_menu_select_callback,
  };
  // The menu items appear in the order saved in the menu items array
  class_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Rogue",
    .callback = class_menu_select_callback,
  };
  
  class_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Mage",
    .callback = class_menu_select_callback,
  };
  
  class_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_CLASS_MENU_ITEMS,
    .items = class_menu_items,
  };

  class_menu_layer = simple_menu_layer_create(bounds, window, class_menu_sections, NUM_CLASS_MENU_SECTIONS, NULL);

}

Window* create_game_window(bool cont){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_game_window
    });
  
  if(!cont){
    //create new character
    //choose a class
    class_menu_create();
    layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(class_menu_layer));
  }
  else{
    if(persist_exists(CLASS)){
      character.class = persist_read_int(CLASS);
      APP_LOG(0, "data is persisted");
    }
    if(persist_exists(LEVEL))
      character.level = persist_read_int(LEVEL);
    if(persist_exists(HEALTH))
      character.health = persist_read_int(HEALTH);
    if(persist_exists(MANA))
      character.mana = persist_read_int(MANA);
    if(persist_exists(P))
      character.p = persist_read_int(P);
    if(persist_exists(D))
      character.d = persist_read_int(D);
    if(persist_exists(S))
      character.s = persist_read_int(S);
    character.damage = getDamage(character);
    character.ac = getAC(character);

    game_menu_create();
    
    layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(game_menu_layer));
  }
  
  return window;
}

void save_data(){
  APP_LOG(0, "SAVING");
  persist_delete(CLASS);
  persist_write_int(CLASS, character.class);//character.class);
  bool write = persist_write_int(LEVEL, character.level);
  //if(write)
    //APP_LOG(0, "TRUE");
  persist_delete(HEALTH);
  persist_write_int(HEALTH, character.health);
  persist_write_int(MANA, character.mana);
  persist_write_int(P, character.p);
  persist_write_int(D, character.d);
  persist_write_int(S, character.s);
  char* log = (char*)malloc(6*sizeof(char*));
  int x = persist_read_int(CLASS);
  snprintf(log, 6, "%d", x);
  APP_LOG(0, log);
}

void deinit_train_window() {
  accel_tap_service_unsubscribe();
  accel_data_service_unsubscribe();
  window_destroy(train_window);
}

void deinit_character_window(){
  save_data();
  text_layer_destroy(character_text_layer);
  scroll_layer_destroy(scroll);
  window_destroy(character_window);
}

void deinit_game_window(){
  save_data();
	simple_menu_layer_destroy(game_menu_layer);
	// Destroy the window
	window_destroy(window);

}
