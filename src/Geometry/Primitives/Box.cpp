#include <Primitives.h>

namespace RT
{
	Box::Box() : bb(VML::VECTOR3F(-1.0f, -1.0f, -1.0f), VML::VECTOR3F(1.0f, 1.0f, 1.0f))
	{
	}

	bool Box::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		D64 t0, t1;
		Vector3d tmin, tmax, abc;
		bool bHit = bb.hits(outHitInfo, ray, t0, t1, tmin, tmax, abc);
		
		if (bHit)
		{
			// Calculate normal
			VML::Vector normals[3] = {
				VML::Vector(1.0f, 0.0f, 0.0f, 0.0f),
				VML::Vector(0.0f, 1.0f, 0.0f, 0.0f),
				VML::Vector(0.0f, 0.0f, 1.0f, 0.0f)
			};

			if (t0 >= 0.0f)
			{
				if (tmin.x > tmin.y && tmin.x > tmin.z)
					outHitInfo.normal = (abc.x >= 0.0) ? normals[0].negate() : normals[0];
				else if (tmin.y > tmin.z)
					outHitInfo.normal = (abc.y >= 0.0) ? normals[1].negate() : normals[1];
				else
					outHitInfo.normal = (abc.z >= 0.0) ? normals[2].negate() : normals[2];
			}
			else
			{
				if (tmax.x < tmax.y && tmax.x < tmax.z)
					outHitInfo.normal = (abc.x >= 0.0) ? normals[0] : normals[0].negate();
				else if (tmax.y < tmax.z)
					outHitInfo.normal = (abc.y >= 0.0) ? normals[1] : normals[1].negate();
				else
					outHitInfo.normal = (abc.z >= 0.0) ? normals[2] : normals[2].negate();
			}
		}

		return bHit;
	}

	bool Box::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection out;
		bool bHit = bb.hits(out, ray);
		tmin = out.t;
		return bHit;
	}

	BoundingBox Box::getBoundingBox()const
	{
		return bb;
	}




	PGeometry LoadBox(std::stringstream& ss, World& world)
	{
		return AllocateAligned16(Box());
	}
}