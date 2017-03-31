#include <Camera.h>
#include <CameraTypes.h>

namespace RT
{
	Camera::Camera()
	{
		calculateBasis(VML::VECTOR3F(0.0f, 0.0f, 0.0f), VML::VECTOR3F(0.0f, 0.0f, -1.0f), VML::VECTOR3F(0.0f, 1.0f, 0.0f));
	}

	Camera::Camera(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up)
	{
		calculateBasis(eyePos, lookat, up);
	}

	Camera::~Camera()
	{

	}

	void Camera::calculateBasis(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up)
	{
		eye = VML::Vector(eyePos);

		w = (eye - VML::Vector(lookat)).v3Normalize();
		u = (VML::Vector(up).v3Cross(w)).v3Normalize();
		v = w.v3Cross(u);
	}

	void Camera::setViewport(Viewport vp)
	{
		this->vp = vp;
	}

	Viewport Camera::getViewport()const
	{
		return vp;
	}

	VML::Vector Camera::getPosition()const
	{
		return eye;
	}




	typedef PCamera(*PCameraLoader)(std::stringstream&, World&, const VML::VECTOR3F&, const VML::VECTOR3F&, const VML::VECTOR3F&);
	std::map<std::string, PCameraLoader> loaders = {
		{ "pinhole", LoadPinholeCamera },
		{ "ortho", LoadOrthoCamera }
	};

	PCamera LoadCamera(const std::map<std::string, std::string>& params, World& world)
	{
		std::string type = params.at("type");

		VML::VECTOR3F pos, lookat, up;

		std::stringstream ss(params.at("pos"));
		ss >> pos.x >> pos.y >> pos.z;

		ss = std::stringstream(params.at("lookat"));
		ss >> lookat.x >> lookat.y >> lookat.z;

		ss = std::stringstream(params.at("up"));
		ss >> up.x >> up.y >> up.z;

		ss = std::stringstream(params.at("params"));

		return loaders[type](ss, world, pos, lookat, up);
	}

	PCamera LoadCamera(const std::string& params, World& world)
	{
		std::stringstream ss(params);

		std::map<std::string, std::string> p;
		ss >> p["type"];

		std::string curr;
		while (!(ss >> curr).eof())
			p["params"] += curr + " ";
		p["params"] += curr;

		return LoadCamera(p, world);
	}
}