#pragma once

#include <glrenderer.h>

class GlutRenderer : public Geometry::GLRenderer
{
public:
  void init(int argc, char ** argv);
  void run();

  virtual void addMenuEntry(int i);

  friend class GlutBootstrap;
};

