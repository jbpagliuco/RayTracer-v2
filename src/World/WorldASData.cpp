#include <World.h>

namespace RT
{
	WorldASData::WorldASData(PRenderable& r) : r(r)
	{

	}

	PGeometry WorldASData::geometry()const
	{
		return r->geometry;
	}

	BoundingBox WorldASData::bbox()const
	{
		return r->geometry->getBoundingBox();
	}

	Transform WorldASData::transform()const
	{
		return r->transform;
	}
}