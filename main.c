#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include<SDL2/SDL_render.h>
#include <time.h>

#include "insertion-info.h"
#include "intro.h"

//Load Fonts
TTF_Font *font;

 
typedef struct cel *liste;
typedef struct cel
{
    int info;
    liste svt;
    liste pre;
}cel; 
// Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ARRAY_SIZE 10
#define BAR_WIDTH (SCREEN_WIDTH / ARRAY_SIZE) 

// SDL variables
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

void render(SDL_Renderer *renderer,liste tete, TTF_Font *font) {
    
    
    SDL_SetRenderDrawColor(renderer, 0, 0,0, 0);

    SDL_RenderClear(renderer);
    
   for (int i = 0; i < ARRAY_SIZE; i++) {
        int barHeight = tete->info * 10;
        int barX = i * (BAR_WIDTH); // +1 for spacing between bars
        int barY = SCREEN_HEIGHT - barHeight;

        SDL_Color barColor;
        if (i % 2 == 0) {
        // Lighter shade of green
        barColor = (SDL_Color){100, 255, 100, 255}; // Adjust RGB values for a lighter shade
        } else {
         // Darker shade of green
        barColor = (SDL_Color){50, 200, 50, 255}; // Adjust RGB values for a darker shade
        }

        SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
        SDL_Rect barRect = {barX, barY, BAR_WIDTH, barHeight};
        SDL_RenderFillRect(renderer, &barRect);

        // Draw the value inside the rectangle
        SDL_Color textColor = {255, 255, 255, 255};
        char valueText[5];
        snprintf(valueText, sizeof(valueText), "%d", tete->info);
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, valueText, textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Calculate the position to center the text
        int textX = barX + BAR_WIDTH / 2 - textSurface->w / 2;
        int textY = barY - textSurface->h - 5; // Adjust for text position

        SDL_Rect textRect = {textX, textY, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        tete=tete->svt;
    }
   

    SDL_RenderPresent(renderer);
    SDL_Delay(100);    
}

void Tri_Insertion1(liste tete, SDL_Renderer *renderer, TTF_Font *font) {
    liste i, j, key;
    for (i = tete->svt; i != NULL; i = i->svt) {
        key = i;
        j = i->pre;
        while (j != NULL && j->info > key->info) {
            j->svt = key->svt;
            if (key->svt != NULL) {
                key->svt->pre = j;
            }
            key->pre = j->pre;
            key->svt = j;
            if (j->pre != NULL) {
                j->pre->svt = key;
            } else {
                tete = key;
            }
            j->pre = key;
            j = key->pre;
            render(renderer, tete, font);
            SDL_Delay(100);
        }
    }
}



liste verifie(){
    liste nouv=(liste)malloc(sizeof(cel));
    if(nouv==NULL)
    {
        printf("Memory error");
        exit(-1);
    }
    return nouv;
}

void ajouter_liste(liste* tete, int e ) {
    liste nouv = verifie();

    nouv->info = e;
    nouv->svt = *tete;
    nouv->pre = NULL;

    if (*tete != NULL) {
        (*tete)->pre = nouv;
    }

    *tete = nouv;
}

void affiche_liste(liste tete){
    while (tete != NULL) {
        printf("%d ", tete->info);
        tete = tete->svt;
    }
    printf("\n");
}



int main(int argc, char * argv[]) {

    //initialize clock
    clock_t start_time, end_time;
    double cpu_time_used;
    // Record the start time
    start_time = clock();


  // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() < 0) {
      fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
      return -1;
  }

  font = TTF_OpenFont("fonts/OpenSans-Light.ttf", 12);

  
  while(true){
  
   liste tete = NULL;
  srand(time(NULL));
  int element;
  
//affiche_liste(tete);

  printintro();

  int choice;
  
  printf("\nEnter your Choice Now: ");
  scanf("%d", & choice);
  switch (choice)
  {
  case 1:
  //random array 
  
  for (int i = 0; i < ARRAY_SIZE; ++i) {
    
    element= rand() % 50;
      ajouter_liste(&tete,element);
  }
window = SDL_CreateWindow("Sorting Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);  
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    

  Tri_Insertion1(tete, renderer, font); 
  
    

  // Record the end time
  end_time = clock();

  // Calculate the CPU time used in seconds
  cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;


  

  printf("\n\n\n\n Time Taken: %f seconds", cpu_time_used );
  printf("\n\n\" The sorted array is : \n");
  affiche_liste(tete);
    break;
  case 2: 
             printf("Enter %d elements of the list :\n", ARRAY_SIZE);
              for (int i = 0; i < ARRAY_SIZE; ++i) {
                  int element;
                  printf("Element %d: ", i + 1);
                  scanf("%d", &element);
                  ajouter_liste(&tete, element); // Add elements to the linked list
              }
            window = SDL_CreateWindow("Insertion Sort Visualiser", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
              printf("\n\n\" The list before the sort : \n");
                affiche_liste(tete);
            Tri_Insertion1(tete, renderer, font);
            
            // Record the end time
            end_time = clock();

            // Calculate the CPU time used in seconds
            cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;


            

            printf("\n\nTime Taken: %f seconds", cpu_time_used );
           
            
  break;
  case 3:  printSortingInfo();
  break;

  case 4:
  //exit
  return(0);
  break;
  default:
  break;
  
  }

    
 

 
//exit after the sort 
  int l;
  printf("\n\n\n\nPress 1 if you want to exit the program. ");
  scanf("%d", &l);
  if(l == 1){
    break;
  }

bool isPaused = false;
  
  // Event loop
  SDL_Event event;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent( & event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }
  }

  // Clean up and quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  }



  return 0;
}