#pragma once
#include "ShapeController.h"

namespace ShapeAnalyzer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace Shapes;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	protected:
		ShapeController^ shapeController{ gcnew ShapeController{} };

	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::RadioButton^ rbnDrawRectangle;

	private: System::Windows::Forms::RadioButton^ rbnDrawLine;
	private: System::Windows::Forms::RadioButton^ rbnDrawPoint;
	private: System::Windows::Forms::RadioButton^ rbnDrawStar;
	private: System::Windows::Forms::RadioButton^ rbnDrawArrowLine;
	private: System::Windows::Forms::TableLayoutPanel^ tlopDrawingArea;
	private: System::Windows::Forms::NumericUpDown^ nudStarPointCount;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnClearShapes;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Button^ btnCheckLineIntersect;

	private: System::Windows::Forms::Button^ btnCheckRectangles;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TrackBar^ tbrArrowAngle;
	private: System::Windows::Forms::TrackBar^ tbrArrowSize;

	private: System::Windows::Forms::Button^ btnCheckPointRotation;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->rbnDrawRectangle = (gcnew System::Windows::Forms::RadioButton());
			this->rbnDrawLine = (gcnew System::Windows::Forms::RadioButton());
			this->rbnDrawPoint = (gcnew System::Windows::Forms::RadioButton());
			this->rbnDrawStar = (gcnew System::Windows::Forms::RadioButton());
			this->rbnDrawArrowLine = (gcnew System::Windows::Forms::RadioButton());
			this->tlopDrawingArea = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->nudStarPointCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnClearShapes = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->btnCheckPointRotation = (gcnew System::Windows::Forms::Button());
			this->btnCheckRectangles = (gcnew System::Windows::Forms::Button());
			this->btnCheckLineIntersect = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbrArrowAngle = (gcnew System::Windows::Forms::TrackBar());
			this->tbrArrowSize = (gcnew System::Windows::Forms::TrackBar());
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudStarPointCount))->BeginInit();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbrArrowAngle))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbrArrowSize))->BeginInit();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::SandyBrown;
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Inset;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->rbnDrawRectangle, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->rbnDrawLine, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->rbnDrawPoint, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->rbnDrawStar, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->rbnDrawArrowLine, 0, 4);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 28)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 24)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(199, 151);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// rbnDrawRectangle
			// 
			this->rbnDrawRectangle->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rbnDrawRectangle->AutoSize = true;
			this->rbnDrawRectangle->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rbnDrawRectangle->Location = System::Drawing::Point(5, 5);
			this->rbnDrawRectangle->Name = L"rbnDrawRectangle";
			this->rbnDrawRectangle->Size = System::Drawing::Size(189, 22);
			this->rbnDrawRectangle->TabIndex = 2;
			this->rbnDrawRectangle->TabStop = true;
			this->rbnDrawRectangle->Text = L"Draw Rectangle";
			this->rbnDrawRectangle->UseVisualStyleBackColor = true;
			// 
			// rbnDrawLine
			// 
			this->rbnDrawLine->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rbnDrawLine->AutoSize = true;
			this->rbnDrawLine->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rbnDrawLine->Location = System::Drawing::Point(5, 35);
			this->rbnDrawLine->Name = L"rbnDrawLine";
			this->rbnDrawLine->Size = System::Drawing::Size(189, 23);
			this->rbnDrawLine->TabIndex = 3;
			this->rbnDrawLine->TabStop = true;
			this->rbnDrawLine->Text = L"Draw Line";
			this->rbnDrawLine->UseVisualStyleBackColor = true;
			// 
			// rbnDrawPoint
			// 
			this->rbnDrawPoint->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rbnDrawPoint->AutoSize = true;
			this->rbnDrawPoint->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rbnDrawPoint->Location = System::Drawing::Point(5, 66);
			this->rbnDrawPoint->Name = L"rbnDrawPoint";
			this->rbnDrawPoint->Size = System::Drawing::Size(189, 21);
			this->rbnDrawPoint->TabIndex = 4;
			this->rbnDrawPoint->TabStop = true;
			this->rbnDrawPoint->Text = L"Draw Point";
			this->rbnDrawPoint->UseVisualStyleBackColor = true;
			// 
			// rbnDrawStar
			// 
			this->rbnDrawStar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rbnDrawStar->AutoSize = true;
			this->rbnDrawStar->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rbnDrawStar->Location = System::Drawing::Point(5, 95);
			this->rbnDrawStar->Name = L"rbnDrawStar";
			this->rbnDrawStar->Size = System::Drawing::Size(189, 22);
			this->rbnDrawStar->TabIndex = 5;
			this->rbnDrawStar->TabStop = true;
			this->rbnDrawStar->Text = L"Draw Star";
			this->rbnDrawStar->UseVisualStyleBackColor = true;
			// 
			// rbnDrawArrowLine
			// 
			this->rbnDrawArrowLine->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rbnDrawArrowLine->AutoSize = true;
			this->rbnDrawArrowLine->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rbnDrawArrowLine->Location = System::Drawing::Point(5, 125);
			this->rbnDrawArrowLine->Name = L"rbnDrawArrowLine";
			this->rbnDrawArrowLine->Size = System::Drawing::Size(189, 21);
			this->rbnDrawArrowLine->TabIndex = 6;
			this->rbnDrawArrowLine->TabStop = true;
			this->rbnDrawArrowLine->Text = L"Draw Arrowed Line";
			this->rbnDrawArrowLine->UseVisualStyleBackColor = true;
			// 
			// tlopDrawingArea
			// 
			this->tlopDrawingArea->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tlopDrawingArea->BackColor = System::Drawing::SystemColors::Desktop;
			this->tlopDrawingArea->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tlopDrawingArea->ColumnCount = 1;
			this->tlopDrawingArea->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tlopDrawingArea->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->tlopDrawingArea->Location = System::Drawing::Point(218, 12);
			this->tlopDrawingArea->Name = L"tlopDrawingArea";
			this->tlopDrawingArea->RowCount = 1;
			this->tlopDrawingArea->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tlopDrawingArea->Size = System::Drawing::Size(1058, 689);
			this->tlopDrawingArea->TabIndex = 2;
			this->tlopDrawingArea->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tlopDrawingArea_Paint);
			this->tlopDrawingArea->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::tlopDrawingArea_MouseDown);
			this->tlopDrawingArea->MouseEnter += gcnew System::EventHandler(this, &MainForm::tlopDrawingArea_MouseEnter);
			this->tlopDrawingArea->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::tlopDrawingArea_MouseUp);
			// 
			// nudStarPointCount
			// 
			this->nudStarPointCount->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->nudStarPointCount->Location = System::Drawing::Point(166, 171);
			this->nudStarPointCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->nudStarPointCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->nudStarPointCount->Name = L"nudStarPointCount";
			this->nudStarPointCount->ReadOnly = true;
			this->nudStarPointCount->Size = System::Drawing::Size(45, 20);
			this->nudStarPointCount->TabIndex = 3;
			this->nudStarPointCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->nudStarPointCount->ValueChanged += gcnew System::EventHandler(this, &MainForm::nudStarPointCount_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::SandyBrown;
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 171);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 20);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Star Point Count";
			// 
			// btnClearShapes
			// 
			this->btnClearShapes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnClearShapes->BackColor = System::Drawing::Color::Maroon;
			this->btnClearShapes->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClearShapes->ForeColor = System::Drawing::Color::SandyBrown;
			this->btnClearShapes->Location = System::Drawing::Point(3, 3);
			this->btnClearShapes->Name = L"btnClearShapes";
			this->btnClearShapes->Size = System::Drawing::Size(193, 35);
			this->btnClearShapes->TabIndex = 5;
			this->btnClearShapes->Text = L"Clear Shapes";
			this->btnClearShapes->UseVisualStyleBackColor = false;
			this->btnClearShapes->Click += gcnew System::EventHandler(this, &MainForm::btnClearShapes_Click);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->btnCheckPointRotation, 0, 3);
			this->tableLayoutPanel2->Controls->Add(this->btnClearShapes, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->btnCheckRectangles, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->btnCheckLineIntersect, 0, 2);
			this->tableLayoutPanel2->Location = System::Drawing::Point(12, 414);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 4;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 47.12644F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 52.87356F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 46)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 40)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(199, 174);
			this->tableLayoutPanel2->TabIndex = 6;
			// 
			// btnCheckPointRotation
			// 
			this->btnCheckPointRotation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnCheckPointRotation->BackColor = System::Drawing::Color::SandyBrown;
			this->btnCheckPointRotation->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckPointRotation->Location = System::Drawing::Point(3, 136);
			this->btnCheckPointRotation->Name = L"btnCheckPointRotation";
			this->btnCheckPointRotation->Size = System::Drawing::Size(193, 35);
			this->btnCheckPointRotation->TabIndex = 11;
			this->btnCheckPointRotation->Text = L"Check Point Rotation";
			this->btnCheckPointRotation->UseVisualStyleBackColor = false;
			this->btnCheckPointRotation->Click += gcnew System::EventHandler(this, &MainForm::btnCheckPointRotation_Click);
			// 
			// btnCheckRectangles
			// 
			this->btnCheckRectangles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnCheckRectangles->BackColor = System::Drawing::Color::SandyBrown;
			this->btnCheckRectangles->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckRectangles->Location = System::Drawing::Point(3, 44);
			this->btnCheckRectangles->Name = L"btnCheckRectangles";
			this->btnCheckRectangles->Size = System::Drawing::Size(193, 40);
			this->btnCheckRectangles->TabIndex = 7;
			this->btnCheckRectangles->Text = L"Check Rectangle Overlap";
			this->btnCheckRectangles->UseVisualStyleBackColor = false;
			this->btnCheckRectangles->Click += gcnew System::EventHandler(this, &MainForm::btnCheckRectangles_Click);
			// 
			// btnCheckLineIntersect
			// 
			this->btnCheckLineIntersect->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnCheckLineIntersect->BackColor = System::Drawing::Color::SandyBrown;
			this->btnCheckLineIntersect->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckLineIntersect->Location = System::Drawing::Point(3, 90);
			this->btnCheckLineIntersect->Name = L"btnCheckLineIntersect";
			this->btnCheckLineIntersect->Size = System::Drawing::Size(193, 40);
			this->btnCheckLineIntersect->TabIndex = 7;
			this->btnCheckLineIntersect->Text = L"Check Line Intersections";
			this->btnCheckLineIntersect->UseVisualStyleBackColor = false;
			this->btnCheckLineIntersect->Click += gcnew System::EventHandler(this, &MainForm::btnCheckLineIntersect_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::SandyBrown;
			this->label2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label2->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 214);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 20);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Arrow Angle";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::SandyBrown;
			this->label3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label3->Font = (gcnew System::Drawing::Font(L"Centaur", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 317);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(106, 20);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Arrow Length";
			// 
			// tbrArrowAngle
			// 
			this->tbrArrowAngle->BackColor = System::Drawing::Color::SandyBrown;
			this->tbrArrowAngle->Location = System::Drawing::Point(12, 253);
			this->tbrArrowAngle->Maximum = 90;
			this->tbrArrowAngle->Minimum = 30;
			this->tbrArrowAngle->Name = L"tbrArrowAngle";
			this->tbrArrowAngle->Size = System::Drawing::Size(199, 45);
			this->tbrArrowAngle->SmallChange = 5;
			this->tbrArrowAngle->TabIndex = 9;
			this->tbrArrowAngle->Value = 90;
			this->tbrArrowAngle->ValueChanged += gcnew System::EventHandler(this, &MainForm::tbrArrowAngle_ValueChanged);
			// 
			// tbrArrowSize
			// 
			this->tbrArrowSize->BackColor = System::Drawing::Color::SandyBrown;
			this->tbrArrowSize->Location = System::Drawing::Point(12, 351);
			this->tbrArrowSize->Maximum = 50;
			this->tbrArrowSize->Minimum = 5;
			this->tbrArrowSize->Name = L"tbrArrowSize";
			this->tbrArrowSize->Size = System::Drawing::Size(199, 45);
			this->tbrArrowSize->SmallChange = 5;
			this->tbrArrowSize->TabIndex = 10;
			this->tbrArrowSize->Value = 30;
			this->tbrArrowSize->ValueChanged += gcnew System::EventHandler(this, &MainForm::tbrArrowSize_ValueChanged);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::MistyRose;
			this->ClientSize = System::Drawing::Size(1288, 713);
			this->Controls->Add(this->tbrArrowSize);
			this->Controls->Add(this->tbrArrowAngle);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->nudStarPointCount);
			this->Controls->Add(this->tlopDrawingArea);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"Shape Analyser v0.1";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudStarPointCount))->EndInit();
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbrArrowAngle))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbrArrowSize))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// Update draw mode when mouse enters drawing region
		private: System::Void tlopDrawingArea_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			if (rbnDrawRectangle->Checked)
				shapeController->drawMode = Shapes::DrawMode::DrawRectangle;
			if (rbnDrawLine->Checked)
				shapeController->drawMode = Shapes::DrawMode::DrawLine;
			if (rbnDrawPoint->Checked)
				shapeController->drawMode = Shapes::DrawMode::DrawPoint;
			if (rbnDrawStar->Checked)
				shapeController->drawMode = Shapes::DrawMode::DrawStar;
			if (rbnDrawArrowLine->Checked)
				shapeController->drawMode = Shapes::DrawMode::DrawArrow;
		}
		// Start drawing when mouse pressed
		private: System::Void tlopDrawingArea_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			shapeController->StartDrawing(e->X, e->Y);
		}
		// Finish drawing when mouse released
		private: System::Void tlopDrawingArea_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			shapeController->StopDrawing(e->X, e->Y);
			Refresh(); // Show the changes on screen
		}
		private: System::Void tlopDrawingArea_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			// Store the current graphics object for draw calls
			Graphics^ g = e->Graphics;

			// Create pen used to draw all the shapes
			Pen^ pen = gcnew Pen(Color::Blue, 3.f);

			for (int i{ 0 }; i < shapeController->GetActiveShapes().size(); i++) {
				pen->Color = shapeController->GetActiveShapes()[i]->GetHilightColor();
				shapeController->GetActiveShapes()[i]->DrawShape(g, pen);
			}
			
			// Forcefully remove pen from memory
			delete pen;
		}
		private: System::Void btnClearShapes_Click(System::Object^ sender, System::EventArgs^ e) {
			shapeController->ClearShapes();
			Refresh(); // Show the changes on screen
		}
		private: System::Void btnCheckRectangles_Click(System::Object^ sender, System::EventArgs^ e) {
			shapeController->CheckRectanglesOverlap(this);
		}
		private: System::Void btnCheckLineIntersect_Click(System::Object^ sender, System::EventArgs^ e) {
			shapeController->CheckLinesIntersect(this);
		}
		private: System::Void btnCheckPointRotation_Click(System::Object^ sender, System::EventArgs^ e) {
			shapeController->CheckPointsRotation(this);
		}
		private: System::Void nudStarPointCount_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			shapeController->SetStarPointCount(static_cast<unsigned int>(nudStarPointCount->Value));
		}
		private: System::Void tbrArrowAngle_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			shapeController->SetArrowHeadAngle(tbrArrowAngle->Value);
			Refresh(); // Show the changes on screen
		}
		private: System::Void tbrArrowSize_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			shapeController->SetArrowSize(tbrArrowSize->Value);
			Refresh(); // Show the changes on screen
		}
	};
}
