#ifndef EVOLUTION_MESH_IMPORTER_HPP
#define EVOLUTION_MESH_IMPORTER_HPP

#include "Buffers.hpp"

#include <string>
#include <boost/filesystem.hpp>
namespace evolution
{
  Mesh fromFile(const std::string& filename);
  Mesh fromFile(const boost::filesystem::path& filename);
}

#endif