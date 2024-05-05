#pragma once
#include <list>
#include <map>
#include <vector>

#include "index_buffer.hpp"
#include "object.hpp"
#include "utils.hpp"
#include "vertex_array.hpp"

namespace kckn {

    class ObjectManager {

        std::list<unsigned int> taken_obj_ids;
        std::list<unsigned int> freed_obj_ids;

        typedef std::list<s_ptr<Object>> ObjectRegister;
        typedef s_ptr<IndexBuffer> IndexBufferRegister;
        typedef s_ptr<VertexBuffer> VertexBufferRegister;
        typedef s_ptr<VertexBufferLayout> LayoutRegister;
        typedef s_ptr<VertexArray> VertexArrayRegister;

        ObjectRegister drawable_objects;
        VertexBufferRegister vertex_buffer;
        IndexBufferRegister index_buffer;
        VertexArrayRegister vertex_array;
        LayoutRegister layout;

    public:
        ObjectManager();
        void update_batch_buffers();
        void bind_for_draw();

        unsigned int obtain_id() {
            unsigned int renderer_id;
            if (freed_obj_ids.empty()) {
                if (taken_obj_ids.empty()) {
                    renderer_id = 0;
                    taken_obj_ids.push_back(0);
                } else {
                    renderer_id = taken_obj_ids.back() + 1;
                    taken_obj_ids.push_back(renderer_id);
                }
            } else {
                renderer_id = freed_obj_ids.back();
                taken_obj_ids.push_back(renderer_id);
                freed_obj_ids.pop_back();
            }
            return renderer_id;
        }

        void free_id(unsigned int renderer_id) {
            freed_obj_ids.push_back(renderer_id);
            taken_obj_ids.remove(renderer_id);
        }

        template <typename T, typename... A>
        s_ptr<T> create(A... args) {
            drawable_objects.push_back(std::make_shared<T>(args...));
            drawable_objects.back()->set_renderer_id(obtain_id());
            s_ptr<T> returned = std::dynamic_pointer_cast<T>(drawable_objects.back());
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
