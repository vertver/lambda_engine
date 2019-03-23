/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "MathTypes.h"

template
<typename T>
class LVector4
{
public:
	inline LVector4<T> operator += (LVector4<T> v)	{ return add(v); }
	inline LVector4<T> operator += (const T p)		{ return add(p); }
	inline LVector4<T> operator -= (LVector4<T> v)	{ return sub(v); }
	inline LVector4<T> operator -= (const T p)		{ return sub(p); }
	inline LVector4<T> operator *= (LVector4<T> v)	{ return mul(v); }
	inline LVector4<T> operator *= (const T p)		{ return mul(p); }
	inline LVector4<T> operator /= (LVector4<T> v)	{ return div(v); }
	inline LVector4<T> operator /= (const T p)		{ return div(p); }

	// 0 - x, 1 - y, 2 - z, 3 - alpha
	T ThisVector[4];

	// x, y, z and alpha
	inline void set(const T _1, const T _2, const T _3, const T _4 = 1)
	{
		ThisVector[0] = _1;
		ThisVector[1] = _2;
		ThisVector[2] = _3;
		ThisVector[3] = _4;
	}

	// set another vector
	inline void set(LVector4<T>& vec)
	{
		ThisVector[0] = vec.ThisVector[0];
		ThisVector[1] = vec.ThisVector[1];
		ThisVector[2] = vec.ThisVector[2];
		ThisVector[3] = vec.ThisVector[3];
	}

	// set value to all points
	inline void set(T value)
	{
		ThisVector[0] = value;
		ThisVector[1] = value;
		ThisVector[2] = value;
		ThisVector[3] = value;
	}

	// x, y, z and alpha
	inline void sub(const T _1, const T _2, const T _3, const T _4 = 1)
	{
		ThisVector[0] -= _1;
		ThisVector[1] -= _2;
		ThisVector[2] -= _3;
		ThisVector[3] -= _4;
	}

	// sub another vector
	inline void sub(LVector4<T>& vec)
	{
		ThisVector[0] -= vec.ThisVector[0];
		ThisVector[1] -= vec.ThisVector[1];
		ThisVector[2] -= vec.ThisVector[2];
		ThisVector[3] -= vec.ThisVector[3];
	}

	// sub value to all points
	inline void sub(T value)
	{
		ThisVector[0] -= value;
		ThisVector[1] -= value;
		ThisVector[2] -= value;
		ThisVector[3] -= value;
	}

	// x, y, z and alpha
	inline void add(const T _1, const T _2, const T _3, const T _4 = 1)
	{
		ThisVector[0] += _1;
		ThisVector[1] += _2;
		ThisVector[2] += _3;
		ThisVector[3] += _4;
	}

	// add another vector
	inline void add(LVector4<T>& vec)
	{
		ThisVector[0] += vec.ThisVector[0];
		ThisVector[1] += vec.ThisVector[1];
		ThisVector[2] += vec.ThisVector[2];
		ThisVector[3] += vec.ThisVector[3];
	}

	// add value to all points
	inline void add(T value)
	{
		ThisVector[0] += value;
		ThisVector[1] += value;
		ThisVector[2] += value;
		ThisVector[3] += value;
	}

	// x, y, z and alpha
	inline void mul(const T _1, const T _2, const T _3, const T _4 = 1)
	{
		ThisVector[0] *= _1;
		ThisVector[1] *= _2;
		ThisVector[2] *= _3;
		ThisVector[3] *= _4;
	}

	// multiply another vector
	inline void mul(LVector4<T>& vec)
	{
		ThisVector[0] *= vec.ThisVector[0];
		ThisVector[1] *= vec.ThisVector[1];
		ThisVector[2] *= vec.ThisVector[2];
		ThisVector[3] *= vec.ThisVector[3];
	}

	// multiply value to all points
	inline void mul(T value)
	{
		ThisVector[0] *= value;
		ThisVector[1] *= value;
		ThisVector[2] *= value;
		ThisVector[3] *= value;
	}

