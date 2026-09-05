#pragma once

class winRenderer;

#ifdef _WIN32
	#include <renderers/winRenderer.h>
	using Renderer = winRenderer;
#endif