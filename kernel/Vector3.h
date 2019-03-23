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
class LVector3
{
public:
	inline LVector3<T> operator += (LVector3<T> v) { return add(v); }
	inline LVector3<T> operator += (const T p) { return add(p); }
	inline LVector3<T> operator -= (LVector3<T> v) { return sub(v); }
	inline LVector3<T> operator -= (const T p) { return sub(p); }
	inline LVector3<T> operator *= (LVector3<T> v) { return mul(v); }
	inline LVector3<T> operator *= (const T p) { return mul(p); }
	inline LVector3<T> operator /= (LVector3<T> v) { return div(v); }
	inline LVector3<T> operator /= (const T p) { return div(p); }

	// 0 - x, 1 - y, 2 - z
	T ThisVector[3];

	// x, y, z
	inline void set(const T _1, const T _2, const T _3)
	{
		ThisVector[0] = _1;
		ThisVector[1] = _2;
		ThisVector[2] = _3;
	}

	// set another vector
	inline void set(LVector3<T>& vec)
	{
		ThisVector[0] = vec.ThisVector[0];
		ThisVector[1] = vec.ThisVector[1];
		ThisVector[2] = vec.ThisVector[2];
	}

	// set value to all points
	inline void set(T value)
	{
		ThisVector[0] = value;
		ThisVector[1] = value;
		ThisVector[2] = value;
	}

	// x, y, z
	inline void sub(const T _1, const T _2, const T _3)
	{
		ThisVector[0] -= _1;
		ThisVector[1] -= _2;
		ThisVector[2] -= _3;
	}

	// sub another vector
	inline void sub(LVector3<T>& vec)
	{
		ThisVector[0] -= vec.ThisVector[0];
		ThisVector[1] -= vec.ThisVector[1];
		ThisVector[2] -= vec.ThisVector[2];
	}

	// sub value to all points
	inline void sub(T value)
	{
		ThisVector[0] -= value;
		ThisVector[1] -= value;
		ThisVector[2] -= value;
	}

	// x, y, z
	inline void add(const T _1, const T _2, const T _3)
	{
		ThisVector[0] += _1;
		ThisVector[1] += _2;
		ThisVector[2] += _3;
	}

	// add another vector
	inline void add(LVector3<T>& vec)
	{
		ThisVector[0] += vec.ThisVector[0];
		ThisVector[1] += vec.ThisVector[1];
		ThisVector[2] += vec.ThisVector[2];
	}

	// add value to all points
	inline void add(T value)
	{
		ThisVector[0] += value;
		ThisVector[1] += value;
		ThisVector[2] += value;
	}

	// x, y, z
	inline void mul(const T _1, const T _2, const T _3)
	{
		ThisVector[0] *= _1;
		ThisVector[1] *= _2;
		ThisVector[2] *= _3;
	}

	// multiply another vector
	inline void mul(LVector3<T>& vec)
	{
		ThisVector[0] *= vec.ThisVector[0];
		ThisVector[1] *= vec.ThisVector[1];
		ThisVector[2] *= vec.ThisVector[2];
	}

	// multiply value to all points
	inline void mul(T value)
	{
		ThisVector[0] *= value;
		ThisVector[1] *= value;
		ThisVector[2] *= value;
	}

	// x, y, z
	inline void div(const T _1, const T _2, const T _3)
	{
		ThisVector[0] /= _1;
		ThisVector[1] /= _2;
		ThisVector[2] /= _3;
	}

	// multiply another vector
	inline void div(LVector3<T> vec)
	{
		ThisVector[0] /= vec.ThisVector[0];
		ThisVector[1] /= vec.ThisVector[1];
		ThisVector[2] /= vec.ThisVector[2];
	}

	// multiply value to all points
	inline void div(T value)
	{
		ThisVector[0] /= value;
		ThisVector[1] /= value;
		ThisVector[2] /= value;
	}

	inline void _min(LVector3<T> ref1)
	{
		ThisVector[0] = min(ThisVector[0], ref1.ThisVector[0]);
		ThisVector[1] = min(ThisVector[1], ref1.ThisVector[1]);
		ThisVector[2] = min(ThisVector[2], ref1.ThisVector[2]);
	}

	inline void _min(LVector3<T> ref1, LVector3<T> ref2)
	{
		ThisVector[0] = min(ref1.ThisVector[0], ref2.ThisVector[0]);
		ThisVector[1] = min(ref1.ThisVector[1], ref2.ThisVector[1]);
		ThisVector[2] = min(ref1.ThisVector[2], ref2.ThisVector[2]);
	}

