#pragma once

// Found the STL - Kinda
#include <cliext/vector>
#include <cliext/queue>
#include "Shapes.h"

using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace Shapes; // Look ma, my own namespace

/// <summary>
/// Controller that handles the generation, storage and removal of all the shapes in the scene
/// </summary>
ref class ShapeController
{
public:
	/// <summary>
	/// The currently selected drawing mode
	/// <para>Used to switch between the different shapes</para>
	/// </summary>
	Shapes::DrawMode drawMode{ DrawRectangle };

protected:
	
	// A reference to the initial drawing position of the current shape
	Shapes::Point^ DrawingStartPoint{};
	// A reference to the final drawing position of the current shape
	Shapes::Point^ DrawingEndPoint{};

	// Variable representing the user's chosen number of points the next star will be drawn in
	unsigned int starPointCount{ 5 };
	// Variable representing the user's chosen arrow height (in pixels)
	float arrowHeadHeight{ 30 };
	// Variable representing the user's chosen arrow head angle (in degrees)
	float arrowHeadAngle{ 90 };

	// A vector containing all active shapes in the scene
	cliext::vector<Shape^> activeShapes{};
	// A queue representing all the rectangles in the scene - iterated through when checking overlap
	cliext::queue<Shapes::Rectangle^> rectangles{};
	// A queue representing all the 'line' shapes drawn in the scene (not all the lines within other shapes) - iterated through when checking intersections
	cliext::queue<Line^> lines{};
	// A queue representing all the 'point' shapes in the scene (not all the points within other shapes) - iterated through when checking rotations
	cliext::queue<Shape^> points{};
	// A queue representing all arrows in the scene - iterated through whenever the 'arrow angle' or 'arrow length' sliders are modified
	cliext::queue<Arrow^> arrows{};

	/// Future proof destructor
	~ShapeController() { ClearShapes(); delete DrawingStartPoint; delete DrawingEndPoint; }
protected:
	/// Future proof finaliser
	!ShapeController() { ClearShapes(); delete DrawingStartPoint; delete DrawingEndPoint; }

private:
	/// <summary>
	/// Creates a new rectangle based on 'DrawingStartPoint' and 'DrawingEndPoint'
	/// then adds it to the activeShapes vector and the rectangles queue
	/// </summary>
	void GenerateRectangle();

	/// <summary>
	/// Creates a new line based on 'DrawingStartPoint' and 'DrawingEndPoint'
	/// then adds it to the 'activeShapes' vector and the 'lines' queue
	/// </summary>
	void GenerateLine();

	/// <summary>
	/// Creates a new drawable point based on 'DrawingStartPoint'
	/// then adds it to the 'activeShapes' vector and the 'points' queue
	/// </summary>
	void GeneratePoint();

	/// <summary>
	/// Creates a new star based on 'DrawingStartPoint' and 'DrawingEndPoint'
	/// then adds it to the 'activeShapes' vector
	/// </summary>
	void GenerateStar();

	/// <summary>
	/// Creates a new arrow and line for it to sit on based on 'DrawingStartPoint' and 'DrawingEndPoint'
	/// then adds it to the 'activeShapes' vector and the 'arrows' queue
	/// </summary>
	void GenerateArrow();

	/// <summary>
	/// Used to update the arrow dimensions based on stored arrow height and angle
	/// </summary>
	void UpdateArrows();

public:

	/// <summary>
	/// Stores the mouse's coordinate in 'DrawingStartPoint' and waits for completion
	/// </summary>
	void StartDrawing(int mouse_x, int mouse_y);

	/// <summary>
	/// Selects which shape to generate based on user's choice and generates it based on drawing start and end points
	/// <para>after storing mouse's new coordinates in 'DrawingEndPoint'</para>
	/// </summary>
	void StopDrawing(int mouse_x, int mouse_y);

	/// <returns>A copied list of references to all the shapes in the scene</returns>
	cliext::vector<Shape^> GetActiveShapes() { return activeShapes; }

	/// <summary>
	/// Cleares the list of active objects and empties all the queues as well
	/// </summary>
	void ClearShapes();

	/// <summary>
	/// Called when user presses the 'Check Rectangles Overlap' button
	/// </summary>
	/// <param name="form">The form that will be refreshed when calculation is complete</param>
	void CheckRectanglesOverlap(System::Windows::Forms::Form^ form);

	/// <summary>
	/// Called when user presses the 'Check Lines Intersect' button
	/// </summary>
	/// <param name="form">The form that will be refreshed when calculation is complete</param>
	void CheckLinesIntersect(System::Windows::Forms::Form^ form);

	/// <summary>
	/// Called when user presses the 'Check Point Rotation' button
	/// </summary>
	/// <param name="form">The form that will be refreshed when calculation is complete</param>
	void CheckPointsRotation(System::Windows::Forms::Form^ form);

protected:

	/// <summary>
	/// Iterator that displays overlap result message to user and, upon request, moves to the next pair of rectangles
	/// </summary>
	/// <param name="form">The form that will be refreshed when calculation is complete</param>
	/// <param name="rects">The current queue of rectangles that should be checked</param>
	void CheckRectanglesOverlap(System::Windows::Forms::Form^ form, cliext::queue<Shapes::Rectangle^> rects);

	/// <summary>
	/// Iterator that displays intersect result message to user and, upon request, moves to the next pair of lines
	/// </summary>
	/// <param name="form">The form that will be refreshed when calculation is complete</param>
	/// <param name="lns">The current queue of lines that should be checked</param>
	void CheckLinesIntersect(System::Windows::Forms::Form^ form, cliext::queue<Line^> lns);

	/// <summary>
	/// Iterator that displays orientation result message to user and, upon request, moves to the next triplet of points
	/// </summary>
	/// <param name="form">The form that will be refreshed when calculation is complete</param>
	/// <param name="lns">The current queue of points that should be checked</param>
	void CheckPointsRotation(System::Windows::Forms::Form^ form, cliext::queue<Shape^> pts);

public:

	/// <summary>
	/// Updates the number of points the next generated star will consist of
	/// <para>Called when user modifies the star point count numberic up-down</para>
	/// </summary>
	/// <param name="newPointCount">New number of points</param>
	void SetStarPointCount(unsigned int newPointCount) { starPointCount = newPointCount; }

	/// <summary>
	/// Updates the height of all arrow heads currently in the scene
	/// <para>Called when user modifies the arrow length slider</para>
	/// </summary>
	/// <param name="newSize">New height of arrow head</param>
	void SetArrowSize(float newSize) { arrowHeadHeight = newSize; UpdateArrows(); }

	/// <summary>
	/// Updates the angle for all arrow heads currently in the scene
	/// <para>Called when user modifies the arrow angle slider</para>
	/// </summary>
	/// <param name="newAngle">New angle of arrow head</param>
	void SetArrowHeadAngle(float newAngle) { arrowHeadAngle = newAngle; UpdateArrows(); }
};