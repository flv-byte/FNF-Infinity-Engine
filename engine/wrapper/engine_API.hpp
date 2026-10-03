#pragma once
#include <unordered_map>
#include <string>
#include <any>
#include "wrapper/GCT.hpp"
#include <memory>
#include <renderer.h>
#include <runtime.h>

namespace global {
	class engine {
	public:
		void init(bool debug, char* argv[]) {
			std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
			renderer->init("FLV FNF", 960, 540);
			std::unique_ptr<runtime> rt = std::make_unique<runtime>();
			global::gct.table["renderer"] = renderer.get();
			global::gct.table["runtime"] = rt.get();
			rt->init();
			renderer->quit();
		};
	};
}