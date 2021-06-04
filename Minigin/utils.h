#pragma once
namespace GameEngine
{
	struct FVector2
	{
		float x;
		float y;
	};
	/*FVector2 operator+(const FVector2& p1, const FVector2& p2)
	{
		return FVector2{ p1.x + p2.x,p1.y + p2.y };
	}*/
	struct IPoint2
	{
		int x;
		int y;
	};
	/*IPoint2 operator+(const IPoint2& p1, const IPoint2& p2)
	{
		return IPoint2{ p1.x + p2.x,p1.y + p2.y };
	}*/
}