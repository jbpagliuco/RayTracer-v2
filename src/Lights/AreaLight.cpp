#include <LightTypes.h>

#include <MaterialTypes.h>

namespace RT
{
	AreaLight::AreaLight(PRenderable renderable) : renderable(renderable)
	{

	}

	AreaLight::~AreaLight()
	{

	}

	F32 AreaLight::getDistanceFromPoint(const VML::Vector& point)const
	{
		return (samplePoint - point).v3Length();
	}

	VML::Vector AreaLight::getDirectionFromPoint(const VML::Vector& point)
	{
		Transform t = renderable->transform;

		VML::Vector s = renderable->geometry->sample();
		samplePoint = t.transformPoint(s);
		samplePoint = t.position + s;

		normal = renderable->geometry->getNormalAtPoint(samplePoint);
		normal = t.transformNormal(normal).negate();

		wi = (samplePoint - point).v3Normalize();

		return wi;
	}

	Color AreaLight::calculateRadiance(const ElementIntersection& ei, const World& world)
	{
		F32 nDOTd = normal.v3Dot(wi);

		PMaterial mat = renderable->material;
		Emissive* e = (Emissive*)(&(*mat));

		if (nDOTd > 0.0f)
			return e->getLe();
		else
			return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}

	F32 AreaLight::g(const ElementIntersection& ei)const
	{
		F32 nDOTd = normal.v3Dot(wi);
		F32 d2 = (ei.rayInt.worldCoords - samplePoint).v3LengthSq();
		
		return nDOTd / d2;
	}

	F32 AreaLight::pdf(const ElementIntersection& ei)const
	{
		// Doesn't account for scaling
		return renderable->geometry->pdf(ei);
	}

	bool AreaLight::inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const
	{
		return Light::inShadow(ray, ei, world);

		if (!bCastsShadows)
			return false;

		F32 ts = (samplePoint - ray.origin()).v3Dot(ray.direction());

		bool bHit;
		world.traceRayIntersections(bHit, ts, ray);

		return bHit;
	}




	PLight LoadAreaLight(std::stringstream& ss, World& world)
	{
		std::string name;
		ss >> name;

		// Remove @
		name = name.substr(1);
		PRenderable r = world.getRenderables()[name];
		return std::make_shared<AreaLight>(r);
	}
}