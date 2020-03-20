#include <dom.hpp>

dom::Node::Node() {}
dom::Node::Node(std::vector<std::unique_ptr<Node>>& children) :
	children(std::move(children)) {}

dom::TextNode::TextNode(const std::string& text) : text(text) {}

dom::ElementData::ElementData(const std::string& tag_name, const AttrMap& attributes)
	: tag_name(tag_name), attributes(attributes) {}

dom::ElementNode::ElementNode(const std::string& name, const AttrMap& attrs,
	std::vector<std::unique_ptr<Node>>& children) : data(name, attrs), Node(children) {
	// this->children.resize(this->children.size() + children.size());
	// this->children.insert(this->children.end(), 
	// 	std::make_move_iterator(children.begin()), 
	// 	std::make_move_iterator(children.end())
	// );
}	