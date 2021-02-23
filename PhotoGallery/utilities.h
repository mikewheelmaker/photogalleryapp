#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>

struct PhotoInformation {
    QString fileURL;
    QString filePath;
    QString fileThumbnailURL;
    QString fileName;
    unsigned int width;
    unsigned int height;
    unsigned long long sizeInBytes;
    /*unsigned int index;*/
};

#endif // UTILITIES_H
