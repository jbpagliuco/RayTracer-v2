#pragma once

#include <Camera.h>
#include <World.h>

namespace RT
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera();

		// Creates an orthographic camera.
		// @param eyePos - The position of this camera.
		// @param lookat - The lookat point of the camera.
		// @param up - The world up vector.
		// @param halfWidth - The halfwidth of the viewport window.
		OrthographicCamera(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up,
			F32 halfWidth);

		virtual Color renderPixel(U32 row, U32 col, World& world) override;

	protected:
		VML::Vector forwardDirection;
		F32 halfWidth;
	};
	PCamera LoadOrthoCamera(std::stringstream&, World&, const VML::VECTOR3F&, const VML::VECTOR3F&, const VML::VECTOR3F&);

	class PinholeCamera : public Camera
	{
	public:
		PinholeCamera();

		// Creates a pinhole camera.
		// @param eyePos - The position of this camera.
		// @param lookat - The lookat point of the camera.
		// @param up - The world up vector.
		// @param distanceToViewPlane - The distance from the camera to the view plane.
		// @param zoom - The zoom factor of this camera.
		PinholeCamera(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up,
			F32 distanceToViewPlane, F32 zoom);

		virtual void setViewport(Viewport vp) override;

		virtual Color renderPixel(U32 row, U32 col, World& world) override;

	protected:
		// Distance to the viewplane
		F32 d;
		F32 zoom;
	};
	PCamera LoadPinholeCamera(std::stringstream&, World&, const VML::VECTOR3F&, const VML::VECTOR3F&, const VML::VECTOR3F&);
}