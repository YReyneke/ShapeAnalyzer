#include "Shapes.h"
#include <math.h>

void Shapes::Shape::DrawShape(System::Drawing::Graphics^ gfx, System::Drawing::Pen^ pen)
{
	// Draw the point on the screen
	gfx->DrawEllipse(pen, origin->x, origin->y, static_cast<int>(pen->Width), static_cast<int>(pen->Width));
}

Color Shapes::Shape::GetHilightColor()
{
	return GetHilightColor(drawState);
}

Color Shapes::Shape::GetHilightColor(DrawHilightState DHS)
{
	// Hard coded colours for now, easy enough to change that in the future
	switch (DHS) {
	case Unselected:
		return Color::Blue;
		break;
	case Selected1:
		return Color::ForestGreen;
		break;
	case Selected2:
		return Color::Red;
		break;
	case Selected3:
		return Color::Yellow;
		break;
	}
	return Color::Purple; // Error colour - should never happen
}

Shapes::Rectangle::Rectangle(Point^ origin, Point^ farCorner) {
	vLine1 = gcnew Line{ origin, gcnew Point{origin->x, farCorner->y} };
	hLine1 = gcnew Line{ origin, gcnew Point{farCorner->x, origin->y} };
	vLine2 = gcnew Line{ gcnew Point{origin->x, farCorner->y}, farCorner };
	hLine2 = gcnew Line{ gcnew Point{farCorner->x, origin->y}, farCorner };
	this->origin = origin;
}

void Shapes::Rectangle::DrawShape(System::Drawing::Graphics^ gfx, System::Drawing::Pen^ pen)
{
	vLine1->DrawShape(gfx, pen);
	vLine2->DrawShape(gfx, pen);
	hLine1->DrawShape(gfx, pen);
	hLine2->DrawShape(gfx, pen);
}

void Shapes::Line::DrawShape(System::Drawing::Graphics^ gfx, System::Drawing::Pen^ pen)
{
	gfx->DrawLine(pen, pointA->x, pointA->y, pointB->x, pointB->y);
}

Shapes::Star::Star(Point^ origin, Point^ sizeRef, unsigned int pointCount) : pointCount{ pointCount } {
	this->origin = origin;
	radius = Distance(origin, sizeRef);

	// Angle between each point (about origin)
	float lineAngle{ static_cast<float>((pointCount == 0) ? PI * 2 : PI * 2 / static_cast<float>(pointCount)) };
	// Point number/id of the point just before 180 deg rotation from top of star
	int halfPoint = pointCount / 2;
	// Angle at which the next line's points are calculated - used to draw the star shape as you would by hand
	lineAngle *= halfPoint;
	// As we are working with a y+ is down system, we need to rotate everything by 180 degrees (PI) for the star to point upward
	float currentPointAngle{ PI };

	// Loop for number of points (and lines) in the star
	for (int i{ 0 }; i < pointCount; i++) {
		int x1, x2, y1, y2;
		
		// Calculate x and y position of the first point of this line
		y1 = origin->y + (radius * cos(currentPointAngle));
		x1 = origin->x + (radius * sin(currentPointAngle));

		// Rotate to the next point in the star
		currentPointAngle += lineAngle;

		// Calculate x and y position of the second point of this line
		y2 = origin->y + (radius * cos(currentPointAngle));
		x2 = origin->x + (radius * sin(currentPointAngle));

		// Add the line to this star's lines ready to be drawn
		lines.push_back(gcnew Line{ gcnew Point{x1,y1}, gcnew Point{x2,y2} });
	}
}

Shapes::Star::~Star()
{
	for (int i{ 0 }; i < lines.size(); i++)
		delete lines[i];
}

Shapes::Star::!Star()
{
	for (int i{ 0 }; i < lines.size(); i++)
		delete lines[i];
}

void Shapes::Star::DrawShape(System::Drawing::Graphics^ gfx, System::Drawing::Pen^ pen)
{
	if (lines.size() <= 0)
		return;

	// Call draw function of each line
	for (int i{ 0 }; i < lines.size(); i++) {
		lines[i]->DrawShape(gfx, pen);
	}
}

