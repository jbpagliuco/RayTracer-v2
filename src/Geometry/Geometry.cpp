#include <Geometry.h>

#include <sstream>
#include <Mesh.h>
#include <World.h>
#include <Primitives.h>

namespace RT
{
	BoundingBox Geometry::getBoundingBox()const
	{
		return BoundingBox();
	}

	bool Geometry::hasBounds()const
	{
		return true;
	}

	F32 Geometry::pdf(const ElementIntersection& ei)const
	{
		return 0.0f;
	}

	VML::Vector Geometry::sample()
	{
		return VML::VectorZero();
	}

	VML::Vector Geometry::getNormalAtPoint(const VML::Vector& point)const
	{
		return VML::VectorZero();
	}





	typedef PGeometry(*GeometryLoader)(std::stringstream&, World&);
	std::map<std::string, GeometryLoader> loaders = {
		{ "sphere", LoadSphere },
		{ "plane", LoadPlane },
		{ "tri", LoadTriangle },
		{ "disk", LoadDisk },
		{ "rect", LoadRectangle }
	};

	PGeometry LoadGeometry(const std::map<std::string, std::string>& params, World& world)
	{
		std::string type = params.at("type");
		std::stringstream ss(params.at("params"));

		return loaders[type](ss, world);
	}

	PGeometry LoadGeometry(const std::string& params, World& world)
	{
		std::stringstream ss(params);

		std::map<std::string, std::string> p;
		ss >> p["type"];

		std::string curr;
		while (!(ss >> curr).eof())
			p["params"] += curr + " ";
		p["params"] += curr;

		return LoadGeometry(p, world);
	}
}