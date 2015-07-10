/*
 * MathUtil.h
 *
 *  Created on: 2013/12/02
 *      Author: kryozahiro
 */

#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#include <cmath>
#include <complex>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>

namespace cpputil {

//----------------------------------------
// 定数
//----------------------------------------

using namespace boost::math::constants;

//----------------------------------------
// スケーリング
//----------------------------------------

//線形変換
template <class T>
T scale(T value, T ratio, T bias) {
	return ratio * value + bias;
}

//範囲の線形変換
template <class T>
T scale(T value, std::pair<T, T> from_range, std::pair<T, T> to_range) {
	T ratio = (to_range.second - to_range.first) / (from_range.second - from_range.first);
	T bias = to_range.first - from_range.first * ratio;
	return scale(value, ratio, bias);
}

//全体の平均を保って最大値を平均のscaling倍にするような線形変換
//f(mean) = a * mean + b = average
//f(max) = a * max + b = scale * average
template <class T>
T scale(T value, T mean, T max, T scaling) {
	T ratio = mean * (scaling - 1.0) / (max - mean);
	T bias = mean * (1.0 - ratio);
	return scale(value, ratio, bias);
}

//----------------------------------------
// 角度
//----------------------------------------

//度数からラジアンへ変換
template <class T>
T toRadian(T deg) {
	return deg * pi<T>() / 180.0;
}

//ラジアンから度数へ変換
template <class T>
T toDegree(T rad) {
	return rad * 180.0 / pi<T>();
}

//-PI < rad <= PIに正規化
template <class T>
T normalize(T rad) {
	rad = std::remainder(rad, 2.0 * pi<T>());
	if (rad <= -pi<T>()) {
		rad += 2.0 * pi<T>();
	}
	return rad;
}

//正規化つきの回転
template <class T>
T rotate(T baseRad, T relativeRad) {
	return normalize(baseRad + relativeRad);
}

//----------------------------------------
// 複素数
// テンプレート引数は実数のみ使用可能
//----------------------------------------

//ペアから複素数へ変換
template <class T, class U, class V>
std::complex<T> toComplex(std::pair<U, V> p) {
	return std::complex<T>(p.first, p.second);
}

//複素数からペアへ変換
template <class T, class U, class V>
std::pair<T, U> toPair(std::complex<V> z) {
	return std::make_pair<T, U>(z.real(), z.imag());
}

//単位長への正規化
template <class T>
std::complex<T> normalize(std::complex<T> z) {
	return z / std::abs(z);
}

//----------------------------------------
// ノルムと距離
//----------------------------------------

//実数版Lp-ノルム
template <class T>
T lpNorm(std::complex<T> z, T p) {
	return std::pow(std::pow(std::fabs(z.real()), p) + std::pow(std::fabs(z.imag()), p), 1.0 / p);
}

//実数版Lp-ノルムによる距離
template <class T>
T lpDistance(std::complex<T> z0, std::complex<T> z1, T p) {
	return lpNorm<T>(z1 - z0, p);
}

//整数版Lp-ノルムの実装の詳細
namespace detail {

template <class T, int p>
struct lpNormHelper {
	static T lpNorm(std::complex<T> z);
};
template <class T, int p>
T lpNormHelper<T, p>::lpNorm(std::complex<T> z) {
	return cpputil::lpNorm(z, static_cast<T>(p));
}

template <class T>
struct lpNormHelper<T, 1> {
	static T lpNorm(std::complex<T> z);
};
template <class T>
T lpNormHelper<T, 1>::lpNorm(std::complex<T> z) {
	return std::fabs(z.real()) + std::fabs(z.imag());
}

template <class T>
struct lpNormHelper<T, 2> {
	static T lpNorm(std::complex<T> z);
};
template <class T>
T lpNormHelper<T, 2>::lpNorm(std::complex<T> z) {
	return std::abs(z);
}

template <class T>
struct lpNormHelper<T, INT_MAX> {
	static T lpNorm(std::complex<T> z);
};
template <class T>
T lpNormHelper<T, INT_MAX>::lpNorm(std::complex<T> z) {
	return std::max(std::fabs(z.real()), std::fabs(z.imag()));
}

}

//整数版Lp-ノルム
template <class T, int p>
T lpNorm(std::complex<T> z) {
	return detail::lpNormHelper<T, p>::lpNorm(z);
}

//整数版Lp-ノルムによる距離
template <class T, int p>
T lpDistance(std::complex<T> z0, std::complex<T> z1) {
	return lpNorm<T, p>(z1 - z0);
}

//マンハッタンノルム
template <class T>
T manhattanNorm(std::complex<T> z) {
	return lpNorm<T, 1>(z);
}

//マンハッタン距離
template <class T>
T manhattanDistance(std::complex<T> z0, std::complex<T> z1) {
	return manhattanNorm(z1 - z0);
}

//ユークリッドノルム
template <class T>
T euclideanNorm(std::complex<T> z) {
	return lpNorm<T, 2>(z);
}

//ユークリッド距離
template <class T>
T euclideanDistance(std::complex<T> z0, std::complex<T> z1) {
	return euclideanNorm(z1 - z0);
}

//チェス盤ノルム
template <class T>
T chessboardNorm(std::complex<T> z) {
	return lpNorm<T, INT_MAX>(z);
}

//チェス盤距離
template <class T>
T chessboardDistance(std::complex<T> z0, std::complex<T> z1) {
	return chessboardNorm(z1 - z0);
}

//----------------------------------------
// アフィン変換
//----------------------------------------

//平行移動
template <class T>
std::complex<T> translate(std::complex<T> z, std::complex<T> translation) {
	return z + translation;
}

//回転
template <class T>
std::complex<T> rotate(std::complex<T> z, double rad) {
	return z * std::polar(1.0, rad);
}

//拡縮
template <class T>
std::complex<T> scale(std::complex<T> z, std::complex<T> scaling) {
	return std::complex<T>(z.real() * scaling.real(), z.imag() * scaling.imag());
}

//変換
template <class T>
std::complex<T> transform(std::complex<T> z, std::complex<T> translation, double rotation, std::complex<T> scaling = std::complex<T>(1, 1)) {
	return translate(rotate(scale(z, scaling), rotation), translation);
}

//変換オブジェクト
template <class T>
class Transformation : private boost::equality_comparable<Transformation<T>, Transformation<T>> {
public:
	Transformation() = default;
	Transformation(std::complex<T> translation, T rotation, std::complex<T> scaling);

