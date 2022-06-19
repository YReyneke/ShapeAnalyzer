#include "ShapeController.h"

using namespace Shapes;

void ShapeController::StartDrawing(int mouse_x, int mouse_y)
{
	// Store current mouse coordinates as start point for shape
	DrawingStartPoint = gcnew Shapes::Point{ mouse_x, mouse_y };
	
	// Place point on mouse down instead of mouse up
	if(drawMode == DrawPoint)
		GeneratePoint();
}

void ShapeController::StopDrawing(int mouse_x, int mouse_y)
{
	// Store current mouse coordinates as end point for shape generation
	DrawingEndPoint = gcnew Shapes::Point{ mouse_x, mouse_y };

	// Select and generate shape by user choice
	switch (drawMode) {
	case DrawRectangle:
		GenerateRectangle();
	break;
	case DrawLine:
		GenerateLine();
		break;
	case DrawStar:
		GenerateStar();
		break;
	case DrawArrow:
		GenerateArrow();
		break;
	}
	// NOTE: DrawPoint handled on StartDrawing instead of here
}

void ShapeController::ClearShapes()
{
	// Cleanup shapes in memory
	for (int i{ 0 }; i < activeShapes.size(); i++) {
		delete activeShapes[i];
	}
	activeShapes.clear();
	while (!rectangles.empty())
		rectangles.pop();
	while (!lines.empty())
		lines.pop();
	while (!points.empty())
		points.pop();
}

void ShapeController::CheckRectanglesOverlap(System::Windows::Forms::Form^ form)
{
	CheckRectanglesOverlap(form, rectangles);
}

void ShapeController::CheckRectanglesOverlap(System::Windows::Forms::Form^ form, cliext::queue<Shapes::Rectangle^> rects)
{
	// Check if too few rectangles in the queue
	if (rects.size() < 2) {
		form->Refresh();
		MessageBox::Show(L"No more rectangles to check!");
		return;
	}

	// Store the next two rectangles in the queue
	Shapes::Rectangle^ rect1{ rects.front() };
	rects.pop();
	Shapes::Rectangle^ rect2{ rects.front() };
	rects.pop();

	// Perform overlap check and display result in message box
	if (CheckRectOverlap(rect1, rect2)) {
		// Set draw colour to affirm colour
		rect1->drawState = Selected1;
		rect2->drawState = Selected1;
		form->Refresh();

		switch (MessageBox::Show(
			L"The hilighted rectangles are overlapping.\nWould you like to continue?",
			L"Rectangle Overlap",
			MessageBoxButtons::YesNo
		)) {
		case DialogResult::Yes:
			// Clear draw colour back to default
			rect1->drawState = Unselected;
			rect2->drawState = Unselected;
			
			// Call this function with the reduced queue
			CheckRectanglesOverlap(form, rects);
			break;
		default:
			// Clear draw colour back to default
			rect1->drawState = Unselected;
			rect2->drawState = Unselected;
			form->Refresh();
			return;
			break;
		}
	}
	else {
		// Set draw colour to undetected
		rect1->drawState = Selected2;
		rect2->drawState = Selected2;
		
		// Paint updated colours to screen
		form->Refresh();

		switch (MessageBox::Show(
			L"The hilighted rectangles are not overlapping.\nWould you like to continue?",
			L"Rectangle No Overlap",
			MessageBoxButtons::YesNo
		)) {
		case DialogResult::Yes:
			// Clear draw colour back to default
			rect1->drawState = Unselected;
			rect2->drawState = Unselected;
			
			// Call this function with the reduced queue
			CheckRectanglesOverlap(form, rects);
			break;
		default:
			// Clear draw colour back to default
			rect1->drawState = Unselected;
			rect2->drawState = Unselected;

			// Refresh screen before exiting
			form->Refresh();
			return;
			break;
		}
	}
}

void ShapeController::CheckLinesIntersect(System::Windows::Forms::Form^ form)
{
	CheckLinesIntersect(form, lines);
}

void ShapeController::CheckLinesIntersect(System::Windows::Forms::Form^ form, cliext::queue<Line^> lns)
{
	// Check if too few lines in the queue
	if (lns.size() < 2) {
		form->Refresh();
		MessageBox::Show(L"No more lines to check!");
		return;
	}

	// Store the next two lines in the queue
	Line^ ln1{ lns.front() };
	lns.pop();
	Line^ ln2{ lns.front() };
	lns.pop();

	// Perform intersect check and notify user of result
	if (CheckLineIntercept(ln1, ln2)) {
		ln1->drawState = Selected1;
		ln2->drawState = Selected1;
		form->Refresh(); // Display changed draw states on screen

		switch (MessageBox::Show(
			L"The hilighted lines are intersecting.\nWould you like to continue?",
			L"Lines Intersect",
			MessageBoxButtons::YesNo
		)) {
		case DialogResult::Yes:
			ln1->drawState = Unselected;
			ln2->drawState = Unselected;
			CheckLinesIntersect(form, lns);
			break;
		default:
			ln1->drawState = Unselected;
			ln2->drawState = Unselected;
			form->Refresh(); // Display changed draw states on screen
			return;
			break;
		}
	}
	else {
		ln1->drawState = Selected2;
		ln2->drawState = Selected2;
		form->Refresh(); // Display changed draw states on screen

		switch (MessageBox::Show(
			L"The hilighted lines are not intersecting.\nWould you like to continue?",
			L"No Line Intersect",
			MessageBoxButtons::YesNo
		)) {
		case DialogResult::Yes:
			ln1->drawState = Unselected;
			ln2->drawState = Unselected;
			CheckLinesIntersect(form, lns);
			break;
		default:
			ln1->drawState = Unselected;
			ln2->drawState = Unselected;
			form->Refresh(); // Display changed draw states on screen
			return;
			break;
		}
	}
}

