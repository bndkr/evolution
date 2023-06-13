#ifndef EVOLUTION_ENGINE_HPP
#define EVOLUTION_ENGINE_HPP

#include <vector>

#include "Buffers.hpp"

#include "assimp/mesh.h"

namespace evolution
{

  typedef uint32_t MeshId;

  // this class will represent any 'state' that evolution game engine
  // holds as well as a handle for the client to access context-specific
  // data.
  class Engine
  {
  public:
    // c'tor
    Engine(); // input - screen size?

    MeshId addMesh(const Mesh& mesh);

    void enableMesh(const MeshId& mesh);

    void disableMesh(const MeshId& mesh);

    // intended on going inside the client's main loop.
    void drawAllEnabledMeshes();

    void updateMesh(MeshId mesh);
  };
} // namespace evolution

#endif