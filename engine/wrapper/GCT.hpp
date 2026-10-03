#pragma once
#include <unordered_map>
#include <string>
#include <any>

namespace global {
	class GCT {
	public:
		std::unordered_map<std::string, std::any> table;
	};

	inline GCT gct;
}