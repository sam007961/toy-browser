#include <dom.hpp>

dom::TextNode::TextNode(const std::string& text) : text(text) {}

dom::ElementData::ElementData(const std::string& tag_name, const AttrMap& attributes)
	: tag_name(tag_name), attributes(attributes) {}

dom::ElementNode::ElementNode(const std::string& name, const AttrMap& attrs,
	std::vector<std::unique_ptr<Node>>& children) : data(name, attrs) {

	children.insert(this->children.end(), 
		std::make_move_iterator(children.begin()), 
		std::make_move_iterator(children.end())
	);
}	