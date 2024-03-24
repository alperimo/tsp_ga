#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>

#include "point.h"

class FileReader{
    public:
        FileReader();

        std::vector<Point> ParseCsv(const std::string& file_path);
};

#endif