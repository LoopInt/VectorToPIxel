#include <SDL.h>

#include <stdio.h>

void drawHorizontalLine(SDL_Renderer* pRenderer, int y, int x1, int x2);
void drawVerticalLine(SDL_Renderer* pRenderer, int x, int y1, int y2);

int main(int argc, char* argv[])
{
	unsigned int width_pxl = 700;
	unsigned int height_pxl = 500;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("VertorToPixel", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width_pxl,
        height_pxl,
        SDL_WINDOW_SHOWN);

    if (!pWindow)
    {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, width_pxl, height_pxl);


    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    SDL_SetRenderTarget(pRenderer, pTexture);
    SDL_RenderClear(pRenderer);
    
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    drawHorizontalLine(pRenderer, 10, 100, 20);
    drawVerticalLine(pRenderer, 10, 100, 20);

    SDL_SetRenderTarget(pRenderer, NULL);

    SDL_Rect dst = { 0, 0, width_pxl, height_pxl };
    SDL_RenderCopy(pRenderer, pTexture, NULL, &dst);
    SDL_RenderPresent(pRenderer);

    SDL_Delay(5000);

    SDL_DestroyTexture(pTexture);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();

    return 0;
}

void drawHorizontalLine(SDL_Renderer* pRenderer, int y, int x1, int x2)
{
    int dx = x2 - x1;

    if (dx >= 0)
    {
        for (int xi = x1; xi <= x2; xi++)
        {
            SDL_RenderDrawPoint(pRenderer, xi, y);
        }
    }
    else
    {
        for (int xi = x1; xi >= x2; xi--)
        {
            SDL_RenderDrawPoint(pRenderer, xi, y);
        }
    }
}

void drawVerticalLine(SDL_Renderer* pRenderer, int x, int y1, int y2)
{
    int dy = y2 - y1;

    if (dy >= 0)
    {
        for (int yi = y1; yi <= y2; yi++)
        {
            SDL_RenderDrawPoint(pRenderer, x, yi);
        }
    }
    else
    {
        for (int yi = y1; yi >= y2; yi--)
        {
            SDL_RenderDrawPoint(pRenderer, x, yi);
        }
    }
}