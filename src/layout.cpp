#include <vector>
#include <layout.hpp>

layout::LayoutBox::LayoutBox(style::StyledNode* style_node)
    : style_node(style_node) {}


layout::AnnonymousBlock::AnnonymousBlock() : LayoutBox(nullptr) {}

layout::LayoutBox* layout::AnnonymousBlock::get_inline_container() { return this; }


layout::LayoutBox* layout::InlineNode::get_inline_container() { return this; }


layout::LayoutBox* layout::BlockNode::get_inline_container() {
    if(auto ptr = dynamic_cast<AnnonymousBlock*>(children.back().get()); !ptr) {
        children.push_back(std::make_unique<AnnonymousBlock>());
    }
    return children.back().get();
}
