#pragma once

#include <Geometry.h>
#include <World.h>

namespace RT
{
	class Plane : public Geometry
	{
	public:
		// Creates a plane with a normal of (0, 1, 0).
		Plane();

		// Default destructor.
		virtual ~Plane() = default;

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& tmin, const Ray& ray)const override;

		virtual bool hasBounds()const override;

	private:
		bool findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const;
	};
	PGeometry LoadPlane(std::stringstream&, World&);

	class Sphere : public Geometry
	{
	public:
		// Creates a unit sphere.
		Sphere();

		// Creates a sphere.
		// @param radius - The radius of the sphere.
		Sphere(F32 radius);

		virtual ~Sphere() = default;

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& tmin, const Ray& ray)const override;

		virtual BoundingBox getBoundingBox()const override;

	private:
		bool findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const;

	private:
		F32 radius;
	};
	PGeometry LoadSphere(std::stringstream&, World&);

	class Triangle : public Geometry
	{
	public:
		Triangle(VML::VECTOR3F p1, VML::VECTOR3F p2, VML::VECTOR3F p3);

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& tmin, const Ray& ray)const override;

		virtual BoundingBox getBoundingBox()const override;

	private:
		bool findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const;

	private:
		VML::Vector normal;
		VML::VECTOR3F p1, p2, p3;
	};
	PGeometry LoadTriangle(std::stringstream&, World&);

	class Disk : public Geometry
	{
	public:
		Disk();

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& tmin, const Ray& ray)const override;

		virtual BoundingBox getBoundingBox()const override;

	private:
		bool findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const;

	protected:
		const VML::Vector normal;
	};
	PGeometry LoadDisk(std::stringstream&, World&);

	class Rectangle : public Geometry
	{
	public:
		// Creates a rectangle.
		Rectangle();

		// Default destructor.
		virtual ~Rectangle() = default;

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32& tmin, const Ray& ray)const override;

		virtual BoundingBox getBoundingBox()const override;

		virtual F32 pdf(const ElementIntersection& ei)const;

		virtual VML::Vector sample();

		virtual VML::Vector getNormalAtPoint(const VML::Vector& point)const;
		
	private:
		virtual bool findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const;

	private:
		VML::Vector p0, a, b, normal;
		F32 invArea;
		Sampler sampler;
	};
	PGeometry LoadRectangle(std::stringstream&, World&);
}