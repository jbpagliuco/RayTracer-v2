#pragma once

#include <Util.h>
#include <VML.h>
#include <Ray.h>
#include <Color.h>
#include <map>

namespace RT
{
	struct ElementIntersection;
	class World;

	class Light
	{
	public:
		// Constructor.
		Light(bool bCastsShadows = true);

		// Destructor.
		virtual ~Light();

		// Returns the distance from the point to this light.
		virtual F32 getDistanceFromPoint(const VML::Vector& point)const = 0;
		// Returns the direction from the point to this light.
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point) = 0;

		// Calculate the radiance at the incident point.
		// @param ei - The incident point.
		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world) = 0;

		// Is this element in the shadow of this light?
		// @param ray - The ray.
		// @param ei - The intersection point.
		virtual bool inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const;

		virtual F32 g(const ElementIntersection& ei)const;

		virtual F32 pdf(const ElementIntersection& ei)const;

	protected:
		bool bCastsShadows;
	};

	typedef std::shared_ptr<Light> PLight;
	typedef std::vector<PLight> Lights;

	PLight LoadLight(const std::map<std::string, std::string>& params, World& world);
	PLight LoadLight(const std::string& params, World& world);
}