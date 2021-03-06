#include "pebble.h"
#include "character.h"
#include "battle.h"

#define NUM_BATTLE_MENU_SECTIONS 1
#define NUM_BATTLE_MENU_ITEMS 11
  
Window* window;
Window* skill_window;

TextLayer* battle_text_layer;

SimpleMenuLayer *battle_menu_layer;
SimpleMenuSection battle_menu_sections[NUM_BATTLE_MENU_SECTIONS];
SimpleMenuItem battle_menu_items[NUM_BATTLE_MENU_ITEMS];

char* my_text;
char* enemy_text;
bool showing_my_text;
char* skills[11];
char* mana[11];

Character character;
Character enemy;
Character backup;

void battle_menu_select_callback(int index, void *ctx){
  if(enemy.d > character.d){
    int hurt = enemy.damage - character.ac;
    if(hurt < 1)
      hurt = 1;
    character.health -= hurt;
    if(character.health <= 0){
      restore(&character, &backup);
      character.health++;
      character.xp = 0;
      //deinit_skill_window();
      //deinit_battle_window();
      //window_stack_pop(true);
      text_layer_set_text(battle_text_layer, "You died.\nLose all current experience.");
      window_set_click_config_provider(window, exit_config_provider);
      restore(&backup, &character);
    }
  }
  
  if(index == 0){
    int dam = character.damage - enemy.ac;
    if(dam < 1)
      dam = 1;
    enemy.health -= dam;
  }
  else if(index == 1){
    if(character.class == 0){
      if(character.mana >= 3){
        character.mana -= 3;
        int dam = character.damage - enemy.ac;
        if(dam < 1)
          dam = 1;
        dam *= 2;
        enemy.health -= dam;
      }      
    }
    else if(character.class == 1){
      if(character.mana >= 2){
        character.mana -= 2;
        enemy.damage -= character.d/5;
      }
    }
    else if(character.class == 2){
      if(character.mana >= 2){
        character.mana -= 2;
        enemy.health -= character.s/5;
      }
    }
  }
  else if (index == 2) {
    if(character.class == 0){
      if(character.mana >= 3){
        character.mana -= 3;
        int dam = character.damage/2 - enemy.ac;
        if(dam < 1)
          dam = 1;
        enemy.health -= dam;
        character.health += character.p/4;
      }
    }
    else if(character.class == 1){
      if(character.mana >= 2){
        character.mana -= 2;
        enemy.ac -= character.d/5;
        int dam = character.d/4 - enemy.ac;
        if(dam < 1)
          dam = 1;
        enemy.health -= dam;
      }
    }
    else if(character.class == 2){
      if(character.mana >= 3){
        character.mana -= 3;
        int dam = character.s/2 - enemy.ac;
        if(dam < 1)
          dam = 1;
        enemy.health -= dam;
      }
    }
  }
  else if (index == 3) {
    character.damage += character.level/3;
  }
  else if (index == 4) {
    if(character.class == 0){
      if(character.mana >= 3){
        character.mana -= 3;
        character.damage += character.p/4;
        int dam = character.damage - enemy.ac;
        if(dam < 1)
          dam = 1;
        enemy.health -= dam;
      }
    }
    else if(character.class == 1){
      if(character.mana >= 1){
        character.mana -= 1;
        character.mana += character.d/4;
        enemy.mana -= character.d/4;
      }
    }
    else if(character.class == 2){
      if(character.mana >= 4){
        character.mana -= 4;
        int dam = character.s/5 - enemy.ac;
        if(dam < 1)
          dam = 1;
        character.health += dam;
        enemy.health -= dam;
      }
    }
  }
  else if (index == 5) {
    character.mana += character.level/2;
  }
  else if (index == 6) {
    if(character.class == 0){
      if(character.mana >= 5){
        character.mana -= 5;
        character.ac += character.p/2;
      }
    }
    else if(character.class == 1){
      if(character.mana >= 5){
        character.mana -= 5;
        character.ac += character.d/2;
        character.health += character.ac;
      }
    }
    else if(character.class == 2){
      if(character.mana >= 5){
        character.mana -= 5;
        character.health += character.s/2;
      }
    }
  }
  else if (index == 7) {
    character.health += character.level/2;
  }
  else if (index == 8) {
    if(character.class == 0){
      if(character.mana >= 5){
        character.mana -= 5;
        int temp = backup.health - character.health;
        if (temp < 1)
          temp = 1;
        int dam = temp + character.p/2 - enemy.ac;
          if (dam < 1)
            dam = 1;
        enemy.health -= dam;
      }
    }
    else if(character.class == 1){
      if(character.mana >= 2){
        character.mana -= 2;
        enemy.p -= character.d/4;
        enemy.d -= character.d/4;
        enemy.s -= character.d/4;
      }
    }
    else if(character.class == 2){
      if(character.mana >= 6){
        character.mana -= 6;
        int dam = character.s/3 - enemy.ac;
        if(dam < 1)
          dam = 1;
        dam *= 3;
        enemy.health -= dam;
      }
    }
  }
  else if (index == 9) {
    character.d += character.level/2;
    character.p += character.level/2;
    character.s += character.level/2;
  }
  else if (index == 10) {
    if(character.class == 0){
      if(character.mana >= 8){
        character.mana -= 8;
        int dam = character.p - (enemy.ac)*2;
        if(dam < 1)
          dam = 1;
        enemy.health -= dam;
      }
    }
    else if(character.class == 1){
      if(character.mana >= 8){
        character.mana -= 8;
        int dam = character.d/3;
        if (dam < 1)
          dam = 1;
        character.p += character.d/4;
        character.d += character.d/4;
        character.s += character.d/4;
        enemy.health -= dam;
      }
    }
    else if(character.class == 2){
      if(character.mana >= 8){
        character.mana -= 8;
        int dam = character.s/2;
        if(dam < 1)
          dam = 1;
        enemy.health -= dam;
      }
    }
  }
  
  if(enemy.health <= 0){
    restore(&character, &backup);
    character.health++;
    character.xp += enemy.xp;
    if(character.xp >= 10*character.level){
      character.xp -= 10*character.level;
      levelUp(&character);
    }
    text_layer_set_text(battle_text_layer, "You Win.\nGain some experience.");
    window_set_click_config_provider(window, exit_config_provider);
    restore(&backup, &character);
  }

  
  if(enemy.d <= character.d){
    int hurt = enemy.damage - character.ac;
    if(hurt < 1)
      hurt = 1;
    character.health -= hurt;
    if(character.health <= 0){
      restore(&character, &backup);
      character.health++;
      character.xp = 0;
      //deinit_skill_window();
      //deinit_battle_window();
      //window_stack_pop(true);
      text_layer_set_text(battle_text_layer, "You died.\nLose all current experience.");
      window_set_click_config_provider(window, exit_config_provider);
      restore(&backup, &character);
    }
    
  }
  
  free(my_text);
  free(enemy_text);
  my_text = (char*)malloc(256*sizeof(char));
  enemy_text = (char*)malloc(256*sizeof(char));
  
  snprintf(my_text, 256, "%s   %s-%d\n------------------------\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d   Damage: %d\n\n\n", 
          "Pebble", setClassname(character), character.level, character.health, character.mana, character.p, character.d, character.s,  
           character.ac, character.damage);

  snprintf(enemy_text, 256, "%s   %s-%d\n------------------------\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d   Damage: %d\n\n\n", 
           "Enemy", setClassname(enemy), enemy.level, enemy.health, enemy.mana, enemy.p, enemy.d, enemy.s, enemy.ac, enemy.damage);

  window_stack_pop(true);
}