Shapes::Arrow::Arrow(Line^ owningLine, float arrowHeight, float headAngle) :
	owningLine{ owningLine }, height{ arrowHeight }, headAngle{ headAngle }	{
	// Create a new point object for the origin of this arrow
	origin = gcnew Point{
		this->owningLine->pointA->x + ((this->owningLine->pointB->x - this->owningLine->pointA->x) / 2.f),
		this->owningLine->pointA->y + ((this->owningLine->pointB->y - this->owningLine->pointA->y) / 2.f)
	};
	UpdateArrowLines();
}

void Shapes::Arrow::DrawShape(System::Drawing::Graphics^ gfx, System::Drawing::Pen^ pen)
{
	// Call draw function of each line
	L1->DrawShape(gfx, pen);
	L2->DrawShape(gfx, pen);
	owningLine->DrawShape(gfx, pen);
}

void Shapes::Arrow::UpdateSize(float newHeight, float newHeadAngle)
{
	height = newHeight;
	headAngle = newHeadAngle;
	UpdateArrowLines();
}

void Shapes::Arrow::UpdateArrowLines()
{
	// Create the lines of the arrow head if they do not already exist
	if (!L1)
		L1 = gcnew Line{ gcnew Point{0,0}, gcnew Point{0,0} };
	if (!L2)
		L2 = gcnew Line{ gcnew Point{0,0}, gcnew Point{0,0} };

	float lineOrientation{}; // Radians
	
	// Calculate line orientation
	int Dx{ owningLine->pointB->x - owningLine->pointA->x };
	int Dy{ owningLine->pointB->y - owningLine->pointA->y };
	if (Dx == 0) {// Avoid div/0 exception
		lineOrientation = (Dy >= 0) ? 0 : PI;
	}
	else if (Dx > 0) { // Moving to the right - add 360deg if moving up
		// so that arrow orientation calculation not affected by -ve values
		lineOrientation = (Dy >= 0) ? atan(Dy / static_cast<float>(Dx)) : atan(Dy / static_cast<float>(Dx)) + 2 * PI;
	}
	else { // Moving to the left - always add 180 deg
		lineOrientation = atan(Dy / static_cast<float>(Dx)) + PI;
	}
	// Fix overall orientation of arrow (it was off by 90 degrees)
	lineOrientation += PI / 2.f;

	// Setup arrow head offset - the arrow body is centered around the line's center, not the arrow head
	Point^ arrowHeadPosRel{ gcnew Point{
		0.f,
		-height / 2.f
	} };

	// Calculate rotated arrow head location
	int x{ arrowHeadPosRel->x }, y{ arrowHeadPosRel->y };
	arrowHeadPosRel->x = (x * cos(lineOrientation)) - (y * sin(lineOrientation));
	arrowHeadPosRel->y = (y * cos(lineOrientation)) + (x * sin(lineOrientation));

	// Set line start points to the calculated coordinates
	L1->pointA->x = arrowHeadPosRel->x;
	L1->pointA->y = arrowHeadPosRel->y;
	L2->pointA->x = arrowHeadPosRel->x;
	L2->pointA->y = arrowHeadPosRel->y;

	// Calculate first feather end point
	x = (height * tan(headAngle * (PI / 180.f) / 2.f));
	y = height / 2.f;
	// Rotate and set coordinates
	L1->pointB->x = (x * cos(lineOrientation)) - (y * sin(lineOrientation));
	L1->pointB->y = (y * cos(lineOrientation)) + (x * sin(lineOrientation));

	// Calculate second feather end point
	x = height * tan(-headAngle * (PI / 180.f) / 2.f); // NOTE: -ve head angle
	//y = height / 2.f; - worlds smallest optimisation
	// Rotate and set coordinates
	L2->pointB->x = (x * cos(lineOrientation)) - (y * sin(lineOrientation));
	L2->pointB->y = (y * cos(lineOrientation)) + (x * sin(lineOrientation));

	// Translate arrow to 'global' space
	L1 += origin;
	L2 += origin;
}

