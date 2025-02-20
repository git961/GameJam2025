#pragma once
// : unsigned char でunsigned char型をもとにenum classを宣言
//eNone等の列挙子がunsigned charで作られる
enum class eInputState : unsigned char
{
	eNone,
	ePress,
	eRelease,
	eHeld,
};