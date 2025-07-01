#pragma once
namespace GAME08 {
	class SCENEBASE{
	public:
		virtual ~SCENEBASE() {}
		virtual void create() = 0;
		virtual void update() = 0;
		virtual void destroy() = 0;
	};
}
