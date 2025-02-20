#pragma once
class Vector2D
{
public:
	float x;
	float y;

public:
	//コンストラクタ
	//初期化
	Vector2D() : x(0.0f),y(0.0f){}
	//Vector2Dクラスに値を代入するときに使用
	Vector2D(float s) : x(s),y(s){}
	Vector2D(float sx,float sy):x(sx),y(sy){}
	~Vector2D() = default;

public:
	
	//加算　const Vector2D&
	//Vector同士で計算させる為演算子のオーバーロード
	void operator += (const Vector2D& v)
	{
		this->x += v.x;
		this->y += v.y;
	}

	void operator -= (const Vector2D& v)
	{
		this->x -= v.x;
		this->y -= v.y;
	}

	void operator *= (float scaler)
	{
		this->x *= scaler;
		this->y *= scaler;
	}

	Vector2D operator * (float scaler) const
	{
		return Vector2D(x * scaler, y * scaler);
	}

	Vector2D operator -() const
	{
		return Vector2D(-x, -y);
	}

public:
	void ToInt(int* x, int* y)
	{
		*x = static_cast<int>(this->x);
		*y = static_cast<int>(this->y);
	}
};

//inline関数でインライン展開
inline Vector2D operator + (const Vector2D& va, const Vector2D& vb)
{
	return Vector2D(va.x + vb.x, va.y + vb.y);
}
inline Vector2D operator - (const Vector2D& va, const Vector2D& vb)
{
	return Vector2D(va.x - vb.x, va.y - vb.y);
}
inline float Dot(const Vector2D& va, const Vector2D& vb)
{
	return (va.x * vb.x + va.y * vb.y);
}
inline float Cross(const Vector2D& va, const Vector2D& vb)
{
	return (va.x * vb.y - vb.x * va.y);
}