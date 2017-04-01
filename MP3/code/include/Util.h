#pragma once

#define NOMINMAX

#include <stdint.h>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <assert.h>
#include <memory>
#include <P4Mem.h>

#define RT_SAFE_FREE(p) if (p) { delete p; p = nullptr; }
#define RT_SAFE_FREE_A(p) if (p) { delete[] p; p = nullptr; }
#define RT_SAFE_FREE_F(p, f) if (p) { f(p); p = nullptr; } 

#ifndef RT_ALIGN_MS
#if _MSC_VER && !__INTEL_COMPILER
#define RT_ALIGN_MS(alignment) __declspec(align(alignment))
#else
#define RT_ALIGN_MS(alignment)
#endif
#endif

#ifndef RT_ALIGN_GCC
#if __GNUC__
#define RT_ALIGN_GCC(alignment) __attribute__((aligned(alignment)))
#else
#define RT_ALIGN_GCC(alignment)
#endif
#endif

namespace RT
{
	typedef uint8_t byte;

	typedef int8_t I8;
	typedef uint8_t U8;

	typedef int16_t I16;
	typedef uint16_t U16;

	typedef int32_t I32;
	typedef uint32_t U32;

	typedef int64_t I64;
	typedef uint64_t U64;

	typedef float F32;
	typedef long double D64;

	// Single precision infinity
	const F32 F32_INF = std::numeric_limits<F32>::infinity();
	// Largest positive single precision value
	const F32 F32_MAX = (std::numeric_limits<F32>::max)();
	// Smallest negative single precision value
	const F32 F32_NMAX = -F32_MAX;
	// Smallest positive single precision value
	const F32 F32_MIN = (std::numeric_limits<F32>::min)();
	// Epsilon value for single precision floats
	const F32 F32_EPS= 1E-5f;

	// Double precision infinity
	const D64 D64_INF = std::numeric_limits<D64>::infinity();
	// Largest positive double precision value
	const D64 D64_MAX = (std::numeric_limits<D64>::max)();
	// Smallest negative double precision value
	const D64 D64_NMAX = -D64_MAX;
	// Smallest positive double precision value
	const D64 D64_MIN = (std::numeric_limits<D64>::min)();
	// Epsilon value for double precision floats
	const F32 D64_EPS = 1E-9f;

	const F32 PI = 3.1415927410125732421875;
	const F32 PI_DIV2 = PI / 2.0f;
	const F32 PI_DIV3 = PI / 3.0f;
	const F32 PI_DIV4 = PI / 4.0f;
	const F32 PI_DIV6 = PI / 6.0f;
	const F32 PI_MUL2 = PI * 2.0f;
	const F32 PI_3DIV2 = 3.0f * PI / 2.0f;
	const D64 INV_PI = 0.31830988618379067154;


	// Memory
	template<class T>
	std::shared_ptr<T> AllocateAligned16(const T& v)
	{
		T * raw = (T*)P4::AllocateAlignedMemory(sizeof(T), 16);
		return std::shared_ptr<T>(new(raw)T(v), P4::FreeAlignedMemory);
	}




	/* Holds 2 components */
	template <typename T>
	struct Vector2
	{
		Vector2<T>() {}
		Vector2<T>(T x, T y) { X = x; Y = y; }
		T X;
		T Y;
	};

	/* Holds 3 components */
	template <typename T>
	struct Vector3
	{
		union {
			struct { T x; T y; T z; };
			T v[3];
		};

		Vector3<T>() {}
		Vector3<T>(T x, T y, T z) : x(x), y(y), z(z) {}
	};
	typedef Vector3<I32> Vector3i;
	typedef Vector3<F32> Vector3f;
	typedef Vector3<D64> Vector3d;

	/* Holds 4 components */
	template <typename T>
	struct Vector4
	{
		Vector4<T>() {}
		Vector4<T>(T x, T y, T z, T w) { X = x; Y = y; Z = z; W = w; }
		T X;
		T Y;
		T Z;
		T W;
	};



	// A wrapper class that reads from files.
	class FileReader
	{
	public:
		// Open the specified file.
		// @param filename - The filename.
		FileReader(const std::string& filename);

		virtual ~FileReader();

		// Adds a string to the comment list.
		// @param comment - A prefix string, which if read, the file reader will skip the line.
		void AddCommentString(const std::string& comment);

		// Reads the next non-comment line.
		bool ReadLine(std::string &line);

		// Is the reader at the end of this file?
		bool EndOfFile()const;

	private:
		bool IsCommentString(const std::string& line)const;

	private:
		std::ifstream file;
		std::vector<std::string> comments;
	};


	// Splits a string by delim
	std::vector<std::string> SplitString(std::string s, const std::string &delim);

	// Removes the whitespace in the string.
	// Includes: " ", "\n", "\t", "\r"
	void RemoveWhitespace(std::string &s);
	// Removes the whitespace at the beginning and end of the string.
	// Includes: " ", "\n", "\t", "\r"
	void RemoveCapWhitespace(std::string &s);
	// Removes the whitespace at the beginning of the string.
	// Includes: " ", "\n", "\t", "\r"
	void RemoveLeadingWhitespace(std::string &s);
	// Removes the whitespace at the end of the string.
	// Includes: " ", "\n", "\t", "\r"
	void RemoveTrailingWhitespace(std::string &s);

	// Returns the time, using a high resolution clock.
	// Use DiffTime() to get elapsed time.
	std::chrono::high_resolution_clock::time_point GetTime();
	// Calculates time difference.
	U64 DiffTime(const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& end);

	template<typename T>
	T Clamp(const T& val, const T& min, const T& max);

	I32 RandInt();
	I32 RandInt(I32 l, I32 h);
	F32 RandFloat();
	F32 RandFloat(F32 l, F32 h);








	template<typename T>
	T Clamp(const T& val, const T& min, const T& max)
	{
		return (val < min) ? min : (val > max) ? max : val;
	}



	inline I32 RandInt()
	{
		return rand();
	}

	inline I32 RandInt(I32 l, I32 h)
	{
		return (I32)(RandFloat(0.0f, (F32)(h - l + 1)) + l);
	}

	inline F32 RandFloat()
	{
		return (F32)(RandInt() * (1.0 / (F32)RAND_MAX));
	}

	inline F32 RandFloat(F32 l, F32 h)
	{
		return RandFloat() * (h - l) + l;
	}
}