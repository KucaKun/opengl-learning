#pragma once
#include <GL/glew.h>
#include <functional>
#include <string>
#include <typeinfo>
#include <vector>
struct ProtoUniform {
    std::string type;
    std::string name;
};

class Uniform {
private:
    std::string type;
    std::string name;
    unsigned int location;
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
                    functor = [l = location, args]() { glUniform1f(l, args[0]); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform1d(l, args[0]); };
                }
                break;
            }
        case 2:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform2f(l, args[0], args[1]); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform2d(l, args[0], args[1]); };
                }
                break;
            }
        case 3:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform3f(l, args[0], args[1], args[2]); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform3d(l, args[0], args[1], args[2]); };
                }
                break;
            }
        case 4:
            {
                if (typeid(T) == typeid(float)) {
                    functor = [l = location, args]() { glUniform4f(l, args[0], args[1], args[2], args[3]); };
                } else if (typeid(T) == typeid(double)) {
                    functor = [l = location, args]() { glUniform4d(l, args[0], args[1], args[2], args[3]); };
                }
                break;
            }
        }
        functor();
    }

    operator unsigned int() const {
        return location;
    }
};
