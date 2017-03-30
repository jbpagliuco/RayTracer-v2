#include <LightTypes.h>

#include <World.h>

namespace RT
{
	AmbientOccluder::AmbientOccluder() {}

	AmbientOccluder::AmbientOccluder(F32 ls, Color color, F32 minAmount) : minAmount(minAmount), AmbientLight(ls, color)
	{
		sampler.mapSamplesToHemisphere(1.0f);
	}

	AmbientOccluder::~AmbientOccluder()
	{

	}

	F32 AmbientOccluder::getDistanceFromPoint(const VML::Vector& point)const
	{
		return 0.5f;
	}

	VML::Vector AmbientOccluder::getDirectionFromPoint(const VML::Vector& point)
	{
		return VML::VectorZero();
	}
	
	VML::Vector AmbientOccluder::sampleDirection()
	{
		VML::VECTOR3F sp = sampler.sampleHemisphere();
		return u * sp.x + v * sp.y + w * sp.z;
	}

	Color AmbientOccluder::calculateRadiance(const ElementIntersection& ei, const World& world)
	{
		w = ei.rayInt.normal;
		v = w.v3Cross(VML::Vector(0.0072f, 1.0f, 0.0034f, 0.0f));
		v.v3Normalize();
		u = v.v3Cross(w);

		Ray shadowRay(ei.rayInt.worldCoords, sampleDirection(), RAY_EPSILON);
		if (Light::inShadow(shadowRay, ei, world))
			return color * ls * minAmount;
		else
			return color * ls;
	}



	PLight LoadAmbientOccluderLight(std::stringstream& ss, World& world)
	{
		F32 ls, minAmount;
		Color color;

		ss >> ls >> color.r >> color.g >> color.b >> minAmount;

		world.ambient = AllocateAligned16(AmbientOccluder(ls, color, minAmount));
		return nullptr;
	}
}