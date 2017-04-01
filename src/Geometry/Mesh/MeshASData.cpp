#include <Mesh.h>

namespace RT
{
	MeshASData::MeshASData(PMeshTriangle t) : t(t)
	{

	}

	PGeometry MeshASData::geometry()const
	{
		return t;
	}

	BoundingBox MeshASData::bbox()const
	{
		return t->getBoundingBox();
	}

	Transform MeshASData::transform()const
	{
		return Transform();
	}
}