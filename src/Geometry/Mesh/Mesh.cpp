#include <Mesh.h>

#include <ASTypes.h>

namespace RT
{
	Mesh::Mesh()
	{
		acc = std::make_unique<RegularGrid>();
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::addVertexPosition(const VML::VECTOR3F& pos)
	{
		positions.push_back(pos);
	}

	void Mesh::addVertexNormal(const VML::VECTOR3F& normal)
	{
		normals.push_back(normal);
	}

	void Mesh::addVertexUV(const VML::VECTOR2F& uv)
	{
		uvs.push_back(uv);
	}

	void Mesh::addFace(const Face& face)
	{
		MeshTriangle t(this, face);
		triangles.push_back(MeshASData(t));
	}

	void Mesh::build()
	{
		std::vector<PASData> elements;
		for (auto it = triangles.begin(); it != triangles.end(); it++)
		{
			MeshASData t = *it;
			std::shared_ptr<MeshASData> d = std::make_shared<MeshASData>(t);
			elements.push_back(d);
		}
		acc->build(elements);
	}

	bool Mesh::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		ElementIntersection ei;
		bool bHit = acc->hits(ei, ray);
		outHitInfo = ei.rayInt;
		return bHit;
	}

	bool Mesh::shadowHits(F32& t, const Ray& ray)const
	{
		return acc->shadowHits(F32_MAX, ray);
	}

	BoundingBox Mesh::getBoundingBox()const
	{
		return acc->getBoundingBox();
	}
}