#pragma once
#include <list>
#include <map>
#include <vector>

#include "index_buffer.hpp"
#include "object.hpp"
#include "utils.hpp"
#include "vertex_array.hpp"

namespace kckn {
    typedef std::vector<s_ptr<Object>> ObjectRegister;
    typedef std::vector<s_ptr<IndexBuffer>> IndexBufferRegister;
    typedef std::vector<s_ptr<VertexBuffer>> VertexBufferRegister;
    typedef std::vector<s_ptr<VertexBufferLayout>> LayoutRegister;
    typedef std::vector<s_ptr<VertexArray>> VertexArrayRegister;

    class ObjectManager {
        ObjectRegister objects;
        VertexBufferRegister vertex_buffers;
        IndexBufferRegister index_buffers;
        VertexArrayRegister vertex_arrays;
        LayoutRegister layouts;

    public:
        ObjectManager();
        void update_batch_buffers();
        void bind_for_draw();

        template <typename T, typename... A>
        s_ptr<T> create(A... args) {
            objects.push_back(std::make_shared<T>(args...));
            s_ptr<T> returned = std::dynamic_pointer_cast<T>(objects.back());
            return returned;
        }

        template <typename T, typename... A>
        std::vector<s_ptr<T>> create_many(size_t count, A... args) {
            std::vector<s_ptr<T>> subvector;
            subvector.reserve(count);
            for (size_t i = 0; i < count; i++) {
                subvector.push_back(create<T>(args...));
            }
            return subvector;
        }
    };
} // namespace kckn
