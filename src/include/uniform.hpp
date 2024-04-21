#pragma once
#include <GL/glew.h>
#include <functional>
#include <string>
#include <typeinfo>
#include <vector>
#define ARGS1 args[0]
#define ARGS2 args[0], args[1]
#define ARGS3 args[0], args[1], args[2]
#define ARGS4 args[0], args[1], args[2], args[3]
struct ProtoUniform {
    std::string type;
    std::string name;
};

class Uniform {
private:
    std::string type;
    std::string name;
    int location;
    unsigned int program_id;

public:
    Uniform(ProtoUniform proto, unsigned int program_id);

    template <typename T>
    void set_value(std::vector<T> args) {
        std::function<void()> functor;
        switch (args.size()) {
        case 1:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform1f(l, ARGS1); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform1d(l, ARGS1); };
                } else if (typeid(T) == typeid(int)) {
                    functor = [l = location, args]() { glUniform1i(l, ARGS1); };
                }
                break;
            }
        case 2:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform2f(l, ARGS2); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform2d(l, ARGS2); };
                } else if (typeid(T) == typeid(int)) {
                    functor = [l = location, args]() { glUniform2i(l, ARGS2); };
                }
                break;
            }
        case 3:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform3f(l, ARGS3); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform3d(l, ARGS3); };
                } else if (typeid(T) == typeid(int)) {
                    functor = [l = location, args]() { glUniform3i(l, ARGS3); };
                }
                break;
            }
        case 4:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform4f(l, ARGS4); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform4d(l, ARGS4); };
                } else if (typeid(T) == typeid(int)) {
                    functor = [l = location, args]() { glUniform4i(l, ARGS4); };
                }
                break;
            }
        }
        functor();
    }

    operator int() const {
        return location;
    }
};
#undef ARGS1
#undef ARGS2
#undef ARGS3
#undef ARGS4