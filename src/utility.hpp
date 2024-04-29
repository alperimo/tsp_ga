#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>

class Utility{
    public:
        template<typename T>
        static T rand(){
            return static_cast<T>(std::rand());
        }
};

#endif