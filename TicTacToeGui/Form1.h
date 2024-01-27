#pragma once

#include <iostream>
#include <string>

using namespace std;


class linked_list {
private:
	class big_node {
	public:
		class small_node {
		public:
			string data;
			small_node* next;
			small_node() : next(0) {}
		};

		small_node* b_data;
		small_node* S_first;
		big_node* b_next;

		big_node() : b_next(0) {}

		big_node(small_node* dataValue) : b_data(dataValue), b_next(0), S_first(dataValue) {
			small_node* s2 = new small_node();
			S_first->next = s2;
			small_node* s3 = new small_node();
			s2->next = s3;
		}
	};

	int mysize;
	big_node* first;

public:
	linked_list() : first(0), mysize(3) {}

	linked_list::~linked_list() {
		big_node* prev = first, * ptr;
		while (prev != 0) {
			big_node::small_node* sprev = prev->S_first, * sptr;
			while (sprev != 0) {
				sptr = sprev->next;
				delete sprev;
				sprev = sptr;
			}
			ptr = prev->b_next;
			delete prev;
			prev = ptr;
		}
	}

	void insert(int row, int col, string value) {
		big_node* ptr = first;
		for (int i = 1; i < row; i++) {
			ptr = ptr->b_next;
		}

		big_node::small_node* sptr = ptr->b_data;
		for (int j = 1; j < col; j++)
			sptr = sptr->next;

		sptr->data = value;
	}

	void drawBoard() {
		big_node::small_node* s1 = new big_node::small_node();
		big_node* b1 = new big_node(s1);
		first = b1;
		big_node::small_node* s2 = new big_node::small_node();
		big_node* b2 = new big_node(s2);
		b1->b_next = b2;
		big_node::small_node* s3 = new big_node::small_node();
		big_node* b3 = new big_node(s3);
		b2->b_next = b3;
		reset();
	}

	void reset() {
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				insert(i, j, "-");

			}
		}
	}

	string getCellValue(int row, int col) {
		big_node* ptr = first;
		for (int i = 1; i < row; i++) {
			ptr = ptr->b_next;
		}

		big_node::small_node* sptr = ptr->b_data;
		for (int j = 1; j < col; j++) {
			sptr = sptr->next;
		}
		return (sptr->data);
	}

	bool isBoardFull() {
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				if (getCellValue(i, j) == "-") {
					return false;
				}
			}
		}
		return true;
	}

	bool checkWin(int row, int col) {

		if (getCellValue(row, 1) == getCellValue(row, 2) && getCellValue(row, 2) == getCellValue(row, 3)) {
			if (getCellValue(row, 1) == "X" || getCellValue(row, 1) == "O")
				return true;
		}

		if (getCellValue(1, col) == getCellValue(2, col) && getCellValue(2, col) == getCellValue(3, col)) {
			if (getCellValue(1, col) == "X" || getCellValue(1, col) == "O")
				return true;
		}

		if (getCellValue(1, 1) == getCellValue(2, 2) && getCellValue(2, 2) == getCellValue(3, 3)) {
			if (getCellValue(2, 2) == "X" || getCellValue(2, 2) == "O")
				return true;
		}

		if (getCellValue(1, 3) == getCellValue(2, 2) && getCellValue(2, 2) == getCellValue(3, 1)) {
			if (getCellValue(2, 2) == "X" || getCellValue(2, 2) == "O")
				return true;
		}

		if (isBoardFull()) {
			return false;
		}

		return false;
	}

};

namespace CppCLRWinFormsProject {
	string value = "X" , P1 , P2;
	int turn = 0 , P1Score = 0, P2Score = 0;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		linked_list* l1;

	public:
		Form1(void)
		{

			InitializeComponent();
			l1 = new linked_list();
			l1->drawBoard();
		}

		string setValue(int& turn) {
			value = turn % 2 == 0 ? value = "X" : value = "O";
			turn++;
			return value;
		}