float Shapes::Distance(Shape^ shape1, Shape^ shape2)
{
	// Pythagoras is back
	return sqrt(pow(shape1->origin->x - shape2->origin->x, 2) + pow(shape1->origin->y - shape2->origin->y, 2));
}

float Shapes::Distance(Point^ point1, Point^ point2)
{
	// Pythagoras is back
	return sqrt(pow(point1->x - point2->x, 2) + pow(point1->y - point2->y, 2));
}

float Shapes::Distance(Point^ point, Shape^ shape)
{
	// Pythagoras is back
	return sqrt(pow(point->x - shape->origin->x, 2) + pow(point->y - shape->origin->y, 2));
}


bool Shapes::CheckRectOverlap(Rectangle^ rect1, Rectangle^ rect2)
{
	// Simple basic collision check, does not check if lines are overlapping
	// so if one rectangle is within the other but not touching the sides it will still return 'true'
	if (rect2->origin->x > rect1->origin->x + rect1->width()) // rect2 too far to the right
		return false;
	if (rect2->origin->x + rect2->width() < rect1->origin->x) // rect2 too far to the left
		return false;
	if (rect2->origin->y > rect1->origin->y + rect1->height()) // rect2 too far below
		return false;
	if (rect2->origin->y + rect2->height() < rect1->origin->y) // rect2 too far above
		return false;

	return true;
}

bool Shapes::CheckLineIntercept(Line^ line1, Line^ line2)
{
	// Find orientation of line2 points relative to line1 points and vice-versa
	Rotation L1Rot1{ CheckPointOrientation(line1->pointA, line1->pointB, line2->pointA) };
	Rotation L1Rot2{ CheckPointOrientation(line1->pointA, line1->pointB, line2->pointB) };
	Rotation L2Rot1{ CheckPointOrientation(line2->pointA, line2->pointB, line1->pointA) };
	Rotation L2Rot2{ CheckPointOrientation(line2->pointA, line2->pointB, line1->pointB) };

	// The point rotations are such that the lines definitely intersect
	if (L1Rot1 != L1Rot2 && L2Rot1 != L2Rot2)
		return true;

	// In the event that a point is colinear with a line, check if it lies on that line
	if (L1Rot1 == Rotation::CoLinear && CheckColinearOverlap(line1->pointA, line1->pointB, line2->pointA))
		return true;

	if (L1Rot2 == Rotation::CoLinear && CheckColinearOverlap(line1->pointA, line1->pointB, line2->pointB))
		return true;

	if (L2Rot1 == Rotation::CoLinear && CheckColinearOverlap(line2->pointA, line2->pointB, line1->pointA))
		return true;

	if (L2Rot2 == Rotation::CoLinear && CheckColinearOverlap(line2->pointA, line2->pointB, line1->pointB))
		return true;

	return false;
}

Shapes::Rotation Shapes::CheckPointOrientation(Point^ p1, Point^ p2, Point^ p3)
{
	// Calculate factor of rotation of the three points
	int rotationFactor{ (p2->y - p1->y) * (p3->x - p2->x) - (p2->x - p1->x) * (p3->y - p2->y) };

	if (rotationFactor == 0) // No rotation calculated
		return Rotation::CoLinear;
	return (rotationFactor < 0) ? Rotation::Clockwise : Rotation::AntiClockwise; // If rotationfactor < 0 then rotation is clockwise
}

bool Shapes::CheckColinearOverlap(Point^ p1, Point^ p2, Point^ p3)
{
	// Returns 'true' if p3 sits between p1 and p2
	if (p3->x <= Max(p1->x, p2->x) && p3->x >= Min(p1->x, p2->x) &&
		p3->y <= Max(p1->y, p2->y) && p3->y >= Min(p1->y, p2->y))
		return true;

	return false;
}