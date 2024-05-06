#pragma once
namespace kckn {
    struct GlobalData {
        int window_width                    = 1920;
        int window_height                   = 1080;
        unsigned int max_vertex_buffer_size = 0xffffff;
        unsigned int max_index_buffer_size  = 0xfffff;
    };
    static GlobalData global_data;
} // namespace kckn
