#pragma once
#include <vector>
#include <memory>
#include <style.hpp>

namespace layout {
    struct Rect {
        float x = 0, y = 0;
        float width = 0, heigth = 0;
    };

    struct EdgeSizes {
        float left = 0, right = 0, top = 0, bottom = 0;
    };

    struct Dimensions {
        Rect content;
        EdgeSizes padding;
        EdgeSizes border;
        EdgeSizes margin;
    };

    struct LayoutBox;
    typedef std::unique_ptr<LayoutBox> LayoutBoxPtr;

    struct LayoutBox {
        const style::StyledNode* const style_node;
        Dimensions dimensions;
        std::vector<LayoutBoxPtr> children;

        LayoutBox(style::StyledNode* styled_node = nullptr);
        virtual LayoutBox* get_inline_container() = 0;
    };

    struct AnnonymousBlock : public LayoutBox {
        AnnonymousBlock();
        AnnonymousBlock(style::StyledNode*) = delete;
        virtual LayoutBox* get_inline_container();
    };

    struct InlineNode : public LayoutBox {
        virtual LayoutBox* get_inline_container();
    };

    struct BlockNode : public LayoutBox {
        virtual LayoutBox* get_inline_container();
    };

    LayoutBoxPtr build_layout_tree(const style::StyledNode& style_node);
}