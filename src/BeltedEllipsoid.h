#pragma once

#include <Magnum/Mesh.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/MeshTools/RemoveDuplicates.h>
#include <Magnum/MeshTools/Subdivide.h>
#include <Magnum/Trade/ArrayAllocator.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Primitives/visibility.h>
#include <Magnum/Trade/Trade.h>

#include <mesh_generators.hpp>

namespace Magnum 
{
  namespace Primitives
  {
    MAGNUM_PRIMITIVES_EXPORT Trade::MeshData beltedEllipsoid(UnsignedInt rings, UnsignedInt slices, double a, double b, double c);
  }

}