	// x, y, z and alpha
	inline void div(const T _1, const T _2, const T _3, const T _4 = 1)
	{
		ThisVector[0] /= _1;
		ThisVector[1] /= _2;
		ThisVector[2] /= _3;
		ThisVector[3] /= _4;
	}

	// multiply another vector
	inline void div(LVector4<T> vec)
	{
		ThisVector[0] /= vec.ThisVector[0];
		ThisVector[1] /= vec.ThisVector[1];
		ThisVector[2] /= vec.ThisVector[2];
		ThisVector[3] /= vec.ThisVector[3];
	}

	// multiply value to all points
	inline void div(T value)
	{
		ThisVector[0] /= value;
		ThisVector[1] /= value;
		ThisVector[2] /= value;
		ThisVector[3] /= value;
	}

	inline void _min(LVector4<T> ref1)
	{
		ThisVector[0] = min(ThisVector[0], ref1.ThisVector[0]);
		ThisVector[1] = min(ThisVector[1], ref1.ThisVector[1]);
		ThisVector[2] = min(ThisVector[2], ref1.ThisVector[2]);
		ThisVector[3] = min(ThisVector[3], ref1.ThisVector[3]);
	}

	inline void _min(LVector4<T> ref1, LVector4<T> ref2)
	{
		ThisVector[0] = min(ref1.ThisVector[0], ref2.ThisVector[0]);
		ThisVector[1] = min(ref1.ThisVector[1], ref2.ThisVector[1]);
		ThisVector[2] = min(ref1.ThisVector[2], ref2.ThisVector[2]);
		ThisVector[3] = min(ref1.ThisVector[3], ref2.ThisVector[3]);
	}

	inline void _max(LVector4<T> ref1)
	{
		ThisVector[0] = max(ThisVector[0], ref1.ThisVector[0]);
		ThisVector[1] = max(ThisVector[1], ref1.ThisVector[1]);
		ThisVector[2] = max(ThisVector[2], ref1.ThisVector[2]);
		ThisVector[3] = max(ThisVector[3], ref1.ThisVector[3]);
	}

	inline void _max(LVector4<T> ref1, LVector4<T> ref2)
	{
		ThisVector[0] = max(ref1.ThisVector[0], ref2.ThisVector[0]);
		ThisVector[1] = max(ref1.ThisVector[1], ref2.ThisVector[1]);
		ThisVector[2] = max(ref1.ThisVector[2], ref2.ThisVector[2]);
		ThisVector[3] = max(ref1.ThisVector[3], ref2.ThisVector[3]);
	}
};

class LFVector4 : public LVector4<f32>
{
	inline void abs()
	{
		ThisVector[0] = fabs(ThisVector[0]);
		ThisVector[1] = fabs(ThisVector[1]);
		ThisVector[2] = fabs(ThisVector[2]);
		ThisVector[3] = fabs(ThisVector[3]);
	}

	inline void abs(LFVector4 ref)
	{
		ThisVector[0] = fabs(ref.ThisVector[0]);
		ThisVector[1] = fabs(ref.ThisVector[1]);
		ThisVector[2] = fabs(ref.ThisVector[2]);
		ThisVector[3] = fabs(ref.ThisVector[3]);
	}

	inline void ceil()
	{
		ThisVector[0] = ::ceil(ThisVector[0]);
		ThisVector[1] = ::ceil(ThisVector[1]);
		ThisVector[2] = ::ceil(ThisVector[2]);
		ThisVector[3] = ::ceil(ThisVector[3]);
	}

	inline void ceil(LFVector4 ref)
	{
		ThisVector[0] = ::ceil(ref.ThisVector[0]);
		ThisVector[1] = ::ceil(ref.ThisVector[1]);
		ThisVector[2] = ::ceil(ref.ThisVector[2]);
		ThisVector[3] = ::ceil(ref.ThisVector[3]);
	}

