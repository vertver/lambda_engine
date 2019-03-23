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
class LVector2
{
public:
	inline LVector2<T> operator += (LVector2<T> v) { return add(v); }
	inline LVector2<T> operator += (const T p) { return add(p); }
	inline LVector2<T> operator -= (LVector2<T> v) { return sub(v); }
	inline LVector2<T> operator -= (const T p) { return sub(p); }
	inline LVector2<T> operator *= (LVector2<T> v) { return mul(v); }
	inline LVector2<T> operator *= (const T p) { return mul(p); }
	inline LVector2<T> operator /= (LVector2<T> v) { return div(v); }
	inline LVector2<T> operator /= (const T p) { return div(p); }

	// 0 - x, 1 - y
	T ThisVector[2];

	// x, y 
	inline void set(const T _1, const T _2)
	{
		ThisVector[0] = _1;
		ThisVector[1] = _2;
	}

	// set another vector
	inline void set(LVector2<T>& vec)
	{
		ThisVector[0] = vec.ThisVector[0];
		ThisVector[1] = vec.ThisVector[1];
	}

	// set value to all points
	inline void set(T value)
	{
		ThisVector[0] = value;
		ThisVector[1] = value;
	}

	// x, y
	inline void sub(const T _1, const T _2)
	{
		ThisVector[0] -= _1;
		ThisVector[1] -= _2;
	}

	// sub another vector
	inline void sub(LVector2<T>& vec)
	{
		ThisVector[0] -= vec.ThisVector[0];
		ThisVector[1] -= vec.ThisVector[1];
	}

	// sub value to all points
	inline void sub(T value)
	{
		ThisVector[0] -= value;
		ThisVector[1] -= value;
	}

	// x, y
	inline void add(const T _1, const T _2)
	{
		ThisVector[0] += _1;
		ThisVector[1] += _2;
	}

	// add another vector
	inline void add(LVector2<T>& vec)
	{
		ThisVector[0] += vec.ThisVector[0];
		ThisVector[1] += vec.ThisVector[1];
	}

	// add value to all points
	inline void add(T value)
	{
		ThisVector[0] += value;
		ThisVector[1] += value;
	}

	// x, y
	inline void mul(const T _1, const T _2)
	{
		ThisVector[0] *= _1;
		ThisVector[1] *= _2;
	}

	// multiply another vector
	inline void mul(LVector2<T>& vec)
	{
		ThisVector[0] *= vec.ThisVector[0];
		ThisVector[1] *= vec.ThisVector[1];
	}

	// multiply value to all points
	inline void mul(T value)
	{
		ThisVector[0] *= value;
		ThisVector[1] *= value;
	}

	// x, y, z and alpha
	inline void div(const T _1, const T _2)
	{
		ThisVector[0] /= _1;
		ThisVector[1] /= _2;
	}

	// multiply another vector
	inline void div(LVector2<T> vec)
	{
		ThisVector[0] /= vec.ThisVector[0];
		ThisVector[1] /= vec.ThisVector[1];
	}

	// multiply value to all points
	inline void div(T value)
	{
		ThisVector[0] /= value;
		ThisVector[1] /= value;
	}

	inline void _min(LVector2<T> ref1)
	{
		ThisVector[0] = min(ThisVector[0], ref1.ThisVector[0]);
		ThisVector[1] = min(ThisVector[1], ref1.ThisVector[1]);
	}

	inline void _min(LVector2<T> ref1, LVector2<T> ref2)
	{
		ThisVector[0] = min(ref1.ThisVector[0], ref2.ThisVector[0]);
		ThisVector[1] = min(ref1.ThisVector[1], ref2.ThisVector[1]);
	}

	inline void _max(LVector2<T> ref1)
	{
		ThisVector[0] = max(ThisVector[0], ref1.ThisVector[0]);
		ThisVector[1] = max(ThisVector[1], ref1.ThisVector[1]);
	}

	inline void _max(LVector2<T> ref1, LVector2<T> ref2)
	{
		ThisVector[0] = max(ref1.ThisVector[0], ref2.ThisVector[0]);
		ThisVector[1] = max(ref1.ThisVector[1], ref2.ThisVector[1]);
	}
};

class LFVector2 : public LVector2<f32>
{
	inline void abs()
	{
		ThisVector[0] = fabs(ThisVector[0]);
		ThisVector[1] = fabs(ThisVector[1]);
	}

	inline void abs(LFVector2 ref)
	{
		ThisVector[0] = fabs(ref.ThisVector[0]);
		ThisVector[1] = fabs(ref.ThisVector[1]);
	}

	inline void ceil()
	{
		ThisVector[0] = ::ceil(ThisVector[0]);
		ThisVector[1] = ::ceil(ThisVector[1]);
	}

	inline void ceil(LFVector2 ref)
	{
		ThisVector[0] = ::ceil(ref.ThisVector[0]);
		ThisVector[1] = ::ceil(ref.ThisVector[1]);
	}

	inline void floor()
	{
		ThisVector[0] = ::floor(ThisVector[0]);
		ThisVector[1] = ::floor(ThisVector[1]);
	}

	inline void floor(LFVector2 ref)
	{
		ThisVector[0] = ::floor(ref.ThisVector[0]);
		ThisVector[1] = ::floor(ref.ThisVector[1]);
	}

	inline bool similar(LFVector2 ref, f32 eps = 0.0010000f)
	{
		return (fabs(ThisVector[0] - ref.ThisVector[0]) < eps) && (fabs(ThisVector[1] - ref.ThisVector[1]) < eps);
	}
};

class LDVector2 : public LVector2<f64>
{
	inline void abs()
	{
		ThisVector[0] = fabs(ThisVector[0]);
		ThisVector[1] = fabs(ThisVector[1]);
	}

	inline void abs(LDVector2 ref)
	{
		ThisVector[0] = fabs(ref.ThisVector[0]);
		ThisVector[1] = fabs(ref.ThisVector[1]);
	}

	inline void ceil()
	{
		ThisVector[0] = ::ceil(ThisVector[0]);
		ThisVector[1] = ::ceil(ThisVector[1]);
	}

	inline void ceil(LDVector2 ref)
	{
		ThisVector[0] = ::ceil(ref.ThisVector[0]);
		ThisVector[1] = ::ceil(ref.ThisVector[1]);
	}

	inline void floor()
	{
		ThisVector[0] = ::floor(ThisVector[0]);
		ThisVector[1] = ::floor(ThisVector[1]);
	}

	inline void floor(LDVector2 ref)
	{
		ThisVector[0] = ::floor(ref.ThisVector[0]);
		ThisVector[1] = ::floor(ref.ThisVector[1]);
	}  

	inline bool similar(LDVector2 ref, f64 eps = 0.0010000)
	{
		return (fabs(ThisVector[0] - ref.ThisVector[0]) < eps) && (fabs(ThisVector[1] - ref.ThisVector[1]) < eps);
	}
};

using LU64Vector2 = LVector2<u64>;
using LU32Vector2 = LVector2<u32>;
using LU16Vector2 = LVector2<u16>;
using LU8Vector2 = LVector2<u8>;

using LI64Vector2 = LVector2<i64>;
using LI32Vector2 = LVector2<i32>;
using LI16Vector2 = LVector2<i16>;
using LI8Vector2 = LVector2<i8>;
