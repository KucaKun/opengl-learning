whole mingw with gcc, cmake and all is from https://winlibs.com/
profiler is from http://www.codersnotes.com/sleepy/
glew is downloaded as binary
glfw is built from source
imgui is built from source


TODO:
 - set mvp only once per shader
 - register buffor changes for just before rendering to do all once
 - clear buffer on scene exit
 - give scene access to data from outside in some big struct (like current frame or polled events or random generator data) 
 - handle mouse and keyboard input
 - 2d lighting scene 
 - maybe google benchmark for testing snippets
 - gpu time when gpu will actually have stuff to do