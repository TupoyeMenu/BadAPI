#pragma once
#include "gta/pointers.hpp"
#include "gta/script/natives.hpp"

#include <random>

namespace big::math
{
	inline float deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	inline float distance_between_vectors(Vector3 a, Vector3 b)
	{
		return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}

	inline float distance_between_vectors(rage::fvector3 a, rage::fvector3 b)
	{
		return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}

	inline Vector3 rotation_to_direction(Vector3 rotation)
	{
		float x = deg_to_rad(rotation.x);
		float z = deg_to_rad(rotation.z);

		float num = abs(cos(x));

		return Vector3{static_cast<float>(-sin(z)) * num, static_cast<float>(cos(z)) * num, static_cast<float>(sin(x))};
	}

	inline Vector3 raycast_coords(Vector3 coord, Vector3 rot, Entity ignore)
	{
		BOOL hit;
		Vector3 end_coords;
		Vector3 surface_normal;
		Entity hit_entity;
		Vector3 dir = math::rotation_to_direction(rot);
		Vector3 far_coords;

		far_coords.x = coord.x + dir.x * 1000;
		far_coords.y = coord.y + dir.y * 1000;
		far_coords.z = coord.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(coord.x,
		    coord.y,
		    coord.z,
		    far_coords.x,
		    far_coords.y,
		    far_coords.z,
		    -1,
		    ignore,
		    7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &end_coords, &surface_normal, &hit_entity);
		return end_coords;
	}

	// [0, max_value)
	template<typename T = int>
	inline T rand(T max_value)
	{
		static std::random_device seed;
		static std::mt19937 gen{seed()};
		std::uniform_int_distribution<T> dist{0, max_value - 1};

		return dist(gen);
	}

	// [min_value, max_value]
	template<typename T = int>
	inline T rand(T min_value, T max_value)
	{
		static std::random_device seed;
		static std::mt19937 gen{seed()};
		std::uniform_int_distribution<T> dist{min_value, max_value};

		return dist(gen);
	}
}
