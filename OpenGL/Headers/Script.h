#pragma once
#include "MonoBehaviour.h"
#include "GameObject.h"

namespace Game
{
	class Script : public MonoBehaviour
	{
	public:
		virtual void Init() = 0;
		void Update() override;
		void Delete() override {};

	protected:
		virtual void UpdateScript() {};
	};
}
