#include "BeltedEllipsoid.h"
#include "Magnum/Mesh.h"
#include <Magnum/GL/Buffer.h>

namespace Magnum {
  namespace Primitives
  {
Trade::MeshData beltedEllipsoid(UnsignedInt rings, UnsignedInt slices, double a, double b, double c)
{
  // Compute ellipsoid
  auto belted_ellipsoid = GenerateParametricBeltedEllipsoidMesh(rings, slices, a, b, c);

  const std::size_t vertexCount = belted_ellipsoid.nv;
  const std::size_t triangleCount = belted_ellipsoid.nt;

  struct Vertex {
      Vector3 position;
      Vector3 normal;
  };

  Containers::Array<char> vertexData;
  Containers::arrayResize<Trade::ArrayAllocator>(vertexData, NoInit, sizeof(Vertex)*vertexCount);
  auto vertices = Containers::arrayCast<Vertex>(vertexData);
  Containers::StridedArrayView1D<Vector3> positions{vertices, &vertices[0].position, vertices.size(), sizeof(Vertex)};
  for(std::size_t i = 0; i != vertexCount; ++i)
  {
      positions[i] = {
        belted_ellipsoid.vertexArray[i].vx, 
        belted_ellipsoid.vertexArray[i].vy,
        belted_ellipsoid.vertexArray[i].vz
      };
  }
  Containers::StridedArrayView1D<Vector3> normals{vertices, &vertices[0].normal, vertices.size(), sizeof(Vertex)};
  for(std::size_t i = 0; i != positions.size(); ++i)
  {
    normals[i] = {
      belted_ellipsoid.vertexArray[i].nx,
      belted_ellipsoid.vertexArray[i].ny,
      belted_ellipsoid.vertexArray[i].nz
    };
  }

  Containers::Array<char> indexData{triangleCount*sizeof(TriangleMesh)};
  auto indices = Containers::arrayCast<UnsignedInt>(indexData);
  std::memcpy(indices.begin(), belted_ellipsoid.triangleArray, triangleCount*sizeof(TriangleMesh));

  return Trade::MeshData
  {
    MeshPrimitive::Triangles,
      std::move(indexData),
      Trade::MeshIndexData{indices},
      std::move(vertexData),
      {Trade::MeshAttributeData{Trade::MeshAttribute::Position, positions},
       Trade::MeshAttributeData{Trade::MeshAttribute::Normal, normals}
      }
  };
}
}
}
