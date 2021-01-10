﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool isPressed_1, isPressed_2, isPressed_3, isPressed_4 = false;
TRect ellipse_loc = {420, 200, 520, 300 };
bool move = false;
//---------------------------------------------------------------------------
void recolorScreen(){
	Form1->Canvas->Brush->Color = TColor(RGB(255, 0, 255));

	TRect screen;
	screen.Top = 0;
	screen.Left = 0;
	screen.Bottom = Form1->Height;
	screen.Right = Form1->Width;

	Form1->Canvas->FillRect(screen);
}
//---------------------------------------------------------------------------
void Task_1(){
	recolorScreen();

	Form1->Canvas->Pen->Width = 1;
	Form1->Canvas->Brush->Color = clBtnFace;
	Form1->Canvas->Brush->Color = clYellow;
	Form1->Canvas->Ellipse(80,80,400,400);


	//left eye
	Form1->Canvas->Brush->Color = clBlack;
	Form1->Canvas->Ellipse(120, 160, 220, 260);
	Form1->Canvas->Brush->Color = clWhite;
	Form1->Canvas->Ellipse(127, 161, 201, 235);
	Form1->Canvas->Ellipse(180, 240, 190, 250);

	//right eyebrow
	Form1->Canvas->Pen->Width = 5;
	Form1->Canvas->Brush->Color = clBlack;
	Form1->Canvas->Arc(90, 100, 160, 160, 125, 160, 160, 130);

	//right eye
	Form1->Canvas->Pen->Width = 1;
	Form1->Canvas->Brush->Color = clBlack;
	Form1->Canvas->Ellipse(260, 160, 360, 260);
	Form1->Canvas->Brush->Color = clWhite;
	Form1->Canvas->Ellipse(267, 161, 341, 235);
	Form1->Canvas->Ellipse(325, 240, 335, 250);

	//left eyebrow
	Form1->Canvas->Pen->Width = 5;
	Form1->Canvas->Brush->Color = clBlack;
	Form1->Canvas->Arc(320, 100, 390, 160, 230, 130, 355, 160);

	Form1->Canvas->Pen->Width = 5;
	Form1->Canvas->Brush->Color = clBlack;
	Form1->Canvas->Arc(190, 300, 290, 350, 290, 320, 190, 320);

}
//---------------------------------------------------------------------------
void recolorScreen2(){

	auto unit = Form1->Width / 3;

	Form1->Canvas->Brush->Color = TColor(RGB(0, 80, 164));

	TRect screen;
	screen.Top = 0;
	screen.Left = 0;
	screen.Bottom = Form1->Height;
	screen.Right = unit;
	Form1->Canvas->FillRect(screen);

	Form1->Canvas->Brush->Color = TColor(RGB(255, 255, 255));

	screen.Top = 0;
	screen.Left = unit;
	screen.Bottom = Form1->Height;
	screen.Right = unit * 2;
	Form1->Canvas->FillRect(screen);

	Form1->Canvas->Brush->Color = TColor(RGB(239, 65, 53));

	screen.Top = 0;
	screen.Left = unit * 2;
	screen.Bottom = Form1->Height;
	screen.Right = unit * 3;
	Form1->Canvas->FillRect(screen);
}
//---------------------------------------------------------------------------
void Task_2(){
	recolorScreen2();

	Form1->Canvas->Brush->Color = TColor();
	Form1->Canvas->Font->Name = "Brush Script MT";
	Form1-> Canvas->Font->Color = TColor(RGB(231, 225, 7));
	Form1->Canvas->Font->Style = TFontStyles() << fsBold;
	Form1->Canvas->Font->Size = 21;
	Form1->Canvas->TextOut(10, 10, "On a dit très justement que la beauté naît dans l'oeil de celui qui la découvre. ");

	Form1->Canvas->Font->Name = "Times New Roman";
	Form1-> Canvas->Font->Color = TColor(RGB(231, 225, 7));
	Form1->Canvas->Font->Style = TFontStyles() << fsBold;
	Form1->Canvas->Font->Size = 21;
	Form1->Canvas->TextOut(25, 100, "It has been truly said that beauty is in the eye of the beholder. ");

}
//---------------------------------------------------------------------------
void Task_5(){

	Form1->Canvas->Brush->Color = TColor(RGB(random(255), random(255), random(255)));

	TRect screen;
	screen.Top = 0;
	screen.Left = 0;
	screen.Bottom = Form1->Height;
	screen.Right = Form1->Width;

	Form1->Canvas->FillRect(screen);

	Form1->Canvas->Pen->Width = 1;
	Form1->Canvas->Brush->Color = clBtnFace;
	Form1->Canvas->Brush->Color = TColor(RGB(random(255), random(255), random(255)));
	Form1->Canvas->Ellipse(80,80,400,400);
}
//---------------------------------------------------------------------------
void Task_6(){

    Form1->Canvas->Pen->Width = 1;
	Form1->Canvas->Brush->Color = clBtnFace;
	Form1->Canvas->Brush->Color = TColor(RGB(255, 255, 255));
	Form1->Canvas->Ellipse(ellipse_loc.Left, ellipse_loc.Top, ellipse_loc.Right, ellipse_loc.Bottom);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	isPressed_1 = true;
	isPressed_2 = false;
	isPressed_3 = false;
	isPressed_4 = false;
	InvalidateRect(Form1->Handle, 0, False);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	isPressed_1 = false;
	isPressed_2 = true;
	isPressed_3 = false;
	isPressed_4 = false;
	InvalidateRect(Form1->Handle, 0, false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
	InvalidateRect(Form1->Handle, 0, False);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
    if (isPressed_1) {
		Task_1();
	}
	if (isPressed_2) {
		Task_2();
	}
	if (isPressed_3) {

		Task_5();
	}
	if (isPressed_4) {
		Task_6();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	isPressed_1 = false;
	isPressed_2 = false;
	isPressed_3 = true;
	isPressed_4 = false;
	InvalidateRect(Form1->Handle, 0, false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
//	isPressed_1 = false;
//	isPressed_2 = false;
//	isPressed_3 = false;
	isPressed_4 = true;
	InvalidateRect(Form1->Handle, &ellipse_loc, false);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    int radius = (ellipse_loc.Right - ellipse_loc.Left) / 2;

	if (abs(radius + ellipse_loc.Left - X) <= radius && abs(radius + ellipse_loc.Top - Y) <= radius)
	{
		if (isPressed_4 && Button == mbRight)
		{
			isPressed_4 = false;
			Refresh();
		}
		else if (isPressed_4 && Button == mbLeft)
		{
		move = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    if (Button == mbLeft) {
		move = false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
     if (move) {
		InvalidateRect(Form1->Handle, &ellipse_loc, false);
		ellipse_loc.Top = Y - 50;
		ellipse_loc.Left = X - 50;
		ellipse_loc.Bottom = Y + 50;
		ellipse_loc.Right = X + 50;
	}
}
//---------------------------------------------------------------------------

