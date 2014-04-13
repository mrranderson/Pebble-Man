#include "character.h"
  
int getAC(Character c) {
  c.ac = c.d / 3;
  return c.ac;
}

int getDamage(Character c) {
  if (c.class == 0)
    c.damage = c.p / 2;
  else if (c.class == 1)
    c.damage = c.d / 2;
  else
    c.damage = c.s / 2;
  return c.damage;
}

char* setClassname(Character c) {
  if (c.class == 0) return "Fighter";
  else if (c.class == 1) return "Rogue";
  else return "Mage";
}

void levelUp(Character* c){
  c->level++;
  c->s++;
  c->p++;
  c->d++;
  if(c->level == 1 || c->level % 3 == 0) {
    if(c->class == 0)
      c->p++;
    if(c->class == 1)
      c->d++;
    if(c->class == 2)
      c->s++;
  }
  c->damage = getDamage(*c);
  c->ac = getAC(*c);
  c->health=c->p + 2;
  c->mana=c->s + 2;
}

char* getSkill(Character c, int i) {
  char *f[11] = { "Attack", "1", "2", "Aim", "3", "Focus", "4", "First Aid", "5", "Paragon", "6" };
  if (c.class == 0) {
    f[1] = "Flurry";
    f[2] = "Warm Up";
    f[4] = "Rising Fury";
    f[6] = "Parry";
    f[8] = "Retaliate";
    f[10] = "Go For the Kill";
  }
  else if (c.class == 1) {
    f[1] = "Disarm";
    f[2] = "Low Blow";
    f[4] = "Spellthief";
    f[6] = "Evasion";
    f[8] = "Disable";
    f[10] = "Assassinate";
  }
  else {
    f[1] = "Magic Missle";
    f[2] = "Rock Blast";
    f[4] = "Absorb";
    f[6] = "Mana Shield";
    f[8] = "Avalanche";
    f[10] = "Disintegrate";
  }
  return f[i];
}

void restore(Character *original, Character *backup){
  original->health = backup->health;
  original->mana = backup->mana;
  original->p = backup->p;
  original->s = backup->s;
  original->d = backup->d;
  original->damage = backup->damage;
  original->ac = backup->ac;
}


