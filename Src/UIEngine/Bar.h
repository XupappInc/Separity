#pragma once
#ifndef __BAR_H__
#define __BAR_H__

#include "SeparityExports\SeparityApi.h"
#include "UIComponent.h"

#include <string>

namespace Ogre {
	class Overlay;
}

namespace Separity {
	class Behaviour;
	class _SEPARITY_API_ Bar : public Separity::UIComponent {
		public:
		__CMPTYPE_DECL__(Separity::_UI)
		__CMPID_DECL__(Separity::_BAR)

		/// <summary>
		/// Constructora de la clase baR
		/// </summary>
		Bar(std::string overlayName, float xPos, float yPos, float width,
		      float height, std::string texture, int zorder = 0);
		void initComponent() override;
		///< summary>
		/// Destructora de la clase BAR
		/// </summary>
		~Bar();
		void setPercentage(float percentage);
		private:
		Behaviour* behaviour_=nullptr;
		std::string texture_;
		float percentage_;
		int width_;
		int height_;
	};
}  // namespace Separity

#endif