#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <math.h>
#include <unordered_map>
#include <cstdint>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <sstream>
#include <fstream>
#include <functional>
#include <deque>
#include <chrono>
#include <map>
#include <stdarg.h>
#include <memory>
#include <regex>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include "emscripten/websocket.h"
#include <emscripten/bind.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_opengl.h>

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include <GL/glfw.h>

#include "engine.h"
#include "../utils/renderer.h"