//
//  monkey.c
//  Monkey
//
//  Created by Blake Lockley on 28/11/2016.
//  Copyright © 2016 Blake Lockley. All rights reserved.
//

#include "monkey.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void crossover(monkey_t *mother, monkey_t *father, monkey_t *child, char *target) {
  int i, m = 0, f = 0, mut, len;
  char c;
  
  len = (int) strlen(target);
  
  for (i = 0; i < len; i++) {
    if (f > 2 || (rand() % 2 == 0 && m++ < 2))
      child->letters[i] = mother->letters[i];
    else {
      child->letters[i] = father->letters[i];
      f++;
    }
    
    //mutation
    mut = 0;
    
    //1/3 ^ n chance to mutate the character by n
    while (rand() % 3 == 0)
      mut++;
    
    //mutation increase or decrease the character
    if (rand() % 2 == 0)
      mut *= -1;
    
    c = child->letters[i] + mut;
    if (c < 'a')
      c = 'a';
    else if (c > 'z')
      c = ' ';
    child->letters[i] = c;
  }
  
  child->fitness = fitness(child, target);
}

double round_to(double n, int places) {
  double m = pow(10, places);
  return round(n * m) / m;
}

double fitness(monkey_t *monkey, char *target) {
  char *expected = target, *actual = monkey->letters, temp_e, temp_a;
  double total = 0.0, d = 1.0 / strlen(target);
  
  for (; *expected && *actual; expected++, actual++) {
    temp_e = *expected;
    temp_a = *actual;
    
    if (temp_e == ' ')
      temp_e = 'z' + 1;
    if (temp_a == ' ')
      temp_a = 'z' + 1;
    
    total += (1 - abs(temp_e - temp_a) / 26.0) * d;
  }
  
  return round_to(pow(total, 2), 6);
}

int compare_monkey(const void *a, const void *b) {
  monkey_t *ma = (monkey_t *) *(void **) a, *mb = (monkey_t *) *(void **) b;
  if (ma->fitness < mb->fitness)
    return -1;
  if (ma->fitness > mb->fitness)
    return 1;
  return 0;
}
