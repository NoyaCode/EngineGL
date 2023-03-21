#pragma once
#include "Input.h"
#include "GameObject.h"
#include "MyMaths.h"
#include "Script.h"

using namespace Core::Maths;

namespace Game
{
	class HeadRotation : public Script
	{
	public:
		void Init() override {};
		void UpdateScript() override;
		bool UpdateComponent(std::string* id) override;

	private:
		void UpdateRotation();

		float rotationSpeed = 10;

		double lastCursorY = NULL;
	};
}