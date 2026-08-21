#ifdef INCLUDE_SDL
	#ifdef _WIN32
		#include <SDL3/SDL.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL3/SDL.h>
	#elif __linux__
		#include <SDL3/SDL.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL
#endif


#ifdef INCLUDE_SDL_IMAGE
	#ifdef _WIN32
		#include <SDL3_image/SDL_image.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL3_image/SDL_image.h>
	#elif __linux__
		#include <SDL3_image/SDL_image.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_IMAGE
#endif


#ifdef INCLUDE_SDL_MIXER
	#ifdef _WIN32
		#include <SDL3_mixer/SDL_mixer.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL3_mixer/SDL_mixer.h>
	#elif __linux__
		#include <SDL3_mixer/SDL_mixer.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_MIXER
#endif


#ifdef INCLUDE_SDL_TTF
	#ifdef _WIN32
		#include <SDL3_ttf/SDL_ttf.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL3_ttf/SDL_ttf.h>
	#elif __linux__
		#include <SDL3_ttf/SDL_ttf.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_TTF
#endif
