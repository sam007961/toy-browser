#include <dom-visitor.hpp>

class DomComparator : public DomVisitor {
private:
    dom::Node& root;

public:
    DomComparator(dom::Node& root);
    bool compare(dom::Node& other);
};