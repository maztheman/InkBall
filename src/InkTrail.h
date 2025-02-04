
#ifndef INKBALL_INKTRAIL_H
#define INKBALL_INKTRAIL_H

#include "Vector2.h"
#include "Renderable.h"
#include "Updatable.h"
#include "Drawing.h"
#include "Collidable.h"

#include <vector>

namespace Where1::InkBall {
	class InkTrail : public Renderable, public Collidable<double> {
	public:
		InkTrail() = default;

		void draw(SDL_Renderer *renderer) override;

		void append(vec2d point);

		std::vector<Geometry::Line<double>> get_bounding_lines() override;

		static const int PADDING = 3;
	private:
		std::vector<vec2d> points;
		//static const int THICKNESS = 3;
	};
}

#endif //INKBALL_INKTRAIL_H
