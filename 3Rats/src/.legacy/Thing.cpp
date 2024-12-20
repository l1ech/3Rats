#include "Thing.h"

void Thing::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}