//
//  main.c
//  Monkey
//
//  Created by Blake Lockley on 28/11/2016.
//  Copyright © 2016 Blake Lockley. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "monkey.h"

void create_population(monkey_t **, char *);
void breed(monkey_t **, char *);
int validate_input(char *);

int main(int argc, const char * argv[]) {
  int found, i, n;
  monkey_t *monkey, *population[10];
  char target[80];
  
  srand((unsigned int) time(NULL));
  
  printf("Enter [q] to exit\n");
  
  while (1) {
    printf("Input: ");
    if (fgets(target, sizeof(target), stdin) == NULL) {
      fprintf(stderr, "Error on input\n");
      continue;
    }
    
    strtok(target, "\n");
    
    if (strcmp(target, "[q]") == 0)
      break;
    
    if (validate_input(target) == 0) {
      fprintf(stderr, "Use lowercase characters 'a' to 'z' and space only\n");
      continue;
    }
    
    create_population(population, target);
    
    //generations
    for (n = 1, found = 0; n <= 1000 && !found; n++) {
      
      //sort from least fit to most
      qsort(population, 10, sizeof(monkey_t *), compare_monkey);
      
      printf("Generation %d:\n", n);
      for (i = 0; i < 10; i++) {
        monkey = population[i];
        printf("%d: %s, %f\n", i, monkey->letters, monkey->fitness);
        if (monkey->fitness >= 1.0)
          found = 1;
      }
      
      //breed 5-9 into 0-4
      breed(population, target);
    }
    
  }
  
  return 0;
}

int validate_input(char* input) {
  char c;
  
  while ((c = *input++))
    if (!(c >= 'a' && c <= 'z') && c != ' ')
      return 0;
  return 1;
}

void create_population(monkey_t **population, char *target) {
  monkey_t *monkey;
  int i, n, len;
  
  len = (int) strlen(target);
  
  for (i = 0; i < 10; i++) {
    monkey = malloc(sizeof(monkey_t));
    monkey->letters = malloc(80);
    
    for (int j = 0; j < len; j++) {
      n = rand() % 27;
      if (n == 26)
        monkey->letters[j] = ' ';
      else
        monkey->letters[j] = 'a' + n;
    }
    monkey->letters[len] = '\0';
    
    monkey->fitness = fitness(monkey, target);
    population[i] = monkey;
  }
  
}

//probabilistic selection
void select_population(monkey_t **population) {
  int i, j, c, min, max, fit;
  monkey_t *temp;
  
  min = population[0]->fitness * 100;
  max = population[9]->fitness * 100;
  
  for (i = 9, c = 0; c < 4; i--) {
    if (i < 0)
      i = 9 - c;
    fit = population[i]->fitness * 100;
    if (fit >= min + (rand() % (max - min))) {
      //selected -> move to end of array
      for (j = i + 1; j < 9 - c; j++) {
        temp = population[j];
        population[j] = population[j - 1];
        population[j - 1] = temp;
      }
      c++;
    }
  }
}

void breed(monkey_t **population, char *target) {
  monkey_t *mother, *father, *child;
  int i;
  
  for (i = 0; i < 5; i++) {
    mother  = population[i + 5];
    father  = population[(i + 1) % 5 + 5];
    child   = population[i];
    crossover(mother, father, child, target);
  }
}