void battle_menu_create(){  
  GRect bounds = layer_get_frame(window_get_root_layer(skill_window));
  int num_a_items = 0;
  
  // SKILL 0: ATTACK
  //char* a = (char*)malloc(16*sizeof(char));
  skills[0] = (char*)malloc(16*sizeof(char*));
  snprintf(skills[0], 16, "%s", getSkill(character, 0));
  //char* sa = (char*)malloc(7*sizeof(char));
  mana[0] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[0], 8, "Mana: %d", getManaCost(character, 0));
  //mana[0] = getManaCost(character, 0);
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[0],
    .subtitle = mana[0],
    .callback = battle_menu_select_callback,
  };
  //free(a);
  
  // SKILL 1
  skills[1] = (char*)malloc(16*sizeof(char));
  snprintf(skills[1], 16, "%s", getSkill(character, 1));
  //char* sb = (char*)malloc(7*sizeof(char));
  mana[1] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[1], 8, "Mana: %d", getManaCost(character, 1));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[1],
    .subtitle = mana[1],
    .callback =  battle_menu_select_callback,
  };
  //free(b);
  
  // SKIL 2
  skills[2] = (char*)malloc(16*sizeof(char));
  snprintf(skills[2], 16, "%s", getSkill(character, 2));
  //char* sc = (char*)malloc(7*sizeof(char));
  //snprintf(sc, 7, "Mana %d", getManaCost(character, 2));
  mana[2] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[2], 8, "Mana: %d", getManaCost(character, 2));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[2],
    .subtitle = mana[2],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 3
  skills[3] = (char*)malloc(16*sizeof(char));
  snprintf(skills[3], 16, "%s", getSkill(character, 3));
  //char* sd = (char*)malloc(7*sizeof(char));
  //snprintf(sd, 7, "Mana %d", getManaCost(character, 3));
  mana[3] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[3], 8, "Mana: %d", getManaCost(character, 3));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[3],
    .subtitle = mana[3],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 4
  skills[4] = (char*)malloc(16*sizeof(char));
  snprintf(skills[4], 16, "%s", getSkill(character, 4));
  //char* se = (char*)malloc(7*sizeof(char));
  //snprintf(se, 7, "Mana %d", getManaCost(character, 4));
  mana[4] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[4], 8, "Mana: %d", getManaCost(character, 4));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[4],
    .subtitle = mana[4],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 5
  skills[5] = (char*)malloc(16*sizeof(char));
  snprintf(skills[5], 16, "%s", getSkill(character, 5));
  //char* sf = (char*)malloc(7*sizeof(char));
  //snprintf(sf, 7, "Mana %d", getManaCost(character, 5));
  mana[5] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[5], 8, "Mana: %d", getManaCost(character, 5));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[5],
    .subtitle = mana[5],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 6
  skills[6] = (char*)malloc(16*sizeof(char));
  snprintf(skills[6], 16, "%s", getSkill(character, 6));
  //char* sg = (char*)malloc(7*sizeof(char));
  //snprintf(sg, 7, "Mana %d", getManaCost(character, 6));
  mana[6] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[6], 8, "Mana: %d", getManaCost(character, 6));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[6],
    .subtitle = mana[6],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 7
  skills[7] = (char*)malloc(16*sizeof(char));
  snprintf(skills[7], 16, "%s", getSkill(character, 7));
  //char* sh = (char*)malloc(7*sizeof(char));
  //snprintf(sh, 7, "Mana %d", getManaCost(character, 7));
  mana[7] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[7], 8, "Mana: %d", getManaCost(character, 7));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[7],
    .subtitle = mana[7],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 8
  skills[8] = (char*)malloc(16*sizeof(char));
  snprintf(skills[8], 16, "%s", getSkill(character, 8));
  //char* si = (char*)malloc(7*sizeof(char));
  //snprintf(si, 7, "Mana %d", getManaCost(character, 8));
  mana[8] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[8], 8, "Mana: %d", getManaCost(character, 8));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[8],
    .subtitle = mana[8],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 9
  skills[9] = (char*)malloc(16*sizeof(char));
  snprintf(skills[9], 16, "%s", getSkill(character, 9));
  //char* sj = (char*)malloc(7*sizeof(char));
  //snprintf(sj, 7, "Mana %d", getManaCost(character, 9));
  mana[9] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[9], 8, "Mana: %d", getManaCost(character, 9));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[9],
    .subtitle = mana[9],
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 10
  skills[10] = (char*)malloc(16*sizeof(char));
  snprintf(skills[10], 16, "%s", getSkill(character, 10));
  //char* sk = (char*)malloc(7*sizeof(char));
  //snprintf(sk, 7, "Mana %d", getManaCost(character, 10));
  mana[10] = (char*)malloc(8*sizeof(char*));
  snprintf(mana[10], 8, "Mana: %d", getManaCost(character, 10));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = skills[10],
    .subtitle = mana[10],
    .callback = battle_menu_select_callback,
  };
  
  battle_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_BATTLE_MENU_ITEMS,
    .items = battle_menu_items,
  };
  
  /*free(sa);
  free(sb);
  free(sc);
  free(sd);
  free(se);
  free(sf);
  free(sg);
  free(sh);
  free(si);
  free(sj);
  free(sk);*/
  /*
  int x;
  for(x = 0; x <= 10; x++){
    free(skills[x]);
  }
  */
  battle_menu_layer = simple_menu_layer_create(bounds, skill_window, battle_menu_sections, NUM_BATTLE_MENU_SECTIONS, NULL);
}


