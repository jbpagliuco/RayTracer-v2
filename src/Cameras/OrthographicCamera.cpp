#include <CameraTypes.h>

namespace RT
{
	OrthographicCamera::OrthographicCamera() : Camera()
	{

	}

	OrthographicCamera::OrthographicCamera(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up,
											F32 halfWidth) 
										: Camera(eyePos, lookat, up)
	{
		this->halfWidth = halfWidth;

		forwardDirection = w;
		forwardDirection.negate();
	}

	Color OrthographicCamera::renderPixel(U32 row, U32 col, World& world)
	{
		VML::VECTOR3F pixelCoords = vp.getUnitSquareSample(row, col);
		pixelCoords.x *= halfWidth;
		pixelCoords.y *= halfWidth;
		VML::Vector rayOriginWorld = (u * pixelCoords.x) + (v * pixelCoords.y);
		Ray ray(eye + rayOriginWorld, forwardDirection);

		Color color;
		color = world.traceRayColor(ray);
		color.a = 1.0f; 
		color.Clamp();

		return color;
	}


	PCamera LoadOrthoCamera(std::stringstream& ss, World& world,
		const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up)
	{
		F32 halfWidth;
		ss >> halfWidth;
		
		return AllocateAligned16(OrthographicCamera(eyePos, lookat, up, halfWidth));
	}
}