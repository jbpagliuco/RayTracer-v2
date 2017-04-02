#pragma once

#include <Util.h>
#include <VML.h>
#include <Primitives.h>
#include <AccelerationStructure.h>

#include <vector>

namespace RT
{
	struct Index
	{
		Index() : bHasUV(false) {}
		Index(U64 vertex, U64 normal, U64 uv) : vertex(vertex), normal(normal), uv(uv), bHasUV(true) {}
		Index(U64 vertex, U64 normal, bool bHasUV) : vertex(vertex), normal(normal), uv(uv), bHasUV(bHasUV) {}

		U64 vertex, normal, uv;
		bool bHasUV;
	};

	struct Face
	{
		Face() {}
		Face(const Index& v1, const Index& v2, const Index& v3) { v[0] = v1; v[1] = v2; v[2] = v3; }

		Index v[3];
	};

	class Mesh;
	class MeshTriangle : public Triangle
	{
	public:
		MeshTriangle() = default;
		MeshTriangle(Mesh * mesh, const Face& face);

		virtual ~MeshTriangle();

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& t, const Ray& ray)const override;

		virtual BoundingBox getBoundingBox()const override;

	private:
		Mesh * mesh;
		Face face;
	};
	typedef std::shared_ptr<MeshTriangle> PMeshTriangle;
	

	class MeshASData : public ASData
	{
	public:
		MeshASData(MeshTriangle t);

		virtual ~MeshASData() = default;

		virtual PGeometry geometry()const override;
		virtual BoundingBox bbox()const override;
		virtual Transform transform()const override;
		virtual bool hasTransform()const override;

	public:
		MeshTriangle t;
	};


	class Mesh : public Geometry
	{
	public:
		Mesh();

		virtual ~Mesh();

		// Add a vertex position.
		// @param pos - The world coordinates of the vertex.
		void addVertexPosition(const VML::VECTOR3F& pos);

		// Add a vertex normal.
		// @param normal - The normal of the vertex.
		void addVertexNormal(const VML::VECTOR3F& normal);

		// Add a uv coordinate.
		// @param uv - The uv texture coordinate.
		void addVertexUV(const VML::VECTOR2F& uv);

		// Add a triangle face.
		// @param face - The triangle face.
		void addFace(const Face& face);

		// Builds the mesh from the vertex and face data.
		void build();

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& t, const Ray& ray)const override;

		virtual BoundingBox getBoundingBox()const override;

	private:
		std::vector<VML::VECTOR3F> positions;
		std::vector<VML::VECTOR3F> normals;
		std::vector<VML::VECTOR2F> uvs;

		std::vector<MeshASData> triangles;
		PAccelerationStructure acc;

		friend class MeshTriangle;
		friend std::shared_ptr<Mesh> LoadMeshFromFile(const std::string& filename);
	};
	typedef std::shared_ptr<Mesh> PMesh;

	PGeometry LoadMesh(std::stringstream& ss, World& world);
	PMesh LoadMeshFromFile(const std::string& filename);
}