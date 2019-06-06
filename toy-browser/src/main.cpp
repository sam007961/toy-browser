#include <dom.hpp>
#include <iostream>

int main(int argc, char** argv) {
	auto tnode = std::unique_ptr<dom::TextNode>(new dom::TextNode("test"));
	std::vector<std::unique_ptr<dom::Node>> children;
	children.push_back(std::move(tnode));
	dom::ElementNode enode("test", {}, children);
	return 0;
}