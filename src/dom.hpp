#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

class DomVisitor;

namespace dom {
	struct Node;
	typedef std::unique_ptr<Node> NodePtr;

	// Node base class
	struct Node {
		// child nodes
		std::vector<NodePtr> children;

		Node();
		Node(std::vector<NodePtr>&& children);

		virtual void accept(DomVisitor& visitor) = 0;
		virtual bool isEqual(const Node& other) const = 0;

		bool operator==(const Node& other) const;
		bool operator!=(const Node& other) const;
	};

	// Text node
	struct TextNode : Node {
		std::string text;
		TextNode() {}
		TextNode(const std::string& text,
			std::vector<NodePtr>&& children = {});

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

		std::optional<std::string> id() const;
		std::unordered_set<std::string> classes() const;
	};

	// Element node
	struct ElementNode : Node {
		ElementData data;
		ElementNode() {}
		ElementNode(const std::string& name, const AttrMap& attrs = {},
			std::vector<NodePtr>&& children = {});

		virtual void accept(DomVisitor& visitor);
		virtual bool isEqual(const Node& other) const;
	};

	// compare two trees or sub-trees
	bool compare(const Node& a, const Node& b);
}