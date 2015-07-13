#include "superfilter.h"

namespace {
    const int MAX_COLOR_DIFF = 28;
}

SuperFilter::SuperFilter(int width, int height):
    was(MyImage(width, height)),
    was2(MyImage(width, height))
{
}

MyImage SuperFilter::apply(const MyImage &target, const MyImage &colors) {
    for (int i = 0; i < was.height; i++)
        for (int j = 0; j < was.width; j++) {
            was[i][j] = false;
            was2[i][j] = false;
        }

    MyImage result(target.width, target.height);

    for (int i = 0; i < was.height; i++)
        for (int j = 0; j < was.width; j++)
            if (!(was[i][j])) {
                long long sum = 0;
                int count = 0;
                dfs(j, i, target, colors, colors[i][j], sum, count);
                dfsSetter(j, i, result, colors, colors[i][j], sum / count);
            }

    return result;
}

void SuperFilter::dfs(int x, int y, const MyImage &target, const MyImage &colors, int color, long long &sum, int &count) {
    if (x < 0 || y < 0 || x >= target.width || y >= target.height ||
            was[y][x] || abs(color - colors[y][x]) > MAX_COLOR_DIFF)
        return;

    was[y][x] = true;
    count++;
    sum += target[y][x];

    for (int i = 0; i < 4; i++)
        dfs(x + dx[i], y + dy[i], target, colors, color, sum, count);


}

void SuperFilter::dfsSetter(int x, int y, MyImage &result, const MyImage &colors, int color, int set) {
    if (x < 0 || y < 0 || x >= colors.width || y >= colors.height ||
            was2[y][x] || abs(color - colors[y][x]) > MAX_COLOR_DIFF)
        return;

    was2[y][x] = true;
    result[y][x] = set;
    for (int i = 0; i < 4; i++)
        dfsSetter(x + dx[i], y + dy[i], result, colors, color, set);

}
