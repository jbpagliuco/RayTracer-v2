#include <Primitives.h>

namespace RT
{
	ConcaveSphere::ConcaveSphere(F32 radius) : Sphere(radius)
	{

	}

	ConcaveSphere::~ConcaveSphere()
	{

	}

	bool ConcaveSphere::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		if (Sphere::hits(outHitInfo, ray))
		{
			outHitInfo.normal.negate();
			return true;
		}

		return false;
	}
}