		void resetBoard() {
			btn1->Text = " ";
			btn2->Text = " ";
			btn3->Text = " ";
			btn4->Text = " ";
			btn5->Text = " ";
			btn6->Text = " ";
			btn7->Text = " ";
			btn8->Text = " ";
			btn9->Text = " ";
			btn1->Enabled = true;
			btn2->Enabled = true;
			btn3->Enabled = true;
			btn4->Enabled = true;
			btn5->Enabled = true;
			btn6->Enabled = true;
			btn7->Enabled = true;
			btn8->Enabled = true;
			btn9->Enabled = true;
			l1->reset();
			turn = 0;
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ StartGame;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::Button^ Reset;
	private: System::Windows::Forms::Button^ NewGame;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Button^ btn6;
	private: System::Windows::Forms::Button^ btn5;
	private: System::Windows::Forms::Button^ btn4;
	private: System::Windows::Forms::Button^ btn3;
	private: System::Windows::Forms::Button^ btn2;
	private: System::Windows::Forms::Button^ btn7;
	private: System::Windows::Forms::Button^ btn9;

	private: System::Windows::Forms::Button^ btn8;

	private: System::Windows::Forms::Button^ btn1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Button^ Exit;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown3;


	protected:
	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel = (gcnew System::Windows::Forms::Panel());
			this->StartGame = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Reset = (gcnew System::Windows::Forms::Button());
			this->NewGame = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->btn6 = (gcnew System::Windows::Forms::Button());
			this->btn5 = (gcnew System::Windows::Forms::Button());
			this->btn4 = (gcnew System::Windows::Forms::Button());
			this->btn3 = (gcnew System::Windows::Forms::Button());
			this->btn7 = (gcnew System::Windows::Forms::Button());
			this->btn8 = (gcnew System::Windows::Forms::Button());
			this->btn1 = (gcnew System::Windows::Forms::Button());
			this->btn2 = (gcnew System::Windows::Forms::Button());
			this->btn9 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Exit = (gcnew System::Windows::Forms::Button());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			this->SuspendLayout();
			// 
			// panel
			// 
			this->panel->Controls->Add(this->StartGame);
			this->panel->Controls->Add(this->label1);
			this->panel->Controls->Add(this->label2);
			this->panel->Location = System::Drawing::Point(0, 0);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(812, 450);
			this->panel->TabIndex = 0;
			// 
			// StartGame
			// 
			this->StartGame->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->StartGame->Cursor = System::Windows::Forms::Cursors::Hand;
			this->StartGame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->StartGame->Location = System::Drawing::Point(234, 192);
			this->StartGame->Name = L"StartGame";
			this->StartGame->Size = System::Drawing::Size(333, 82);
			this->StartGame->TabIndex = 2;
			this->StartGame->Text = L"Start Game";
			this->StartGame->UseVisualStyleBackColor = true;
			this->StartGame->Click += gcnew System::EventHandler(this, &Form1::StartGame_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 40, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Location = System::Drawing::Point(119, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(600, 152);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Welcome to our \r\nTic Tac Toe Game";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label2->Location = System::Drawing::Point(3, 314);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(177, 125);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Created by:\r\nAhmed Fadlya \r\nAley Amin \r\nHassan Al Masrafy\r\nMazen Sameh ";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(20, 28);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(242, 54);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Player X : ";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(20, 94);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(242, 54);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Player O: ";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Reset
			// 
			this->Reset->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Reset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Reset->Location = System::Drawing::Point(32, 238);
			this->Reset->Name = L"Reset";
			this->Reset->Size = System::Drawing::Size(159, 84);
			this->Reset->TabIndex = 4;
			this->Reset->Text = L"Reset";
			this->Reset->UseVisualStyleBackColor = true;
			this->Reset->Click += gcnew System::EventHandler(this, &Form1::Reset_Click);
			// 
			// NewGame
			// 
			this->NewGame->Cursor = System::Windows::Forms::Cursors::Hand;
			this->NewGame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NewGame->Location = System::Drawing::Point(32, 323);
			this->NewGame->Name = L"NewGame";
			this->NewGame->Size = System::Drawing::Size(324, 95);
			this->NewGame->TabIndex = 6;
			this->NewGame->Text = L"Start New Game";
			this->NewGame->UseVisualStyleBackColor = true;
			this->NewGame->Click += gcnew System::EventHandler(this, &Form1::NewGame_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel1->Controls->Add(this->btn6, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->btn5, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->btn4, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->btn3, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->btn7, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->btn8, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->btn1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->btn2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->btn9, 2, 2);
			this->tableLayoutPanel1->Location = System::Drawing::Point(421, 28);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(361, 388);
			this->tableLayoutPanel1->TabIndex = 7;
			// 
			// btn6
			// 
			this->btn6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn6->Location = System::Drawing::Point(243, 132);
			this->btn6->Name = L"btn6";
			this->btn6->Size = System::Drawing::Size(114, 123);
			this->btn6->TabIndex = 8;
			this->btn6->UseVisualStyleBackColor = true;
			this->btn6->Click += gcnew System::EventHandler(this, &Form1::btn6_Click);
			// 
			// btn5
			// 
			this->btn5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn5->Location = System::Drawing::Point(123, 132);
			this->btn5->Name = L"btn5";
			this->btn5->Size = System::Drawing::Size(114, 123);
			this->btn5->TabIndex = 7;
			this->btn5->UseVisualStyleBackColor = true;
			this->btn5->Click += gcnew System::EventHandler(this, &Form1::btn5_Click);
			// 
			// btn4
			// 
			this->btn4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn4->Location = System::Drawing::Point(3, 132);
			this->btn4->Name = L"btn4";
			this->btn4->Size = System::Drawing::Size(114, 123);
			this->btn4->TabIndex = 6;
			this->btn4->UseVisualStyleBackColor = true;
			this->btn4->Click += gcnew System::EventHandler(this, &Form1::btn4_Click);
			// 
			// btn3
			// 
			this->btn3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn3->Location = System::Drawing::Point(243, 3);
			this->btn3->Name = L"btn3";
			this->btn3->Size = System::Drawing::Size(114, 123);
			this->btn3->TabIndex = 5;
			this->btn3->UseVisualStyleBackColor = true;
			this->btn3->Click += gcnew System::EventHandler(this, &Form1::btn3_Click);
			// 
			// btn7
			// 
			this->btn7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn7->Location = System::Drawing::Point(3, 261);
			this->btn7->Name = L"btn7";
			this->btn7->Size = System::Drawing::Size(114, 123);
			this->btn7->TabIndex = 3;
			this->btn7->UseVisualStyleBackColor = true;
			this->btn7->Click += gcnew System::EventHandler(this, &Form1::btn7_Click);
			// 
			// btn8
			// 
			this->btn8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn8->Location = System::Drawing::Point(123, 261);
			this->btn8->Name = L"btn8";
			this->btn8->Size = System::Drawing::Size(114, 123);
			this->btn8->TabIndex = 1;
			this->btn8->UseVisualStyleBackColor = true;
			this->btn8->Click += gcnew System::EventHandler(this, &Form1::btn8_Click);
			// 
			// btn1
			// 
			this->btn1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn1->Location = System::Drawing::Point(3, 3);
			this->btn1->Name = L"btn1";
			this->btn1->Size = System::Drawing::Size(114, 123);
			this->btn1->TabIndex = 0;
			this->btn1->UseVisualStyleBackColor = true;
			this->btn1->Click += gcnew System::EventHandler(this, &Form1::btn1_Click);
			// 
			// btn2
			// 
			this->btn2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn2->Location = System::Drawing::Point(123, 3);
			this->btn2->Name = L"btn2";
			this->btn2->Size = System::Drawing::Size(114, 123);
			this->btn2->TabIndex = 4;
			this->btn2->UseVisualStyleBackColor = true;
			this->btn2->Click += gcnew System::EventHandler(this, &Form1::btn2_Click);
			// 
			// btn9
			// 
			this->btn9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn9->Location = System::Drawing::Point(243, 261);
			this->btn9->Name = L"btn9";
			this->btn9->Size = System::Drawing::Size(114, 123);
			this->btn9->TabIndex = 2;
			this->btn9->UseVisualStyleBackColor = true;
			this->btn9->Click += gcnew System::EventHandler(this, &Form1::btn9_Click);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->tableLayoutPanel1);
			this->panel2->Controls->Add(this->NewGame);
			this->panel2->Controls->Add(this->Exit);
			this->panel2->Controls->Add(this->Reset);
			this->panel2->Controls->Add(this->numericUpDown1);
			this->panel2->Controls->Add(this->numericUpDown2);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->numericUpDown3);
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(811, 447);
			this->panel2->TabIndex = 3;
			this->panel2->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(21, 159);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(241, 54);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Draws    : ";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Exit
			// 
			this->Exit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Exit->Location = System::Drawing::Point(193, 238);
			this->Exit->Name = L"Exit";
			this->Exit->Size = System::Drawing::Size(163, 84);
			this->Exit->TabIndex = 5;
			this->Exit->Text = L"Exit";
			this->Exit->UseVisualStyleBackColor = true;
			this->Exit->Click += gcnew System::EventHandler(this, &Form1::Exit_Click);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->BackColor = System::Drawing::Color::Teal;
			this->numericUpDown1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->numericUpDown1->Cursor = System::Windows::Forms::Cursors::Default;
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numericUpDown1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->numericUpDown1->InterceptArrowKeys = false;
			this->numericUpDown1->Location = System::Drawing::Point(285, 32);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->ReadOnly = true;
			this->numericUpDown1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->numericUpDown1->Size = System::Drawing::Size(233, 56);
			this->numericUpDown1->TabIndex = 8;
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->BackColor = System::Drawing::Color::Teal;
			this->numericUpDown2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->numericUpDown2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numericUpDown2->Location = System::Drawing::Point(285, 94);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->ReadOnly = true;
			this->numericUpDown2->Size = System::Drawing::Size(217, 56);
			this->numericUpDown2->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(20, 28);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(242, 54);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Player X : ";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->BackColor = System::Drawing::Color::Teal;
			this->numericUpDown3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->numericUpDown3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numericUpDown3->Location = System::Drawing::Point(285, 157);
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->ReadOnly = true;
			this->numericUpDown3->Size = System::Drawing::Size(217, 56);
			this->numericUpDown3->TabIndex = 11;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Teal;
			this->ClientSize = System::Drawing::Size(812, 444);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel);
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(830, 491);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(830, 491);
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tic Tac Toe";
			this->panel->ResumeLayout(false);
			this->panel->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public: System::Void StartGame_Click(System::Object^ sender, System::EventArgs^ e) {
		this->panel->Visible = false;
		this->panel2->Visible = true;
	}
	private: System::Void btn1_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(1, 1, value);

		if (value == "X")
			btn1->Text = "X";
		else
			btn1->Text = "O";

		btn1->Enabled = false;
		if (l1->checkWin(1, 1)) {
			l1->getCellValue(1, 1) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}

		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn2_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(1, 2, value);

		if (value == "X")
			btn2->Text = "X";
		else
			
			btn2->Text = "O";

		btn2->Enabled = false;
		if (l1->checkWin(1, 2)) {
			l1->getCellValue(1, 2) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn3_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(1, 3, value);

		if (value == "X")
			btn3->Text = "X";
		else
			btn3->Text = "O";

		btn3->Enabled = false;
		if (l1->checkWin(1, 3)){
			l1->getCellValue(1, 3) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn4_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(2, 1, value);

		if (value == "X")
			btn4->Text = "X";
		else
			btn4->Text = "O";

		btn4->Enabled = false;
		if (l1->checkWin(2, 1)) {
			l1->getCellValue(2, 1) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn5_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(2, 2, value);

		if (value == "X")
			btn5->Text = "X";
		else
			btn5->Text = "O";

		btn5->Enabled = false;
		if (l1->checkWin(2, 2)) {
			l1->getCellValue(2, 2) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn6_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(2, 3, value);

		if (value == "X")
			btn6->Text = "X";
		else
			btn6->Text = "O";

		btn6->Enabled = false;
		if (l1->checkWin(2, 3)) {
			l1->getCellValue(2, 3) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn7_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(3, 1, value);

		if (value == "X")
			btn7->Text = "X";
		else
			btn7->Text = "O";

		btn7->Enabled = false;
		if (l1->checkWin(3, 1)) {
			l1->getCellValue(3, 1) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();

		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn8_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(3, 2, value);

		if (value == "X")
			btn8->Text = "X";
		else
			btn8->Text = "O";

		btn8->Enabled = false;
		if (l1->checkWin(3, 2)) {
			l1->getCellValue(3, 2) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void btn9_Click(System::Object^ sender, System::EventArgs^ e) {
		value = setValue(turn);
		l1->insert(3, 3, value);

		if (value == "X")
			btn9->Text = "X";
		else
			btn9->Text = "O";

		btn9->Enabled = false;
		if (l1->checkWin(3, 3)) {
			l1->getCellValue(3, 3) == "X" ? numericUpDown1->UpButton() : numericUpDown2->UpButton();
			this->resetBoard();
		}
		else if (l1->isBoardFull()) {
			numericUpDown3->UpButton();
			this->resetBoard();
		}
	}
	private: System::Void Reset_Click(System::Object^ sender, System::EventArgs^ e) {
		this->resetBoard();
	}
	private: System::Void Exit_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void NewGame_Click(System::Object^ sender, System::EventArgs^ e) {
		this->resetBoard();
		numericUpDown1->Value = 0;
		numericUpDown2->Value = 0;
		numericUpDown3->Value = 0;
	}
};
}