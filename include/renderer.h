#pragma once

#ifdef _WIN32
	#include <renderers/winRenderer.h>
	using Renderer = winRenderer;
#endif