#include <dom.hpp>
#include <parser.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	/*auto tnode = std::unique_ptr<dom::TextNode>(new dom::TextNode("test"));
	std::vector<std::unique_ptr<dom::Node>> children;
	children.push_back(std::move(tnode));
	dom::ElementNode enode("test", {}, children);*/

	std::ifstream test("test/test.html");
	std::string source;
	test.seekg(0, std::ios::end);
	source.reserve(test.tellg());
	test.seekg(0, std::ios::beg);
	source.assign(std::istreambuf_iterator<char>(test),
		std::istreambuf_iterator<char>());

	std::cout << "test" << std::endl;
	std::cout << source << std::endl;

	Parser parser(source);
	auto root = parser.parse();
	return 0;
}