	inline void _max(LVector3<T> ref1)
	{
		ThisVector[0] = max(ThisVector[0], ref1.ThisVector[0]);
		ThisVector[1] = max(ThisVector[1], ref1.ThisVector[1]);
		ThisVector[2] = max(ThisVector[2], ref1.ThisVector[2]);
	}

	inline void _max(LVector3<T> ref1, LVector3<T> ref2)
	{
		ThisVector[0] = max(ref1.ThisVector[0], ref2.ThisVector[0]);
		ThisVector[1] = max(ref1.ThisVector[1], ref2.ThisVector[1]);
		ThisVector[2] = max(ref1.ThisVector[2], ref2.ThisVector[2]);
	}
};

class LFVector3 : public LVector3<f32>
{
	inline void abs()
	{
		ThisVector[0] = fabs(ThisVector[0]);
		ThisVector[1] = fabs(ThisVector[1]);
		ThisVector[2] = fabs(ThisVector[2]);
	}

	inline void abs(LFVector3 ref)
	{
		ThisVector[0] = fabs(ref.ThisVector[0]);
		ThisVector[1] = fabs(ref.ThisVector[1]);
		ThisVector[2] = fabs(ref.ThisVector[2]);
	}

	inline void ceil()
	{
		ThisVector[0] = ::ceil(ThisVector[0]);
		ThisVector[1] = ::ceil(ThisVector[1]);
		ThisVector[2] = ::ceil(ThisVector[2]);
	}

	inline void ceil(LFVector3 ref)
	{
		ThisVector[0] = ::ceil(ref.ThisVector[0]);
		ThisVector[1] = ::ceil(ref.ThisVector[1]);
		ThisVector[2] = ::ceil(ref.ThisVector[2]);
	}

	inline void floor()
	{
		ThisVector[0] = ::floor(ThisVector[0]);
		ThisVector[1] = ::floor(ThisVector[1]);
		ThisVector[2] = ::floor(ThisVector[2]);
	}

	inline void floor(LFVector3 ref)
	{
		ThisVector[0] = ::floor(ref.ThisVector[0]);
		ThisVector[1] = ::floor(ref.ThisVector[1]);
		ThisVector[2] = ::floor(ref.ThisVector[2]);
	}

	inline bool similar(LFVector3 ref, f32 eps = 0.0010000f)
	{
		return (fabs(ThisVector[0] - ref.ThisVector[0]) < eps) && (fabs(ThisVector[1] - ref.ThisVector[1]) < eps)
			&& (fabs(ThisVector[2] - ref.ThisVector[2]) < eps);
	}
};

class LDVector3 : public LVector3<f64>
{
	inline void abs()
	{
		ThisVector[0] = fabs(ThisVector[0]);
		ThisVector[1] = fabs(ThisVector[1]);
		ThisVector[2] = fabs(ThisVector[2]);
	}

	inline void abs(LDVector3 ref)
	{
		ThisVector[0] = fabs(ref.ThisVector[0]);
		ThisVector[1] = fabs(ref.ThisVector[1]);
		ThisVector[2] = fabs(ref.ThisVector[2]);
	}

	inline void ceil()
	{
		ThisVector[0] = ::ceil(ThisVector[0]);
		ThisVector[1] = ::ceil(ThisVector[1]);
		ThisVector[2] = ::ceil(ThisVector[2]);
	}

	inline void ceil(LDVector3 ref)
	{
		ThisVector[0] = ::ceil(ref.ThisVector[0]);
		ThisVector[1] = ::ceil(ref.ThisVector[1]);
		ThisVector[2] = ::ceil(ref.ThisVector[2]);
	}

	inline void floor()
	{
		ThisVector[0] = ::floor(ThisVector[0]);
		ThisVector[1] = ::floor(ThisVector[1]);
		ThisVector[2] = ::floor(ThisVector[2]);
	}

	inline void floor(LDVector3 ref)
	{
		ThisVector[0] = ::floor(ref.ThisVector[0]);
		ThisVector[1] = ::floor(ref.ThisVector[1]);
		ThisVector[2] = ::floor(ref.ThisVector[2]);
	}

	inline bool similar(LDVector3 ref, f64 eps = 0.0010000)
	{
		return (fabs(ThisVector[0] - ref.ThisVector[0]) < eps) && (fabs(ThisVector[1] - ref.ThisVector[1]) < eps)
			&& (fabs(ThisVector[2] - ref.ThisVector[2]) < eps);
	}
};

using LU64Vector3 = LVector3<u64>;
using LU32Vector3 = LVector3<u32>;
using LU16Vector3 = LVector3<u16>;
using LU8Vector3 = LVector3<u8>;

using LI64Vector3 = LVector3<i64>;
using LI32Vector3 = LVector3<i32>;
using LI16Vector3 = LVector3<i16>;
using LI8Vector3 = LVector3<i8>;