void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(showing_my_text){
    text_layer_set_text(battle_text_layer, enemy_text);
    showing_my_text = false;
  }
  else{
    text_layer_set_text(battle_text_layer, my_text);
    showing_my_text = true;
  }
}

void battle_select_click_handler(ClickRecognizerRef recognizer, void *context){
  skill_window = window_create();
  
  window_set_window_handlers(window, (WindowHandlers) {
    //.load = window_load,
    //.appear = window_appear,
    //.disappear = window_disappear,
    .unload = deinit_skill_window
  });
  

  battle_menu_create();
  layer_add_child(window_get_root_layer(skill_window), simple_menu_layer_get_layer(battle_menu_layer));
  window_stack_push(skill_window, true);
}

void exit_click_handler(ClickRecognizerRef recognizer, void *context){
    window_stack_pop(true);
}


void battle_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, battle_select_click_handler);
 }
  
void exit_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_UP, exit_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, exit_click_handler);
}


Window* create_battle_window(Character c){
  character = c;
  backup = c;
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_battle_window
    });
  
  enemy = (Character)generate_enemy(character);
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  battle_text_layer = text_layer_create(bounds);
  
  my_text = (char*)malloc(256*sizeof(char));
  snprintf(my_text, 256, "%s   %s-%d\n------------------------\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d   Damage: %d\n\n\n", 
          "Pebble", setClassname(character), character.level, character.health, character.mana, character.p, character.d, character.s,  
           character.ac, character.damage);

  enemy_text = (char*)malloc(256*sizeof(char));
  snprintf(enemy_text, 256, "%s   %s-%d\n------------------------\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d   Damage: %d\n\n\n", 
           "Enemy", setClassname(enemy), enemy.level, enemy.health, enemy.mana, enemy.p, enemy.d, enemy.s, enemy.ac, enemy.damage);
 
  text_layer_set_text(battle_text_layer, my_text);
  text_layer_set_font(battle_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(battle_text_layer, GTextAlignmentLeft);
 
  layer_add_child(window_layer, text_layer_get_layer(battle_text_layer));
  
  window_set_click_config_provider(window, battle_config_provider);

  return window;
}

Character generate_enemy(){
  srand(time(NULL));
  Character enemy;
  int eclass = rand()%3;
  int elevel = character.difficulty;
  int pds = 2+elevel;
  enemy = (Character){eclass, elevel, 10+5*character.difficulty, 0, 0, pds, pds, pds, 0, 0, 0};
  levelUp(&enemy);
  return enemy;
}

void deinit_skill_window(){
  simple_menu_layer_destroy(battle_menu_layer);
  
  int x;
  for(x = 0; x <= 10; x++){
    free(skills[x]);
    free(mana[x]);
  }
  
  //free(skills);
  window_destroy(skill_window);
}

void deinit_battle_window(){
  free(my_text);
  free(enemy_text);
  text_layer_destroy(battle_text_layer);
  window_destroy(window);
}