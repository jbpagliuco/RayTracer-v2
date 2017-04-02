#include <Mesh.h>

namespace RT
{
	MeshTriangle::MeshTriangle(Mesh* mesh, const Face& face) : mesh(mesh), face(face)
	{

	}

	MeshTriangle::~MeshTriangle()
	{

	}

	bool MeshTriangle::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		VML::VECTOR3F v0 = mesh->positions[face.v[0].vertex];
		VML::VECTOR3F v1 = mesh->positions[face.v[1].vertex];
		VML::VECTOR3F v2 = mesh->positions[face.v[2].vertex];

		D64 beta, gamma, t;
		VML::VECTOR3F points[3] = { v0, v1, v2 };
		if (!Triangle::findBarycentricCoords(beta, gamma, t, points, ray))
			return false;


		outHitInfo.t = (F32)t;
		outHitInfo.worldCoords = ray.getPointAlongRay((F32)t);
		outHitInfo.normal =
			(VML::Vector(mesh->normals[face.v[0].normal]) * (1.0f - (F32)beta - (F32)gamma)) +
			(VML::Vector(mesh->normals[face.v[1].normal]) * (F32)beta) +
			(VML::Vector(mesh->normals[face.v[2].normal]) * (F32)gamma);
		outHitInfo.normal.v3Normalize();

		// We have texture coordinates
		if (face.v[0].bHasUV)
		{
			VML::VECTOR2F uv[3] = { mesh->uvs[face.v[0].uv], mesh->uvs[face.v[1].uv], mesh->uvs[face.v[2].uv] };
			outHitInfo.uv = VML::VECTOR2F(0.0f, 0.0f);

			outHitInfo.uv.x += ((1.0f - (F32)beta - (F32)gamma) * uv[0].x);
			outHitInfo.uv.y += ((1.0f - (F32)beta - (F32)gamma) * (1.0f - uv[0].y));

			outHitInfo.uv.x += ((F32)beta * uv[1].x);
			outHitInfo.uv.y += ((F32)beta * (1.0f - uv[1].y));

			outHitInfo.uv.x += ((F32)gamma * uv[2].x);
			outHitInfo.uv.y += ((F32)gamma * (1.0f - uv[2].y));
		}

		return true;
	}

	bool MeshTriangle::shadowHits(F32& tmin, const Ray& ray)const
	{
		VML::VECTOR3F v0 = mesh->positions[face.v[0].vertex];
		VML::VECTOR3F v1 = mesh->positions[face.v[1].vertex];
		VML::VECTOR3F v2 = mesh->positions[face.v[2].vertex];

		D64 beta, gamma, t;
		VML::VECTOR3F points[3] = { v0, v1, v2 };
		if (!Triangle::findBarycentricCoords(beta, gamma, t, points, ray))
			return false;

		tmin = (F32)t;
		return true;
	}

	BoundingBox MeshTriangle::getBoundingBox()const
	{
		VML::VECTOR3F v1 = mesh->positions[face.v[0].vertex];
		VML::VECTOR3F v2 = mesh->positions[face.v[1].vertex];
		VML::VECTOR3F v3 = mesh->positions[face.v[2].vertex];

		VML::VECTOR3F min(
			std::min(v1.x, std::min(v2.x, v3.x)),
			std::min(v1.y, std::min(v2.y, v3.y)),
			std::min(v1.z, std::min(v2.z, v3.z)));

		VML::VECTOR3F max(
			std::max(v1.x, std::max(v2.x, v3.x)),
			std::max(v1.y, std::max(v2.y, v3.y)),
			std::max(v1.z, std::max(v2.z, v3.z)));

		return BoundingBox(min, max, true);
	}
}