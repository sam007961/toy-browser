#pragma once
#include <vector>
#include <memory>
#include <style.hpp>

namespace layout {
    struct Rect {
        float x, y;
        float width, heigth;
    };

    struct EdgeSizes {
        float left, right, top, bottom;
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
        Dimensions dimensions;
        std::vector<LayoutBoxPtr> children;

        virtual style::StyledNode* get_styled_node() const = 0;
        virtual LayoutBoxPtr get_inline_container() const = 0;
    };

    struct AnnonymousBlock : public LayoutBox {
        virtual style::StyledNode* get_styled_node() const;
        virtual LayoutBoxPtr get_inline_container() const;
    };
}