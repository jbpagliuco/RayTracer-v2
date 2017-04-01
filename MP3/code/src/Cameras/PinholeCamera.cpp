#include <CameraTypes.h>

namespace RT
{
	PinholeCamera::PinholeCamera() : Camera()
	{

	}

	PinholeCamera::PinholeCamera(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up,
								F32 distanceToViewPlane, F32 zoom) : Camera(eyePos, lookat, up)
	{
		d = distanceToViewPlane;
		this->zoom = zoom;
	}
	
	void PinholeCamera::setViewport(Viewport vp)
	{
		Camera::setViewport(vp);

		this->vp.scalePixelWidth(zoom);
	}

	Color PinholeCamera::renderPixel(U32 row, U32 col, World& world)
	{
		VML::VECTOR3F pixelCoords = vp.getUnitSquareSample(row, col);
		VML::Vector rayDir = ((u * pixelCoords.x) + (v * pixelCoords.y) - (w * d)).v3Normalize();
		Ray ray(eye, rayDir);

		Color color;
		color = world.traceRayColor(ray);
		color.a = 1.0f;
		color.Clamp();

		return color;
	}



	PCamera LoadPinholeCamera(std::stringstream& ss, World& world, 
		const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up)
	{
		F32 distanceToViewPlane, pwScale;
		ss >> distanceToViewPlane >> pwScale;

		return AllocateAligned16(PinholeCamera(eyePos, lookat, up, distanceToViewPlane, pwScale));
	}
}