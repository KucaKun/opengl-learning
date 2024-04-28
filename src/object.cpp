#include "object.hpp"
namespace kckn {
    std::unique_ptr<VertexBuffer> Point::vb;
    std::unique_ptr<IndexBuffer> Point::ib;
    std::unique_ptr<VertexBufferLayout> Point::layout;
    std::unique_ptr<Shader> Point::shader;
    std::unique_ptr<VertexArray> Point::va;
    unsigned int Point::obj_ctr = 0;
} // namespace kckn
