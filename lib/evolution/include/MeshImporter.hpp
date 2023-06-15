#ifndef EVOLUTION_MESH_IMPORTER_HPP
#define EVOLUTION_MESH_IMPORTER_HPP

#include "Buffers.hpp"

#include <string>

namespace evolution
{
  Mesh fromFile(const std::string& filename);
}

#endif