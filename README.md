whole mingw with gcc, cmake and all is from https://winlibs.com/
profiler is from http://www.codersnotes.com/sleepy/
glew is downloaded as binary
glfw is built from source
imgui is built from source


TODO:

 - handle removing stuff from master buffer
   - object manager holds the ids of objects and can give and take
   - object manager is templated by object type to get rid of layout inside object manager

 - global buffer registration to be aware of all buffers and their sizes
   - check current gpu memory usage

 - make million particles faster (currently its 2.5fps)
    - optimize size of draw calls (not use upload_whole_batch_buffer)


 - clear buffer on scene exit
 - generate shaders on the fly, not relying on text files
 - handle mouse and keyboard input
 - 2d lighting scene 
 - gpu time when gpu will actually have stuff to do
 - ui and text rendering capabilities
 - procedural animations