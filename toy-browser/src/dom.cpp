#include <dom.hpp>

dom::TextNode::TextNode(const std::string& text) : text(text) {}

dom::ElementNode::ElementNode(const std::string& name, const AttrMap& attrs,
	std::vector<std::unique_ptr<Node>>& children) {

	this->data.tag_name = name;
	this->data.attributes = attrs;
	this->children.insert(this->children.end(), 
		std::make_move_iterator(children.begin()), 
		std::make_move_iterator(children.end())
	);
}	