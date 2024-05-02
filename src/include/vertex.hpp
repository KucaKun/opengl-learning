#pragma once
namespace kckn {
    struct Position {
        float x, y;
    };
    struct Color {
        float r, g, b, a;
    };
    union Vertex {
        float data[6];
        struct {
            Position position;
            Color color;
        };
    };
} // namespace kckn
