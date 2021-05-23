#pragma once
#include "core.h"
#include "vector"

namespace paecs
{
    class AbstractComponentPool
    {
    private:
        /* data */
    public:
        // AbstractComponentPool(/* args */);
    };

    template <typename T>
    class ComponentPool : public AbstractComponentPool
    {

    public:
        ComponentPool(int size = config::DEFAULT_POOL_SIZE)
        {
            resize(size);
        }
        // ~ComponentPool();
        // virtual ~Pool() {}

        inline bool isEmpty() const
        {
            return data.empty();
        }

        inline unsigned int getSize() const
        {
            return data.size();
        }

        inline void resize(int n)
        {
            data.resize(n);
        }

        inline void clear()
        {
            data.clear();
        }

        inline bool set(unsigned int index, T object)
        {
            assert(index < getSize());
            data[index] = object;
            return true;
        }

        inline T &get(unsigned int index)
        {
            assert(index < getSize());
            return static_cast<T &>(data[index]);
        }

        inline void add(T object)
        {
            data.push_back(object);
        }

        T &operator[](unsigned int index)
        {
            return data[index];
        }

        const T &operator[](unsigned int index) const
        {
            return data[index];
        }

        inline std::vector<T> &getData()
        {
            return data;
        }

    private:
        std::vector data;
        /* data */
    };
}