	inline void floor()
	{
		ThisVector[0] = ::floor(ThisVector[0]);
		ThisVector[1] = ::floor(ThisVector[1]);
		ThisVector[2] = ::floor(ThisVector[2]);
		ThisVector[3] = ::floor(ThisVector[3]);
	}

	inline void floor(LFVector4 ref)
	{
		ThisVector[0] = ::floor(ref.ThisVector[0]);
		ThisVector[1] = ::floor(ref.ThisVector[1]);
		ThisVector[2] = ::floor(ref.ThisVector[2]);
		ThisVector[3] = ::floor(ref.ThisVector[3]);
	}

	inline bool similar(LFVector4 ref, f32 eps = 0.0010000f)
	{
		return (fabs(ThisVector[0] - ref.ThisVector[0]) < eps) && (fabs(ThisVector[1] - ref.ThisVector[1]) < eps)
			&& (fabs(ThisVector[2] - ref.ThisVector[2]) < eps) && (fabs(ThisVector[3] - ref.ThisVector[3]) < eps);
	}
};

class LDVector4 : public LVector4<f64>
{
	inline void abs()
	{
		ThisVector[0] = fabs(ThisVector[0]);
		ThisVector[1] = fabs(ThisVector[1]);
		ThisVector[2] = fabs(ThisVector[2]);
		ThisVector[3] = fabs(ThisVector[3]);
	}

	inline void abs(LDVector4 ref)
	{
		ThisVector[0] = fabs(ref.ThisVector[0]);
		ThisVector[1] = fabs(ref.ThisVector[1]);
		ThisVector[2] = fabs(ref.ThisVector[2]);
		ThisVector[3] = fabs(ref.ThisVector[3]);
	}

	inline void ceil()
	{
		ThisVector[0] = ::ceil(ThisVector[0]);
		ThisVector[1] = ::ceil(ThisVector[1]);
		ThisVector[2] = ::ceil(ThisVector[2]);
		ThisVector[3] = ::ceil(ThisVector[3]);
	}

	inline void ceil(LDVector4 ref)
	{
		ThisVector[0] = ::ceil(ref.ThisVector[0]);
		ThisVector[1] = ::ceil(ref.ThisVector[1]);
		ThisVector[2] = ::ceil(ref.ThisVector[2]);
		ThisVector[3] = ::ceil(ref.ThisVector[3]);
	}

	inline void floor()
	{
		ThisVector[0] = ::floor(ThisVector[0]);
		ThisVector[1] = ::floor(ThisVector[1]);
		ThisVector[2] = ::floor(ThisVector[2]);
		ThisVector[3] = ::floor(ThisVector[3]);
	}

	inline void floor(LDVector4 ref)
	{
		ThisVector[0] = ::floor(ref.ThisVector[0]);
		ThisVector[1] = ::floor(ref.ThisVector[1]);
		ThisVector[2] = ::floor(ref.ThisVector[2]);
		ThisVector[3] = ::floor(ref.ThisVector[3]);
	}

	inline bool similar(LDVector4 ref, f64 eps = 0.0010000)
	{
		return (fabs(ThisVector[0] - ref.ThisVector[0]) < eps) && (fabs(ThisVector[1] - ref.ThisVector[1]) < eps)
			&& (fabs(ThisVector[2] - ref.ThisVector[2]) < eps) && (fabs(ThisVector[3] - ref.ThisVector[3]) < eps);
	}
};

using LU64Vector4 = LVector4<u64>;
using LU32Vector4 = LVector4<u32>;
using LU16Vector4 = LVector4<u16>;
using LU8Vector4 = LVector4<u8>;

using LI64Vector4 = LVector4<i64>;
using LI32Vector4 = LVector4<i32>;
using LI16Vector4 = LVector4<i16>;
using LI8Vector4 = LVector4<i8>;

