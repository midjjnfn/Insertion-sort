#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

typedef struct cel *liste;
typedef struct cel
{
    int info;
    liste svt;
    liste pre;
} cel;

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

void Tri_Insertion1(liste tete) {
    int temp;
    liste i, j, v;
    v = tete->svt;

    while (v != NULL) {
        j = v->pre;
        i = v;
        while (j != NULL && j->info > i->info) {
            temp = j->info;
            j->info = i->info;
            i->info = temp;

            i = j;
            j = j->pre;
        }
        v = v->svt;
    }
}

void render(liste tete, int blockWidth) {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Draw your sorting bars here
    int posX = 0;
    while (tete != NULL) {
        SDL_Rect bar = { posX, SCREEN_HEIGHT - tete->info, blockWidth, tete->info };
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF); // Blue
        SDL_RenderFillRect(gRenderer, &bar);

        tete = tete->svt;
        posX += blockWidth;
    }

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    gWindow = SDL_CreateWindow("Sorting Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    int numBlocks;
    std::cout << "Enter the number of blocks: ";
    std::cin >> numBlocks;

    int blockWidth = SCREEN_WIDTH / numBlocks;

    liste tete = NULL;
    int e;
    for (int i = 0; i < numBlocks; ++i) {
        std::cout << "Enter a value: ";
        std::cin >> e;
        ajouter_liste(&tete, e);
    }

    // Visualization starts here
    render(tete, blockWidth);
    SDL_Delay(1000);

    Tri_Insertion1(tete);

    // Visualization after sorting
    render(tete, blockWidth);

    // Wait for the user to close the window
SDL_Event event;
bool quit = false;

while (!quit) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }

    // Visualization during sorting
    render(tete, blockWidth);
    SDL_Delay(100);  // Adjust the delay as needed

    Tri_Insertion1(tete);
}

// Visualization after sorting
render(tete, blockWidth);

// Wait for the user to close the window
bool endProgram = false;
while (!endProgram) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            endProgram = true;
        }
    }
}

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();

    return 0;
}
