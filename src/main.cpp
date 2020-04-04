#include <iostream>
#include <fstream>
#include <html-parser.hpp>
#include <css-parser.hpp>
#include <dom-printer.hpp>

int main(int argc, char** argv) {
	/*auto tnode = std::unique_ptr<dom::TextNode>(new dom::TextNode("test"));
	std::vector<std::unique_ptr<dom::Node>> children;
	children.push_back(std::move(tnode));
	dom::ElementNode enode("test", {}, children);*/

	std::ifstream test_html("resources/test.html");
	std::string source_html;
	test_html.seekg(0, std::ios::end);
	source_html.reserve(test_html.tellg());
	test_html.seekg(0, std::ios::beg);
	source_html.assign(std::istreambuf_iterator<char>(test_html),
		std::istreambuf_iterator<char>());

	std::ifstream test_css("resources/test.css");
	std::string source_css;
	test_css.seekg(0, std::ios::end);
	source_css.reserve(test_css.tellg());
	test_css.seekg(0, std::ios::beg);
	source_css.assign(std::istreambuf_iterator<char>(test_css),
		std::istreambuf_iterator<char>());

	std::cout << source_html << std::endl;
	std::cout << source_css << std::endl;

	auto dom_root = HtmlParser(source_html).parse();
	auto stylesheet = CssParser(source_css).parse();
	std::cout << DomPrinter(*dom_root).print() << std::endl;
	return 0;
}