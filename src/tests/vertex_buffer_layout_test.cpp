#include <gtest/gtest.h>

#include "vertex_buffer_layout.hpp"
using namespace kckn;
TEST(VertexBufferLayoutTest, PushSingleElement) {
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    auto elements = layout.get_elements();
    ASSERT_EQ(elements.size(), 1);
    ASSERT_EQ(elements[0].type, GL_FLOAT);
    ASSERT_EQ(elements[0].count, 2);
    ASSERT_EQ(elements[0].normalized, false);
}

TEST(VertexBufferLayoutTest, PushMultipleElements) {
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 4);
    auto elements = layout.get_elements();
    ASSERT_EQ(elements.size(), 2);
    ASSERT_EQ(elements[0].type, GL_FLOAT);
    ASSERT_EQ(elements[0].count, 2);
    ASSERT_EQ(elements[0].normalized, false);
    ASSERT_EQ(elements[1].type, GL_FLOAT);
    ASSERT_EQ(elements[1].count, 4);
    ASSERT_EQ(elements[1].normalized, false);
}

TEST(VertexBufferLayoutTest, GetStrideFloat) {
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    ASSERT_EQ(layout.get_stride(), 2 * sizeof(float));
    layout.push(GL_FLOAT, 4);
    ASSERT_EQ(layout.get_stride(), 6 * sizeof(float));
}


TEST(VertexBufferLayoutTest, GetStrideInt) {
    VertexBufferLayout layout;
    layout.push(GL_INT, 3);
    ASSERT_EQ(layout.get_stride(), 3 * sizeof(int));
    layout.push(GL_INT, 2);
    ASSERT_EQ(layout.get_stride(), 5 * sizeof(int));
}

TEST(VertexBufferLayoutTest, GetStrideUnsignedInt) {
    VertexBufferLayout layout;
    layout.push(GL_UNSIGNED_INT, 1);
    ASSERT_EQ(layout.get_stride(), sizeof(unsigned int));
    layout.push(GL_UNSIGNED_INT, 4);
    ASSERT_EQ(layout.get_stride(), 5 * sizeof(unsigned int));
}

TEST(VertexBufferLayoutTest, GetStrideByte) {
    VertexBufferLayout layout;
    layout.push(GL_BYTE, 1);
    ASSERT_EQ(layout.get_stride(), sizeof(char));
    layout.push(GL_BYTE, 2);
    ASSERT_EQ(layout.get_stride(), 3 * sizeof(char));
}

TEST(VertexBufferLayoutTest, GetStrideUnsignedByte) {
    VertexBufferLayout layout;
    layout.push(GL_UNSIGNED_BYTE, 3);
    ASSERT_EQ(layout.get_stride(), 3 * sizeof(unsigned char));
    layout.push(GL_UNSIGNED_BYTE, 2);
    ASSERT_EQ(layout.get_stride(), 5 * sizeof(unsigned char));
}
