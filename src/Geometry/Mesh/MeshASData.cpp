#include <Mesh.h>

namespace RT
{
	MeshASData::MeshASData(MeshTriangle t) : t(t)
	{

	}

	PGeometry MeshASData::geometry()const
	{
		return std::make_shared<MeshTriangle>(t);
	}

	BoundingBox MeshASData::bbox()const
	{
		return t.getBoundingBox();
	}

	Transform MeshASData::transform()const
	{
		return Transform();
	}

	bool MeshASData::hasTransform()const
	{
		return false;
	}
}