#include <dom.hpp>
#include <dom-visitor.hpp>

dom::Node::Node() {}
dom::Node::Node(std::vector<std::unique_ptr<Node>>&& children) :
	children(std::move(children)) {}

dom::TextNode::TextNode(const std::string& text) : text(text) {}
void dom::TextNode::accept(DomVisitor& visitor) { visitor.visit(*this); }

dom::ElementData::ElementData(const std::string& tag_name, const AttrMap& attributes)
	: tag_name(tag_name), attributes(attributes) {}

dom::ElementNode::ElementNode(const std::string& name, const AttrMap& attrs,
	std::vector<std::unique_ptr<Node>>&& children) :
	data(name, attrs), Node(std::move(children)) {}	
void dom::ElementNode::accept(DomVisitor& visitor) { visitor.visit(*this); }