void ShapeController::CheckPointsRotation(System::Windows::Forms::Form^ form)
{
	CheckPointsRotation(form, points);
}

void ShapeController::CheckPointsRotation(System::Windows::Forms::Form^ form, cliext::queue<Shape^> pts)
{
	// Check if too few points are in the queue
	if (pts.size() < 3) {
		form->Refresh();
		MessageBox::Show(L"No more points to check!");
		return;
	}

	// Store the next three points in the queue
	Shape^ pt1{ pts.front() };
	pts.pop();
	Shape^ pt2{ pts.front() };
	pts.pop();
	Shape^ pt3{ pts.front() };
	pts.pop();

	// Perform point rotation check and notify user of result
	if (CheckPointOrientation(pt1->origin, pt2->origin, pt3->origin) == Clockwise) {
		pt1->drawState = Selected1;
		pt2->drawState = Selected2;
		pt3->drawState = Selected3;
		form->Refresh();

		switch (MessageBox::Show(
			L"The hilighted points (green->red->yellow) are in clockwise rotation\nWould you like to continue?",
			L"Clockwise Rotation",
			MessageBoxButtons::YesNo
		)) {
		case DialogResult::Yes:
			pt1->drawState = Unselected;
			pt2->drawState = Unselected;
			pt3->drawState = Unselected;
			CheckPointsRotation(form, pts);
			break;
		default:
			pt1->drawState = Unselected;
			pt2->drawState = Unselected;
			pt3->drawState = Unselected;
			form->Refresh();
			return;
			break;
		}
	}
	else {
		pt1->drawState = Selected1;
		pt2->drawState = Selected2;
		pt3->drawState = Selected3;
		form->Refresh();

		switch (MessageBox::Show(
			L"The hilighted points (green->red->yellow) are in counter-clockwise rotation\nWould you like to continue?",
			L"Counter-Clockwise Rotation",
			MessageBoxButtons::YesNo
		)) {
		case DialogResult::Yes:
			pt1->drawState = Unselected;
			pt2->drawState = Unselected;
			pt3->drawState = Unselected;
			CheckPointsRotation(form, pts);
			break;
		default:
			pt1->drawState = Unselected;
			pt2->drawState = Unselected;
			pt3->drawState = Unselected;
			form->Refresh();
			return;
			break;
		}
	}
}

void ShapeController::GenerateRectangle()
{
	Shapes::Rectangle^ rect{ gcnew Shapes::Rectangle{ DrawingStartPoint, DrawingEndPoint } };
	activeShapes.push_back(rect);
	rectangles.push(rect);
}

void ShapeController::GenerateLine()
{
	Line^ line{ gcnew Line{DrawingStartPoint, DrawingEndPoint} };
	activeShapes.push_back(line);
	lines.push(line);
}

void ShapeController::GeneratePoint()
{
	Shape^ point{ gcnew Shape{ gcnew Shapes::Point{DrawingStartPoint->x, DrawingStartPoint->y} } };
	activeShapes.push_back(point);
	points.push(point);
}

void ShapeController::GenerateStar()
{
	if (starPointCount % 2 == 0) { // Should never happen - but just in case
		MessageBox::Show(L"Stars with even point counts not yet implemented! Please use odd number of points");
		return;
	}
	Star^ star{ gcnew Star{ DrawingStartPoint, DrawingEndPoint, starPointCount } };
	activeShapes.push_back(star);
}

void ShapeController::GenerateArrow()
{
	Arrow^ arrow{ gcnew Arrow{gcnew Line{DrawingStartPoint, DrawingEndPoint}, arrowHeadHeight, arrowHeadAngle} };
	activeShapes.push_back(arrow);
	arrows.push(arrow);
}

void ShapeController::UpdateArrows()
{
	if (arrows.size() <= 0)
		return;

	cliext::queue<Arrow^> arrs = arrows;
	while (!arrs.empty()) {
		arrs.front()->UpdateSize(arrowHeadHeight, arrowHeadAngle);
		arrs.pop();
	}
}
