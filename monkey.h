//
//  monkey.h
//  Monkey
//
//  Created by Blake Lockley on 28/11/2016.
//  Copyright © 2016 Blake Lockley. All rights reserved.
//

#ifndef monkey_h
#define monkey_h

#include <stdio.h>

typedef struct {
  char *letters;
  double fitness;
} monkey_t;

void crossover(monkey_t *, monkey_t *, monkey_t *, char *);
double fitness(monkey_t *, char *);
int compare_monkey(const void *, const void *);

#endif /* monkey_h */
