#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Textures.h"

#include "Defs.h"

#include "SDL_image/include/SDL_image.h"

Textures::Textures() : Module()
{

}

// Destructor
Textures::~Textures()
{}

// Called before render is available
bool Textures::Awake()
{
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool Textures::Start()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool Textures::CleanUp()
{
	ListItem<SDL_Texture*>* item;

	for (item = textures.start; item != NULL; item = item->next)
	{
		SDL_DestroyTexture(item->data);
	}

	textures.Clear();
	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const Textures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if(path != NULL)
	{
		texture = LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

// Unload texture
bool Textures::UnLoad(SDL_Texture* texture)
{
	ListItem<SDL_Texture*>* item;

	for (item = textures.start; item != NULL; item = item->next)
	{
		if (texture == item->data)
		{
			SDL_DestroyTexture(item->data);
			textures.Del(item);
			return true;
		}
	}

	return false;
}

// Translate a surface into a texture
SDL_Texture* const Textures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(App->renderer3D->renderer, surface); 

	if(surface != NULL)
	{
		textures.Add(texture);
	}

	return texture;
}

// Retrieve size of a texture
void Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}


