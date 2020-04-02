#include <iostream>
#include <fstream>
#include <html-parser.hpp>
#include <dom-printer.hpp>

int main(int argc, char** argv) {
	/*auto tnode = std::unique_ptr<dom::TextNode>(new dom::TextNode("test"));
	std::vector<std::unique_ptr<dom::Node>> children;
	children.push_back(std::move(tnode));
	dom::ElementNode enode("test", {}, children);*/

	std::ifstream test_html("test/test.html");
	std::string source_html;
	test_html.seekg(0, std::ios::end);
	source_html.reserve(test_html.tellg());
	test_html.seekg(0, std::ios::beg);
	source_html.assign(std::istreambuf_iterator<char>(test_html),
		std::istreambuf_iterator<char>());

	std::cout << source_html << std::endl;

	auto dom_root = HtmlParser(source_html).parse();
	std::cout << DomPrinter(*dom_root).print() << std::endl;
	return 0;
}