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
