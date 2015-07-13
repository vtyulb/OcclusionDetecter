#ifndef SUPERFILTER_H
#define SUPERFILTER_H

#include <QPair>

#include <myimage.h>

class SuperFilter
{
    public:
        SuperFilter(int width, int height);

        MyImage apply(const MyImage &target, const MyImage &colors);

    private:
        MyImage was, was2;

        void dfs(int x, int y, const MyImage &target, const MyImage &colors, int color, long long &sum, int &count);
        void dfsSetter(int x, int y, MyImage &result, const MyImage &colors, int color, int set);
};

#endif // SUPERFILTER_H
