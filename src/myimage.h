#ifndef MYIMAGE
#define MYIMAGE

typedef unsigned char byte;

struct MyImage {
    int width;
    int height;

    byte **bright;

    const byte* operator[](int y) const { return bright[y]; }
    byte* operator[](int y) { return bright[y]; }
};

#endif // MYIMAGE

