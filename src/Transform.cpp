#include <Transform.h>

#include <sstream>
#include <algorithm>

namespace RT
{
	Transform::Transform()
	{
		m = VML::MatrixIdentity();
		inv = VML::MatrixIdentity();
	}

	Transform::Transform(const VML::VECTOR3F& position, const VML::VECTOR3F& rotation, const VML::VECTOR3F& scale)
	{
		calculateMatrices(VML::Vector(position), rotation, VML::Vector(scale));
	}

	Transform::~Transform()
	{

	}

	void Transform::calculateMatrices(const VML::Vector& position, const VML::VECTOR3F& rotation, const VML::Vector scale)
	{
		VML::Matrix t = VML::MatrixTranslation(position);
		VML::Matrix r = VML::MatrixRotationEuler(rotation.x, rotation.y, rotation.z);
		VML::Matrix s = VML::MatrixScaling(scale);
		m = inv = t * r * s;
		inv.invert(nullptr);

		invT = VML::Matrix(inv);
		invT.transpose();
	}


	Ray Transform::transformRay(const Ray& ray)const
	{
		VML::Vector o = inv * ray.origin();
		VML::Vector d = inv * ray.direction();
		return Ray(o, d, false);
	}

	VML::Vector Transform::transformNormal(const VML::Vector& normal)const
	{
		VML::Vector tn = (invT * normal).v3Normalize();
		return VML::Vector(tn.getX(), tn.getY(), tn.getZ(), 0.0f);
	}

	VML::Vector Transform::transformVector(const VML::Vector& v)const
	{
		return m * v;
	}

	BoundingBox Transform::transformBox(const BoundingBox& box)const
	{
		VML::Vector min(box.min.x, box.min.y, box.min.z, 1.0f);
		VML::Vector max(box.max.x, box.max.y, box.max.z, 1.0f);

		VML::Vector vertices[8] = {
			VML::Vector(min.getX(), min.getY(), min.getZ(), 1.0f),
			VML::Vector(min.getX(), min.getY(), max.getZ(), 1.0f),
			VML::Vector(min.getX(), max.getY(), min.getZ(), 1.0f),
			VML::Vector(min.getX(), max.getY(), max.getZ(), 1.0f),
			VML::Vector(max.getX(), min.getY(), min.getZ(), 1.0f),
			VML::Vector(max.getX(), min.getY(), max.getZ(), 1.0f),
			VML::Vector(max.getX(), max.getY(), min.getZ(), 1.0f),
			VML::Vector(max.getX(), max.getY(), max.getZ(), 1.0f)
		};

		VML::VECTOR3F newMin, newMax;
		for (I32 i = 0; i < 8; i++)
		{
			VML::Vector v = vertices[i];
			VML::Vector t = m * v;

			newMin.x = std::min(newMin.x, t.getX());
			newMin.y = std::min(newMin.y, t.getY());
			newMin.z = std::min(newMin.z, t.getZ());

			newMax.x = std::max(newMax.x, t.getX());
			newMax.y = std::max(newMax.y, t.getY());
			newMax.z = std::max(newMax.z, t.getZ());
		}
		return BoundingBox(newMin, newMax);
	}




	Transform LoadTransform(const std::string& params)
	{
		std::stringstream ss(params);

		VML::VECTOR3F position, rotation, scale;
		ss >> position.x >> position.y >> position.z >>
			rotation.x >> rotation.y >> rotation.z >>
			scale.x >> scale.y >> scale.z;

		rotation.x = rotation.x * PI / 180.0f;
		rotation.y = rotation.y * PI / 180.0f;
		rotation.z = rotation.z * PI / 180.0f;

		return Transform(position, rotation, scale);
	}
}