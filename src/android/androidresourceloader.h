#pragma once

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <jni.h>
#include <resourceloader.h>

using namespace std;

class AndroidResourceLoader : public ResourceLoader {
  public:
    AndroidResourceLoader(AAssetManager* manager);
    virtual std::vector<char> readFile(string filename);
    virtual void setResourcesPath(string path);

  private:
    string resPath_;
    AAssetManager* assetManager_;
};
