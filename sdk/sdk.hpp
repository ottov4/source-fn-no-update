#pragma once
#include <d3d9.h>
#include <vector>
#include <string>
#include <algorithm>
#include "../security/StackMasker.h"
#define M_PI 3.14159265358979323846264338327950288419716939937510

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(double _x, double _y) : x(_x), y(_y) {}
	~Vector2() {}
	double x, y;
};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f) {}
	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	~Vector3() {}
	double x, y, z;
	inline double dot(Vector3 v) { return x * v.x + y * v.y + z * v.z; }
	inline double distance(Vector3 v) { return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0))); }
	Vector3 operator-(Vector3 v) { return Vector3(x - v.x, y - v.y, z - v.z); }
};

struct FQuat { double x, y, z, w; };
struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX to_matrix_with_scale()
	{
		D3DMATRIX m{};
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;
		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;
		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;
		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;
		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;
		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

template<class type>
class TArray
{
public:
	TArray() : data(nullptr), count(std::int32_t()), maxx(std::int32_t()) { }
	TArray(type* data, std::int32_t count, std::int32_t maxx) : data(data), count(count), maxx(maxx) { }

	const bool is_valid() const noexcept
	{
		return !(this->data == nullptr);
	}

	const std::int32_t size() const noexcept
	{
		return this->count;
	}

	type& operator[](std::int32_t index) noexcept
	{
		return this->data[index];
	}

	const type& operator[](std::int32_t index) const noexcept
	{
		return this->data[index];
	}

	bool is_valid_index(std::int32_t index) const noexcept
	{
		return index < this->size();
	}
protected:
	type* data;
	std::int32_t count;
	std::int32_t maxx;
};

D3DMATRIX matrix_multiplication(D3DMATRIX pm1, D3DMATRIX pm2)
{
	D3DMATRIX pout{};
	pout._11 = pm1._11 * pm2._11 + pm1._12 * pm2._21 + pm1._13 * pm2._31 + pm1._14 * pm2._41;
	pout._12 = pm1._11 * pm2._12 + pm1._12 * pm2._22 + pm1._13 * pm2._32 + pm1._14 * pm2._42;
	pout._13 = pm1._11 * pm2._13 + pm1._12 * pm2._23 + pm1._13 * pm2._33 + pm1._14 * pm2._43;
	pout._14 = pm1._11 * pm2._14 + pm1._12 * pm2._24 + pm1._13 * pm2._34 + pm1._14 * pm2._44;
	pout._21 = pm1._21 * pm2._11 + pm1._22 * pm2._21 + pm1._23 * pm2._31 + pm1._24 * pm2._41;
	pout._22 = pm1._21 * pm2._12 + pm1._22 * pm2._22 + pm1._23 * pm2._32 + pm1._24 * pm2._42;
	pout._23 = pm1._21 * pm2._13 + pm1._22 * pm2._23 + pm1._23 * pm2._33 + pm1._24 * pm2._43;
	pout._24 = pm1._21 * pm2._14 + pm1._22 * pm2._24 + pm1._23 * pm2._34 + pm1._24 * pm2._44;
	pout._31 = pm1._31 * pm2._11 + pm1._32 * pm2._21 + pm1._33 * pm2._31 + pm1._34 * pm2._41;
	pout._32 = pm1._31 * pm2._12 + pm1._32 * pm2._22 + pm1._33 * pm2._32 + pm1._34 * pm2._42;
	pout._33 = pm1._31 * pm2._13 + pm1._32 * pm2._23 + pm1._33 * pm2._33 + pm1._34 * pm2._43;
	pout._34 = pm1._31 * pm2._14 + pm1._32 * pm2._24 + pm1._33 * pm2._34 + pm1._34 * pm2._44;
	pout._41 = pm1._41 * pm2._11 + pm1._42 * pm2._21 + pm1._43 * pm2._31 + pm1._44 * pm2._41;
	pout._42 = pm1._41 * pm2._12 + pm1._42 * pm2._22 + pm1._43 * pm2._32 + pm1._44 * pm2._42;
	pout._43 = pm1._41 * pm2._13 + pm1._42 * pm2._23 + pm1._43 * pm2._33 + pm1._44 * pm2._43;
	pout._44 = pm1._41 * pm2._14 + pm1._42 * pm2._24 + pm1._43 * pm2._34 + pm1._44 * pm2._44;

	return pout;
}

D3DMATRIX to_matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radpitch = (rot.x * M_PI / 180);
	float radyaw = (rot.y * M_PI / 180);
	float radroll = (rot.z * M_PI / 180);
	float sp = sinf(radpitch);
	float cp = cosf(radpitch);
	float sy = sinf(radyaw);
	float cy = cosf(radyaw);
	float sr = sinf(radroll);
	float cr = cosf(radroll);
	D3DMATRIX matrix{};
	matrix.m[0][0] = cp * cy;
	matrix.m[0][1] = cp * sy;
	matrix.m[0][2] = sp;
	matrix.m[0][3] = 0.f;
	matrix.m[1][0] = sr * sp * cy - cr * sy;
	matrix.m[1][1] = sr * sp * sy + cr * cy;
	matrix.m[1][2] = -sr * cp;
	matrix.m[1][3] = 0.f;
	matrix.m[2][0] = -(cr * sp * cy + sr * sy);
	matrix.m[2][1] = cy * sr - cr * sp * sy;
	matrix.m[2][2] = cr * cp;
	matrix.m[2][3] = 0.f;
	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

struct Camera
{
	Vector3 location;
	Vector3 rotation;
	float fov;
};

struct FNRot
{
	double a;
	char pad_0008[24];
	double b;
	char pad_0028[424];
	double c;
};

namespace cache
{
	inline uintptr_t gworld;
	inline uintptr_t game_state;
	inline uintptr_t persistent_level;
	inline uintptr_t game_instance;
	inline uintptr_t local_players;
	inline uintptr_t player_controller;
	inline uintptr_t local_pawn;
	inline uintptr_t current_weapon;
	inline uintptr_t root_component;
	inline uintptr_t player_state;
	inline Vector3 localRelativeLocation;
	inline float closest_distance;
	inline uintptr_t closest_mesh;
	inline Camera local_camera;
	//std::vector<ImVec2> radarPoints;
}

Camera get_view_point()
{
	MASK
	Camera view_point{};
	uintptr_t location_pointer = read<uintptr_t>(cache::gworld + 0x110);
	uintptr_t rotation_pointer = read<uintptr_t>(cache::gworld + 0x120);
	FNRot fnrot{};
	fnrot.a = read<double>(rotation_pointer);
	fnrot.b = read<double>(rotation_pointer + 0x20);
	fnrot.c = read<double>(rotation_pointer + 0x1D0);
	view_point.location = read<Vector3>(location_pointer);
	view_point.rotation.x = asin(fnrot.c) * (180.0 / M_PI);
	view_point.rotation.y = ((atan2(fnrot.a * -1, fnrot.b) * (180.0 / M_PI)) * -1) * -1;
	view_point.fov = read<float>(cache::player_controller + 0x394) * 90.f;

	return view_point;
}

Vector2 project_world_to_screen(Vector3 world_location)
{
	MASK
	cache::local_camera = get_view_point();
	D3DMATRIX temp_matrix = to_matrix(cache::local_camera.rotation);
	Vector3 vaxisx = Vector3(temp_matrix.m[0][0], temp_matrix.m[0][1], temp_matrix.m[0][2]);
	Vector3 vaxisy = Vector3(temp_matrix.m[1][0], temp_matrix.m[1][1], temp_matrix.m[1][2]);
	Vector3 vaxisz = Vector3(temp_matrix.m[2][0], temp_matrix.m[2][1], temp_matrix.m[2][2]);
	Vector3 vdelta = world_location - cache::local_camera.location;
	Vector3 vtransformed = Vector3(vdelta.dot(vaxisy), vdelta.dot(vaxisz), vdelta.dot(vaxisx));
	if (vtransformed.z < 1) vtransformed.z = 1;

	return Vector2(settings::screen_center_x + vtransformed.x * ((settings::screen_center_x / tanf(cache::local_camera.fov * M_PI / 360))) / vtransformed.z, settings::screen_center_y - vtransformed.y * ((settings::screen_center_x / tanf(cache::local_camera.fov * M_PI / 360))) / vtransformed.z);
}

Vector3 get_entity_bone(uintptr_t mesh, int bone_id)
{
	MASK
	uintptr_t bone_array = read<uintptr_t>(mesh + BONE_ARRAY);
	if (bone_array == 0) bone_array = read<uintptr_t>(mesh + BONE_ARRAY_CACHE);
	FTransform bone = read<FTransform>(bone_array + (bone_id * 0x60));
	FTransform component_to_world = read<FTransform>(mesh + COMPONENT_TO_WORLD);
	D3DMATRIX matrix = matrix_multiplication(bone.to_matrix_with_scale(), component_to_world.to_matrix_with_scale());

	return Vector3(matrix._41, matrix._42, matrix._43);
}

bool is_visible(uintptr_t mesh)
{
	MASK
	float last_sumbit_time = read<float>(mesh + LAST_SUMBIT_TIME);
	float last_render_time_on_screen = read<float>(mesh + LAST_SUMBIT_TIME_ON_SCREEN);

	return last_render_time_on_screen + 0.06f >= last_sumbit_time;
}

//Vector2 worldToRadar(Vector3 location, Vector3 origin, Vector3 rotation, int width, float scale = 16.f)
//{
//	float x_diff = location.x - origin.x;
//	float z_diff = location.z - origin.z;
//	float yaw = rotation.y * M_PI / 180.0f;
//
//	float tempX = x_diff * cosf(yaw) + z_diff * sinf(yaw);
//	float tempZ = -x_diff * sinf(yaw) + z_diff * cosf(yaw);
//	x_diff = tempX;
//	z_diff = tempZ;
//
//	x_diff /= scale;
//	z_diff /= scale;
//
//	float radarCenter = width * 0.5f;
//	float xnew_diff = radarCenter + x_diff;
//	float ynew_diff = radarCenter + z_diff;
//
//	xnew_diff = std::clamp(xnew_diff, 4.0f, width - 4.0f);
//	ynew_diff = std::clamp(ynew_diff, 4.0f, width - 4.0f);
//
//	return Vector2(static_cast<int>(xnew_diff), static_cast<int>(ynew_diff));
//}

double getCrossDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

float getBulletDrop(float height, float depthPlayerTarget, float velocity, float gravity)
{
	float pitch = (atan2(height, depthPlayerTarget));
	float BulletVelocityXY = velocity * cos(pitch);
	float Time = depthPlayerTarget / BulletVelocityXY;
	float TotalVerticalDrop = (0.5f * gravity * Time * Time);

	return TotalVerticalDrop;
}

Vector3 calculateNewRotation(Vector3& zaz, Vector3& daz)
{
	Vector3 dalte = zaz - daz;
	Vector3 ongle;
	float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
	ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
	ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;

	if (dalte.x >= 0.f) ongle.y += 180.f;

	return ongle;
}

Vector3 getLoc(Vector3 Loc)
{
	Vector3 Location = Vector3(Loc.x, Loc.y, Loc.z);

	return Location;
}

std::string getRank(int32_t tier)
{
	MASK
	static const std::string ranks[] = {
		"Bronze 1", "Bronze 2", "Bronze 3",
		"Silver 1", "Silver 2", "Silver 3",
		"Gold 1", "Gold 2", "Gold 3",
		"Platinum 1", "Platinum 2", "Platinum 3",
		"Diamond 1", "Diamond 2", "Diamond 3",
		"Elite", "Champion", "Unreal", "Unranked"
	};

	if (tier >= 0 && tier < 18)
	{
		return ranks[tier];
	}
	else
	{
		return ranks[18];
	}
}

std::string getUsername(std::uintptr_t playerstate)
{
	MASK
	int pNameLength;
	uint16_t* pNameBufferPointer;
	int i;
	char v25;
	int v26;
	int v29;
	char16_t* pNameBuffer;

	uintptr_t pNameStructure = read<uintptr_t>(playerstate + 0xab0);
	pNameLength = read<int>(pNameStructure + 0x10);
	if (pNameLength <= 0)
		return "BOT";

	pNameBuffer = new char16_t[pNameLength];
	uintptr_t pNameEncryptedBuffer = read <uintptr_t>(pNameStructure + 0x8);
	PaysonDRV::ReadPhysicalMemory((PVOID)pNameEncryptedBuffer, pNameBuffer, pNameLength * sizeof(wchar_t));

	v25 = pNameLength - 1;
	v26 = 0;
	pNameBufferPointer = (uint16_t*)pNameBuffer;

	for (i = (v25) & 3;; *pNameBufferPointer++ += i & 7)
	{
		v29 = pNameLength - 1;
		if (!(uint32_t)pNameLength)
			v29 = 0;

		if (v26 >= v29)
			break;

		i += 3;
		++v26;
	}

	std::u16string temp_wstring(pNameBuffer);
	delete[] pNameBuffer;

	return std::string(temp_wstring.begin(), temp_wstring.end());
}