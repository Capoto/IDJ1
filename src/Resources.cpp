
#include "Resources.h"
#include "Game.h"
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {

  /* Looks for the requested image. */
  std::unordered_map<std::string, SDL_Texture*>::const_iterator foundIt =
                                            Resources::imageTable.find(file);

  /* If found, return it, if not, create it. */
  if (foundIt != Resources::imageTable.end()) {
    return foundIt->second;
  } else {
    SDL_Texture* sdlTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    Resources::imageTable.insert({file, sdlTexture});
    return sdlTexture;
  }
}

void Resources::ClearImages() {

  /* Clearing each of the allocated images. */
  for (auto& image: Resources::imageTable) {
    SDL_DestroyTexture(image.second);
  }
  Resources::imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {

  /* Looks for the requested music. */
  std::unordered_map<std::string, Mix_Music*>::const_iterator foundIt =
                                            Resources::musicTable.find(file);

  /* If found, return it, if not, create it. */
  if (foundIt != Resources::musicTable.end()) {
    return foundIt->second;
  } else {
    Mix_Music* mixMusic = Mix_LoadMUS(file.c_str());
    if (mixMusic == nullptr) {
      SDL_Log("Unable to load music Mix_LoadMUS: %s", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    Resources::musicTable.insert({file, mixMusic});
    return mixMusic;
  }
}

void Resources::ClearMusics() {

  /* Clearing each of the allocated musics. */
  for (auto& music: Resources::musicTable) {
    Mix_FreeMusic(music.second);
  }
  Resources::musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {

  /* Looks for the requested sound. */
  std::unordered_map<std::string, Mix_Chunk*>::const_iterator foundIt =
                                            Resources::soundTable.find(file);

  /* If found, return it, if not, create it. */
  if (foundIt != Resources::soundTable.end()) {
    return foundIt->second;
  } else {
    Mix_Chunk* mixChunk = Mix_LoadWAV(file.c_str());
    if (mixChunk == nullptr) {
      SDL_Log("Unable to open sound Mix_LoadWAV: %s", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    Resources::soundTable.insert({file, mixChunk});
    return mixChunk;
  }
}

void Resources::ClearSounds() {

  /* Clearing each of the allocated images. */
  for (auto& sound: Resources::soundTable) {
    Mix_FreeChunk(sound.second);
  }
  Resources::soundTable.clear();
}