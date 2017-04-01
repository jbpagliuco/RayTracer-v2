#pragma once

#include <VML.h>
#include <Buffer.h>
#include <Sampler.h>
#include <ImageCV.h>
#include <map>

namespace RT
{
	class World;

	class Viewport
	{
	public:
		// Default constructor.
		Viewport() = default;

		// Creates a viewport with the specified width and height.
		// @param width - The width of the viewport.
		// @param height - The height of the viewport.
		Viewport(U32 width, U32 height);

		// Get the center (in world coordinates) on the pixel at (row, col).
		// @param row - The row of the pixel.
		// @param col - The col of the pixel.
		// @return The 3D world coordinates of this pixel.
		VML::VECTOR3F getPixelCenter(U32 row, U32 col)const;

		// Get a pointer to this viewport's sampler.
		Sampler* getSampler();

		// Get a unit square sample.
		VML::VECTOR3F getUnitSquareSample(U32 row, U32 col);

		// Scale the pixel width of this viewport.
		void scalePixelWidth(F32 scale);

		// Get the width of this viewport.
		U32 width()const;
		// Get the height of this viewport.
		U32 height()const;

	private:
		U32 w, h;
		F32 pixelWidth;
		Sampler sampler;
	};

	class Camera
	{
	public:
		// Default constructor.
		Camera();
		// Creates a camera
		Camera(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up);

		virtual ~Camera();

		// Sets the viewport of this camera.
		virtual void setViewport(Viewport vp);
		// Gets the viewport.
		Viewport getViewport()const;

		// Renders a single pixel.
		// @param row - The pixel's row.
		// @param col - The pixel's column.
		// @param pWorld - A pointer to the world to render.
		virtual Color renderPixel(U32 row, U32 col, World& world) = 0;

		// Gets the position of this camera.
		VML::Vector getPosition()const;

	private:
		void calculateBasis(const VML::VECTOR3F& eyePos, const VML::VECTOR3F& lookat, const VML::VECTOR3F& up);

	public:
		Color backgroundColor;

	protected:
		VML::Vector eye;
		VML::Vector u, v, w;
		F32 maxDepth;

		Viewport vp;

		friend class RenderingEngine;
	};
	typedef std::shared_ptr<Camera> PCamera;

	PCamera LoadCamera(const std::map<std::string, std::string>& params, World& world);
	PCamera LoadCamera(const std::string& params, World& world);
}