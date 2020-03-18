#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

namespace dom {

	// Node base class
	struct Node {
		// child nodes
		std::vector<std::unique_ptr<Node>> children;
	};

	// Text node
	struct TextNode : Node {
		std::string text;
		TextNode() {}
		TextNode(const std::string& text);
	};

	// Attribute map
	typedef std::unordered_map<std::string, std::string> AttrMap;

	// Element data
	struct ElementData {
		std::string tag_name;
		AttrMap attributes;

		ElementData() {}
		ElementData(const std::string& tag_name, const AttrMap& attributes);
	};

	// Element node
	struct ElementNode : Node {
		ElementData data;
		ElementNode() {}
		ElementNode(const std::string& name, const AttrMap& attrs,
			std::vector<std::unique_ptr<Node>>& children);
	};
}