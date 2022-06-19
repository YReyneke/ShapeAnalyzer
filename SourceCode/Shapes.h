#pragma once

// Found the STL - kinda
#include <cliext/vector>

// It's PI! At least, as far as I can remember it
#define PI 3.14159265f

using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Shapes {
	/// <summary>
	/// Type of rotation:
	/// <para>Clockwise, AntiClockwise, CoLinear (in a line)</para>
	/// </summary>
	enum Rotation {
		Clockwise,
		AntiClockwise,
		CoLinear
	};

	/// <summary>
	/// Describes which drawing state the controller is in:
	/// <para>DrawPoint, DrawLine, DrawRectangle, DrawStar, DrawArrow</para>
	/// </summary>
	enum DrawMode {
		DrawPoint,
		DrawLine,
		DrawRectangle,
		DrawStar,
		DrawArrow
	};

	/// <summary>
	/// Describes which 'selection' colour you wish to draw in
	/// <para>Unselected, Selected1, Selected2, Selected3</para>
	/// </summary>
	enum DrawHilightState {
		Unselected,
		Selected1,
		Selected2,
		Selected3
	};

	/// <summary>
	/// Container for {x, y} coordinate - Cannot be drawn in window, use 'Shape' class instead.
	/// <para>Includes '+=' override for translating of points</para>
	/// </summary>
	ref class Point {
	public:
		int x, y;

		// Default constructor, must always be initialised with co-ordinates
		Point(int x, int y) : x{ x }, y{ y } {}
		// Copy constructor
		Point(Point^ pt) : x{ pt->x }, y{ pt->y } {}

		// Translate this <- point by another ->
		void operator+=(Point^ p) { x += p->x; y += p->y; }
	};

	/// <summary>
	/// Base class for all shapes - use this for drawing a point object
	/// </summary>
	ref class Shape {
	public:
		DrawHilightState drawState{ Unselected }; // Used to chose which colour the shape should be displayed in
		Point^ origin; // The origin co-ordinates of this shape

		/// <summary>
		/// Default constructor
		/// <para>origin{0,0}</para>
		/// </summary>
		Shape() : origin{ gcnew Point{0,0} } {}

		/// <summary>
		/// Recommended constructor
		/// </summary>
		/// <param name="origin"> The location of this shape on screen</param>
		Shape(Point^ origin) : origin{ origin } {}

		/// Destructor
		~Shape() { delete origin; };
	protected:
		/// Finaliser
		!Shape() { delete origin; }
	
	public:
		/// <summary>
		/// Overridable function, called within 'Paint' function of main form
		/// </summary>
		/// <param name="gfx">Graphics object reference of the calling form</param>
		/// <param name="pen">Pen used to draw the shape</param>
		virtual void DrawShape(Graphics^ gfx, Pen^ pen);

		/// <returns>The hilight colour based on DrawHilightState</returns>
		Color GetHilightColor();
	protected:

		/// <summary>
		/// Internal implementation (and where the actual calculation is performed)
		/// </summary>
		/// <returns>The hilight colour based on DrawHilightState</returns>
		Color GetHilightColor(DrawHilightState DHS);
	};

	/// <summary>
	/// A simple line that can be drawn on the screen
	/// <para>Child of 'Shape' class</para>
	/// </summary>
	ref class Line : Shape {
	public:
		// Origin and start of the line
		Point^ pointA;
		// End of the line... Please mind the gap, and remember to take your luggage with you
		Point^ pointB;

		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="pointA">Start coordinate of the line</param>
		/// <param name="pointB">End coordinate of the line</param>
		Line(Point^ pointA, Point^ pointB) : pointA{ pointA }, pointB{ pointB } { origin = pointA; }

		/// Destructor
		~Line() { delete pointA; delete pointB; };
	protected:
		/// Finaliser
		!Line() { delete pointA; delete pointB; };

	public:
		/// <summary>
		/// Overridable function, called within 'Paint' function of main form
		/// </summary>
		/// <param name="gfx">Graphics object reference of the calling form</param>
		/// <param name="pen">Pen used to draw the shape</param>
		void DrawShape(Graphics^ gfx, Pen^ pen) override;

		/// <summary>
		/// Transforms the line x and y by 'p' coordinates
		/// </summary>
		/// <param name="p">Transformation to apply</param>
		void operator+=(Point^ p) { pointA += p; pointB += p; }
	};

	/// <summary>
	/// Rectangle defined by four lines that can be drawn on screen
	/// <para>Child of 'Shape'</para>
	/// </summary>
	ref class Rectangle : public Shape {
	public:
		// Vertical line 1
		Line^ vLine1;
		// Horizontal line 1
		Line^ hLine1;
		// Vertical line 2
		Line^ vLine2;
		// Horizontal line 2
		Line^ hLine2;

		/// <summary>
		/// Default constructor - creates a new rectangle defined by opposite corners
		/// </summary>
		/// <param name="origin">Initial corner and origin of the rectangle</param>
		/// <param name="farCorner">Farthest corner from the origin</param>
		Rectangle(Point^ origin, Point^ farCorner);

		/// Destructor
		~Rectangle() { delete vLine1; delete hLine1; delete vLine2; delete hLine2; }
	protected:
		/// Finaliser
		!Rectangle() { delete vLine1; delete hLine1; delete vLine2; delete hLine2; }

	public:
		/// <returns>Returns the height of the rectangle (Delta Y)</returns>
		float height() { return vLine1->pointB->y - vLine1->pointA->y; }

		/// <returns>Returns the width of the rectangle (Delta X)</returns>
		float width() { return hLine1->pointB->x - hLine1->pointA->x; }

		/// <summary>
		/// Overridable function, called within 'Paint' function of main form
		/// </summary>
		/// <param name="gfx">Graphics object reference of the calling form</param>
		/// <param name="pen">Pen used to draw the shape</param>
		void DrawShape(Graphics^ gfx, Pen^ pen) override;
	};

	/// <summary>
	/// Star that can be created by any odd number of points
	/// <para>Defined by a number of lines equal to the number of points</para>
	/// <para>Child of 'Shape'</para>
	/// </summary>
	ref class Star : public Shape {

		// The lines that make up the star
		cliext::vector<Line^> lines{};

		// The outer radius of the star from the origin and center of the shape
		float radius;

		// Number of both points and lines that make up the star
		unsigned int pointCount;

	public:
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="origin">Center point and origin of the star</param>
		/// <param name="sizeRef">The point by which the radius of the star is calculated relative to origin</param>
		/// <param name="pointCount">Number of points and lines in this star</param>
		Star(Point^ origin, Point^ sizeRef, unsigned int pointCount);

		/// Destructor
		~Star();
	protected:
		/// Finaliser
		!Star();

	public:
		/// <summary>
		/// Overridable function, called within 'Paint' function of main form
		/// </summary>
		/// <param name="gfx">Graphics object reference of the calling form</param>
		/// <param name="pen">Pen used to draw the shape</param>
		void DrawShape(Graphics^ gfx, Pen^ pen) override;
	};

	/// <summary>
	/// A re-sizeable arrow that sits on the center of a line and points in the direction the line was placed
	/// <para>Child of 'Shape'</para>
	/// </summary>
	ref class Arrow : public Shape {
		// First feather of the arrowhead
		Line^ L1;
		// Second feather of the arrowhead
		Line^ L2;
		// The line the arrow sits on
		Line^ owningLine;

		// Height: height of arrow
		float height;
		// headAngle: Angle of the arrow head (deg)
		float headAngle;

	public:
		/// <summary>
		/// 'Default' constructor
		/// <para>Generates arrow with 50.f length and 90.f headAngle</para>
		/// </summary>
		/// <param name="owningLine">A reference to the line this arrow sits on</param>
		Arrow(Line^ owningLine) { Arrow(owningLine, 50.f, 90.f); }

		/// <summary>
		/// Constructor of arrow onbject
		/// </summary>
		/// <param name="owningLine">Reference of line the arrow sits on</param>
		/// <param name="arrowHeight">Height of the arrow head</param>
		/// <param name="headAngle">Angle/pointiness of the arrow (deg)</param>
		Arrow(Line^ owningLine, float arrowHeight, float headAngle);

		/// Destructor
		~Arrow() { delete L1; delete L2; delete owningLine; }
	protected:
		/// Finaliser
		!Arrow() { delete L1; delete L2; delete owningLine; }

	public:
		/// <summary>
		/// Overridable function, called within 'Paint' function of main form
		/// <para>Draws the arrow as well as the line the arrow sits on</para>
		/// </summary>
		/// <param name="gfx">Graphics object reference of the calling form</param>
		/// <param name="pen">Pen used to draw the shape</param>
		void DrawShape(Graphics^ gfx, Pen^ pen) override;

		/// <summary>
		/// Use this to change the height and angle of the arrow
		/// </summary>
		/// <param name="newHeight">New height of the arrow head</param>
		/// <param name="newHeadAngle">New angle (deg) of the arrow head</param>
		void UpdateSize(float newHeight, float newHeadAngle);

	protected:
		/// <summary>
		/// Function that calculates all the transformation data required to 
		/// place the arrow, with the chosen dimensions and rotation, at the center of the line
		/// </summary>
		void UpdateArrowLines();
	};

	///*** Helper Functions ***///

	/// <summary>
	/// Template function to return MAX of two inputs
	/// </summary>
	/// <typeparam name="T">Type</typeparam>
	/// <returns> a greater than b ? a : b </returns>
	template <typename T>
	inline T Max(T a, T b) {
		return a > b ? a : b;
	}

	/// <summary>
	/// Template function to return MIN of two inputs
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>a less than b ? a : b</returns>
	template <typename T>
	inline T Min(T a, T b) {
		return a < b ? a : b;
	}
	
	/// <summary>
	/// Calculates distance between two shapes
	/// </summary>
	/// <param name="point1"></param>
	/// <param name="point2"></param>
	/// <returns>Distance between points</returns>
	extern float Distance(Point^ point1, Point^ point2);

	/// <summary>
	/// Calculates distance between two shapes
	/// </summary>
	/// <param name="shape1"></param>
	/// <param name="shape2"></param>
	/// <returns>Distance between origins of both shapes</returns>
	extern float Distance(Shape^ shape1, Shape^ shape2);

	/// <summary>
	/// Calculates distance between two shapes
	/// </summary>
	/// <param name="point"></param>
	/// <param name="shape"></param>
	/// <returns>Distance between origin of shape and point</returns>
	extern float Distance(Point^ point, Shape^ shape);

	/// <summary>
	/// Function used to calculate if two 2D rectangles are overlapping each other
	/// </summary>
	/// <param name="rect1">The first rectangle</param>
	/// <param name="rect2">The second rectangle</param>
	/// <returns>'true' if Rectangles are overlapping each other</returns>
	extern bool CheckRectOverlap(Rectangle^ rect1, Rectangle^ rect2);

	/// <summary>
	/// Function used to calculate if two 2D lines intersect each other
	/// </summary>
	/// <param name="line1">The first line</param>
	/// <param name="line2">The second line</param>
	/// <returns>'true' if the lines are intersecting each other</returns>
	extern bool CheckLineIntercept(Line^ line1, Line^ line2);

	/// <summary>
	/// Function used to calculate the orientation of three ordered points
	/// </summary>
	/// <param name="p1">The first point in the sequence</param>
	/// <param name="p2">The second point in the sequence</param>
	/// <param name="p3">The third point in the sequence</param>
	/// <returns>
	/// <para>'Clockwise' if the points rotate in a clockwise orientation</para>
	/// <para>'AntiClockwise' if the points rotate in a counter-clockwise orientation</para>
	/// <para>'CoLinear' if the points do not rotate (hint: this is rare)</para>
	/// </returns>
	extern Rotation CheckPointOrientation(Point^ p1, Point^ p2, Point^ p3);

	/// <summary>
	/// Used to calculate if a point sits between two other points
	/// in the event that 'CheckPointOrientation' returns 'CoLinear'
	/// when checking the straight line intersection
	/// </summary>
	/// <param name="p1">The first outer point</param>
	/// <param name="p2">The second outer point</param>
	/// <param name="p3">The point that is checked to confirm overlap</param>
	/// <returns>'true' if p3 sits between p1 and p2</returns>
	extern bool CheckColinearOverlap(Point^ p1, Point^ p2, Point^ p3);
}