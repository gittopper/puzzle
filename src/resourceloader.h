#pragma once

#include <string>
#include <vector>

class ResourceLoader {
   public:
    virtual std::vector<char> readFile(std::string filename) = 0;
    virtual void setResourcesPath(std::string path) = 0;

    virtual ~ResourceLoader() {}
};
