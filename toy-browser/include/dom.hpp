#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

namespace dom {
	template <typename T>
	struct Node {
		// child nodes
		std::vector<std::unique_ptr<Node>> children;

	};

	typedef std::unordered_map<std::string, std::string> AttrMap;

	struct ElementData {
		std::string tag_name;
		AttrMap attributes;
	};
}