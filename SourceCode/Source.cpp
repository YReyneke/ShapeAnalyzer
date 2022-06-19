#include "MainForm.h"

using namespace ShapeAnalyzer;

/// Launcher for this application
[STAThreadAttribute]
int main() {
	MainForm fm;
	fm.ShowDialog();
	return 0;
}