	//アクセサ
	std::complex<T> translation() const;
	void translation(std::complex<T> t);
	T rotation() const;
	void rotation(T rad);
	std::complex<T> scaling() const;
	void scaling(std::complex<T> s);

	//変換の適用
	std::complex<T> operator*(std::complex<T> z);

	//逆変換
	Transformation<T> inverse();

	//変換オブジェクトの変換
	void translate(std::complex<T> t, bool local = true);
	void rotate(double rad, bool local = true);
	void scale(std::complex<T> s, bool local = true);
	void transform(const Transformation<T>& t, bool local = true);
	Transformation<T>& operator*=(const Transformation<T>& t);

	//変換の比較
	template <class X>
	friend bool operator==(const Transformation<X>& lhs, const Transformation<X>& rhs);

private:
	//平行移動
	std::complex<T> translation_ = {0, 0};

	//回転
	T rotation_ = 0;

	//拡縮
	std::complex<T> scaling_ = {1, 1};
};

template <class T>
Transformation<T>::Transformation(std::complex<T> translation, T rotation, std::complex<T> scaling) :
	translation_(translation), rotation_(rotation), scaling_(scaling) {
}

template <class T>
std::complex<T> Transformation<T>::translation() const {
	return translation_;
}

template <class T>
void Transformation<T>::translation(std::complex<T> t) {
	translation_ = t;
}

template <class T>
T Transformation<T>::rotation() const {
	return rotation_;
}

template <class T>
void Transformation<T>::rotation(T rad) {
	rotation_ = rad;
}

template <class T>
std::complex<T> Transformation<T>::scaling() const {
	return scaling_;
}

template <class T>
void Transformation<T>::scaling(std::complex<T> s) {
	scaling_ = s;
}

template <class T>
std::complex<T> Transformation<T>::operator*(std::complex<T> z) {
	return cpputil::transform(z, translation_, rotation_, scaling_);
}

template <class T>
Transformation<T> Transformation<T>::inverse() {
	return Transformation<T>(
		-cpputil::rotate(cpputil::scale(translation_, 1.0 / scaling_), -rotation_),
		-rotation_,
		1.0 / scaling_
	);
}

template <class T>
void Transformation<T>::translate(std::complex<T> t, bool local) {
	if (local) {
		translation_ = cpputil::transform(t, translation_, rotation_, scaling_);
	} else {
		translation_ = cpputil::translate(translation_, t);
	}
}

template <class T>
void Transformation<T>::rotate(double rad, bool local) {
	rotation_ = cpputil::rotate(rotation_, rad);
	if (!local) {
		translation_ = cpputil::rotate(translation_, rad);
	}
}

template <class T>
void Transformation<T>::scale(std::complex<T> s, bool local) {
	scaling_ = cpputil::scale(scaling_, s);
	if (!local) {
		translation_ = cpputil::scale(translation_, s);
	}
}

template <class T>
void Transformation<T>::transform(const Transformation<T>& t, bool local) {
	scale(t.scaling_, local);
	rotate(t.rotation_, local);
	translate(t.translation_, local);
}

template <class T>
Transformation<T>& Transformation<T>::operator*=(const Transformation<T>& t) {
	transform(t);
	return *this;
}

//変換の合成
template <class T>
Transformation<T> operator*(const Transformation<T>& lhs, const Transformation<T>& rhs) {
	Transformation<T> ret = lhs;
	ret *= rhs;
	return ret;
}

//変換の比較
template <class T>
bool operator==(const Transformation<T>& lhs, const Transformation<T>& rhs) {
	return lhs.translation_ == rhs.translation_ and lhs.rotation_ == rhs.rotation_ and lhs.scaling_ == rhs.scaling_;
}

//運動
//mathというよりphysics
/*template <class T>
struct RigidBody : public Transformation<T> {
	//並進運動
	T mass = 1;
	std::complex<T> velocity = {0, 0};
	std::complex<T> resultantForce = {0, 0};

	//回転運動
	T momentOfInertia = 1;
	T angularVelocity = 0;
	T resultantMoment = 0;

	void update(T dt) {
		Transformation<T>::translate(velocity * dt);
		translate(velocity, resultantForce / mass * dt);
		resultantForce = 0;

		Transformation<T>::rotate(angularVelocity * dt);
		rotate(angularVelocity, resultantMoment / momentOfInertia * dt);
		resultantMoment = 0;
	}
};*/

}

#endif /* MATHUTIL_H_ */
