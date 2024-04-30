whole mingw with gcc, cmake and all is from https://winlibs.com/
profiler is from http://www.codersnotes.com/sleepy/
glew is downloaded as binary
glfw is built from source
imgui is built from source


TODO:
 - set mvp only once per shader
 - make pixel color one byte per channel
 - register buffor changes for just before rendering to do all once
 - handle removing stuff from master buffer
 - remove scene from window to scene-picker class, so that window can be included in scene
 - clear buffer on scene exit
 - move stuff from hpp to cpp files
 - generate shaders on the fly, not relying on text files
 - give scene access to data from outside in some big struct (like current frame or polled events or random generator data) 
 - global buffer registration to be aware of all buffers and their sizes
 - handle mouse and keyboard input
 - 2d lighting scene 
 - maybe google benchmark for testing snippets
 - gpu time when gpu will actually have stuff to do
 - ui and text rendering capabilities
 - procedural animations