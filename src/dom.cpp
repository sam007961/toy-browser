#include <dom.hpp>
#include <dom-visitor.hpp>
#include <typeinfo>
#include <sstream>
#include <iterator>

dom::Node::Node() {}

dom::Node::Node(std::vector<std::unique_ptr<Node>>&& children) :
	children(std::move(children)) {}

bool dom::Node::operator==(const Node& other) const {
	return typeid(*this) == typeid(other) && isEqual(other);
}

bool dom::Node::operator!=(const Node& other) const {
	return !(*this == other);
}


dom::TextNode::TextNode(const std::string& text,
	std::vector<std::unique_ptr<Node>>&& children)
		: text(text), Node(std::move(children)) {}

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

std::optional<std::string> dom::ElementData::id() const {
	auto idIt = attributes.find("id");
	if(idIt == attributes.end()) {
		return std::nullopt;
	} else {
		return idIt->second;
	}
}

std::unordered_set<std::string> dom::ElementData::classes() const {
	auto classesIt = attributes.find("class");
	if(classesIt == attributes.end()) {
		return {};
	} else {
		auto classesIss = std::istringstream(classesIt->second);
		return std::unordered_set<std::string>(
			std::istream_iterator<std::string>(classesIss),
			std::istream_iterator<std::string>()
		);
	}
}


dom::ElementNode::ElementNode(const std::string& name, const AttrMap& attrs,
	std::vector<std::unique_ptr<Node>>&& children) :
	data(name, attrs), Node(std::move(children)) {}	

void dom::ElementNode::accept(DomVisitor& visitor) { visitor.visit(*this); }

bool dom::ElementNode::isEqual(const Node& other) const {
	return data == static_cast<const ElementNode&>(other).data;
}


bool compare_helper(
	const std::vector<std::unique_ptr<dom::Node>>& nodes_a,
	const std::vector<std::unique_ptr<dom::Node>>& nodes_b) {
		auto aIt = nodes_a.begin();
		auto bIt = nodes_b.begin();
		while(aIt != nodes_a.end() && bIt != nodes_b.end()) {
			if(**aIt != **bIt) return false;
			aIt++; bIt++;
		}
		return true;
}

bool dom::compare(const Node& a, const Node& b) {
	return a == b && a.children.size() == b.children.size()
		&& compare_helper(a.children, b.children);
}