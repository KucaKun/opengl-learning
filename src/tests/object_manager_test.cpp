#include <gtest/gtest.h>

#include "object_manager.hpp"
#include "point.hpp"
#include "tests/gl_context_fixture.hpp"

using namespace kckn;
class MockObject : public Object {
    Vertex vertex_data;
    unsigned int index_data;

public:
    MockObject(float x, float y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : vertex_data{x, y, r, g, b, a} {}
    void set_renderer_id(unsigned int id) {

        renderer_id = id;
        set_index_data();
    }
    void set_index_data() {
        index_data = renderer_id;
    }
    Vertex* get_vertex_data() {
        return &vertex_data;
    }
    unsigned int* get_index_data() {
        return &index_data;
    }
    unsigned int get_index_count() {
        return 1;
    }
    void set_position(float x, float y) {}
    void move(float x_offset, float y_offset) {}
    void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
    void move_color(unsigned char r_offset, unsigned char g_offset, unsigned char b_offset, unsigned char a_offset) {}
};
TEST_F(GLContextFixture, SingleObjectInBatchBuffer) {
    ObjectManager object_manager;
    object_manager.create<MockObject>(0, 100, 0, 100, 200, 255);

    object_manager.update_batch_buffers();
    auto batch_buffer = object_manager.get_vertex_buffer()->get_batch_buffer();
    auto vertex_data  = reinterpret_cast<Vertex*>(batch_buffer.get());
    EXPECT_EQ(vertex_data[0].position.x, 0);
    EXPECT_EQ(vertex_data[0].position.y, 100);
    EXPECT_EQ(vertex_data[0].color.r, 0);
    EXPECT_EQ(vertex_data[0].color.g, 100);
    EXPECT_EQ(vertex_data[0].color.b, 200);
    EXPECT_EQ(vertex_data[0].color.a, 255);

    auto index_buffer = object_manager.get_index_buffer()->get_batch_buffer();
    auto index_data   = reinterpret_cast<unsigned int*>(index_buffer.get());
    EXPECT_EQ(index_data[0], 0);
}

TEST_F(GLContextFixture, MultipleObjectsInBatchBuffer) {
    ObjectManager object_manager;
    object_manager.create<MockObject>(0, 100, 0, 100, 200, 255);
    object_manager.create<MockObject>(0, 100, 0, 100, 200, 255);
    object_manager.create<MockObject>(0, 100, 0, 100, 200, 255);

    object_manager.update_batch_buffers();
    auto batch_buffer = object_manager.get_vertex_buffer()->get_batch_buffer();
    auto vertex_data  = reinterpret_cast<Vertex*>(batch_buffer.get());
    EXPECT_EQ(vertex_data[0].position.x, 0);
    EXPECT_EQ(vertex_data[0].position.y, 100);
    EXPECT_EQ(vertex_data[0].color.r, 0);
    EXPECT_EQ(vertex_data[0].color.g, 100);
    EXPECT_EQ(vertex_data[0].color.b, 200);
    EXPECT_EQ(vertex_data[0].color.a, 255);

    EXPECT_EQ(vertex_data[1].position.x, 0);
    EXPECT_EQ(vertex_data[1].position.y, 100);
    EXPECT_EQ(vertex_data[1].color.r, 0);
    EXPECT_EQ(vertex_data[1].color.g, 100);
    EXPECT_EQ(vertex_data[1].color.b, 200);
    EXPECT_EQ(vertex_data[1].color.a, 255);

    EXPECT_EQ(vertex_data[2].position.x, 0);
    EXPECT_EQ(vertex_data[2].position.y, 100);
    EXPECT_EQ(vertex_data[2].color.r, 0);
    EXPECT_EQ(vertex_data[2].color.g, 100);
    EXPECT_EQ(vertex_data[2].color.b, 200);
    EXPECT_EQ(vertex_data[2].color.a, 255);

    auto index_buffer = object_manager.get_index_buffer()->get_batch_buffer();
    auto index_data   = reinterpret_cast<unsigned int*>(index_buffer.get());
    EXPECT_EQ(index_data[0], 0);
    EXPECT_EQ(index_data[1], 1);
    EXPECT_EQ(index_data[2], 2);
}

TEST_F(GLContextFixture, SingleObjectProperRendererId) {
    {
        ObjectManager object_manager;
        object_manager.create<MockObject>(0, 100, 0, 100, 200, 255);
        EXPECT_EQ(object_manager.get_drawable_objects().back()->renderer_id, 0);
    } // should free the renderer_id

    ObjectManager object_manager;
    object_manager.create<MockObject>(100, 200, 0, 1, 2, 3);
    EXPECT_EQ(object_manager.get_drawable_objects().back()->renderer_id, 0);
}

TEST_F(GLContextFixture, SingleObjectInBatchBufferAfterRemoval) {
    {
        ObjectManager object_manager;
        object_manager.create<MockObject>(0, 100, 0, 100, 200, 255);
        object_manager.update_batch_buffers();
    } // should free the renderer_id

    ObjectManager object_manager;
    object_manager.create<MockObject>(100, 200, 0, 1, 2, 3);
    object_manager.update_batch_buffers();

    auto batch_buffer = object_manager.get_vertex_buffer()->get_batch_buffer();
    auto vertex_data  = reinterpret_cast<Vertex*>(batch_buffer.get());
    EXPECT_EQ(vertex_data[0].position.x, 100);
    EXPECT_EQ(vertex_data[0].position.y, 200);
    EXPECT_EQ(vertex_data[0].color.r, 0);
    EXPECT_EQ(vertex_data[0].color.g, 1);
    EXPECT_EQ(vertex_data[0].color.b, 2);
    EXPECT_EQ(vertex_data[0].color.a, 3);

    auto index_buffer = object_manager.get_index_buffer()->get_batch_buffer();
    auto index_data   = reinterpret_cast<unsigned int*>(index_buffer.get());
    EXPECT_EQ(index_data[0], 0);
}
