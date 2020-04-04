#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class DomVisitor;

namespace dom {

	// Node base class
	struct Node {
		// child nodes
		std::vector<std::unique_ptr<Node>> children;
		Node();
		Node(std::vector<std::unique_ptr<Node>>&& children);

		virtual void accept(DomVisitor& visitor) = 0;
		virtual bool isEqual(const Node& other) const = 0;

		bool operator==(const Node& other) const;
	};

	// Text node
	struct TextNode : Node {
		std::string text;
		TextNode() {}
		TextNode(const std::string& text);

		virtual void accept(DomVisitor& visitor);
		virtual bool isEqual(const Node& other) const;
	};

	// Attribute map
	typedef std::unordered_map<std::string, std::string> AttrMap;

	// Element data
	struct ElementData {
		std::string tag_name;
		AttrMap attributes;

		ElementData() {}
		ElementData(const std::string& tag_name, const AttrMap& attributes);
		bool operator==(const ElementData& other) const;
	};

	// Element node
	struct ElementNode : Node {
		ElementData data;
		ElementNode() {}
		ElementNode(const std::string& name, const AttrMap& attrs,
			std::vector<std::unique_ptr<Node>>&& children);

		virtual void accept(DomVisitor& visitor);
		virtual bool isEqual(const Node& other) const;
	};
}