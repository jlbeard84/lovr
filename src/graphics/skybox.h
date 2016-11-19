#include "glfw.h"

#ifndef LOVR_SKYBOX_TYPES
#define LOVR_SKYBOX_TYPES
typedef struct {
  GLuint texture;
} Skybox;
#endif

Skybox* lovrSkyboxCreate(void** data, int* size);
void lovrSkyboxDestroy(Skybox* skybox);
