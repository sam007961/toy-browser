#include <dom.hpp>
#include <dom-visitor.hpp>
#include <typeinfo>

dom::Node::Node() {}
dom::Node::Node(std::vector<std::unique_ptr<Node>>&& children) :
	children(std::move(children)) {}
bool dom::Node::operator==(const Node& other) const {
	return typeid(*this) == typeid(other) && isEqual(other);
}

dom::TextNode::TextNode(const std::string& text) : text(text) {}
void dom::TextNode::accept(DomVisitor& visitor) { visitor.visit(*this); }
bool dom::TextNode::isEqual(const Node& other) const {
	return text == static_cast<const TextNode&>(other).text;
}

dom::ElementData::ElementData(const std::string& tag_name, const AttrMap& attributes)
	: tag_name(tag_name), attributes(attributes) {}
bool dom::ElementData::operator==(const ElementData& other) const {
	return tag_name == other.tag_name
		&& attributes == other.attributes;
}

dom::ElementNode::ElementNode(const std::string& name, const AttrMap& attrs,
	std::vector<std::unique_ptr<Node>>&& children) :
	data(name, attrs), Node(std::move(children)) {}	
void dom::ElementNode::accept(DomVisitor& visitor) { visitor.visit(*this); }
bool dom::ElementNode::isEqual(const Node& other) const {
	return data == static_cast<const ElementNode&>(other).data;
}