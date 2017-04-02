#include <LightTypes.h>

#include <MaterialTypes.h>
#include <RenderingEngine.h>

namespace RT
{
	AreaLight::AreaLight(PRenderable renderable) : renderable(renderable)
	{
		for (I32 i = 0; i < RenderingEngine::NumThreads; i++)
			sampleData.push_back(SampleData());

		pdfVal = renderable->geometry->pdf(ElementIntersection(), renderable->transform);
	}

	AreaLight::~AreaLight()
	{

	}

	F32 AreaLight::getDistanceFromPoint(const VML::Vector& point)const
	{
		return (sampleData[GetThreadIndex()].samplePoint - point).v3Length();
	}

	VML::Vector AreaLight::getDirectionFromPoint(const VML::Vector& point)
	{
		Transform t = renderable->transform;

		VML::Vector s = renderable->geometry->sample();
		s = t.transformVector(s);
		sampleData[GetThreadIndex()].samplePoint = VML::Vector(s.getX(), s.getY(), s.getZ(), 1.0f);

		VML::Vector wi = (sampleData[GetThreadIndex()].samplePoint - point).v3Normalize();
		VML::Vector normal = renderable->geometry->getNormalAtPoint(sampleData[GetThreadIndex()].samplePoint);
		normal = t.transformNormal(normal);
		sampleData[GetThreadIndex()].nDOTd = normal.negate().v3Dot(wi);

		return wi;
	}

	Color AreaLight::calculateRadiance(const ElementIntersection& ei, const World& world)
	{
		PMaterial mat = renderable->material;
		Emissive* e = (Emissive*)(&(*mat));

		if (sampleData[GetThreadIndex()].nDOTd > 0.0f)
			return e->getLe();
		else
			return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}

	F32 AreaLight::g(const ElementIntersection& ei)const
	{
		F32 d2 = (ei.rayInt.worldCoords - sampleData[GetThreadIndex()].samplePoint).v3LengthSq();
		
		return sampleData[GetThreadIndex()].nDOTd / d2;
	}

	F32 AreaLight::pdf(const ElementIntersection& ei)const
	{
		return pdfVal;
	}

	bool AreaLight::inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const
	{
		return Light::inShadow(ray, ei, world);
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