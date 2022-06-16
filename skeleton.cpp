//************************************************************************
//************************************************************************
// skeleton.cpp
// created: february 2019
// How to:
// - use 2 panels (one for controls, one for drawings)
// - manage basic events (so that controls impact drawings)
// with wxWidgets (3.0.2) 
// Author: Pascal Bertolino, UGA - GIPSA-lab laboratory, Grenoble - France
// Email pascal.bertolino@gipsa-lab.fr
// Web http://www.gipsa-lab.inpg.fr/~pascal.bertolino/
//
// tested with xWidget 3.0.2 under Linux and Windows 10
// Under Linux, compile then link as follows (with g++):
// g++ -c `wx-config --cxxflags` skeleton.cpp
// g++ -o skeleton skeleton.o `wx-config --libs`
//************************************************************************
//************************************************************************
// this skeleton includes 4 classes that are all derived from wxWidgets classes:
// the application class:	MyApp
// the main frame class:	MyFrame
// the left panel class:	MyControlPanel
// the right panel class:	MyDrawingPanel
//************************************************************************
//************************************************************************

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include<wx/filedlg.h>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <bits/stdc++.h>
#include <string> 
#include <cstdlib>
#include <iostream>
#include <vector>
#include <wx/stattext.h>
#include <wx/statline.h>

#include "Point.h"
#include "Dessin.h"
#include "Forme.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cercle.h"
#include "Ligne.h"

//------------------------------------------------------------------------
// Some constants
//------------------------------------------------------------------------
#define APPLICATION_WIDTH		900
#define APPLICATION_HEIGHT		800 
#define WIDGET_PANEL_WIDTH		150
#define WIDGET_Y0				30
#define WIDGET_Y_STEP			70
#define WIDGET_Y_SPACE_BTN		40
#define WIDGET_Y_SPACE_SLINE	50
#define WIDGET_Y_SPACE_TITLE	15
#define APP_NAME "M1102 Skeleton 1.0"

using namespace std;

//------------------------------------------------------------------------
// Some enums for widgets
//------------------------------------------------------------------------
enum
{
	ID_QUIT = 1,
	ID_ABOUT,
	ID_LOAD,
	ID_SAVE,
	ID_BUTTON1,
	ID_BUTTON_LINE,
	ID_BUTTON_RECT,
	ID_BUTTON_CIRCLE,
	ID_BUTTON_TRIANGLE,
	ID_SLIDER_TRANSPARENCY,
	ID_SLIDER_RED,
	ID_SLIDER_BLUE,
	ID_SLIDER_GREEN,
	ID_COLOUR_PICKER,
	ID_CHECKBOX1
};

class MyFrame;

//------------------------------------------------------------------------
// CONTROLEUR
//------------------------------------------------------------------------
class MonControleur{
	
	public :

	//Constructeurs destructeurs
	MonControleur();
	~MonControleur();
	
	//Fonctions
	void ResetPts();
	void SetPts(int stepPt, int x, int y);
	void AddRectangle();
	void AddLigne();
	void AddCercle();
	void AddTriangle();
	MyFrame* GetFrame();
	void AfficheFormeSaved(wxClientDC& dc);

	//Etat des boutons
	int btnSelected = 0;

	//Etapes de creation d'une forme
	int stepShape = 0;

	//Slider Value
	int sliderTransparency = 0;

	int profondId = 1;

	//Points Temporaires Coordonées
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int x3 = 0;
	int y3 = 0;

	Dessin* dessin;
	
	private :
		MyFrame* frame;

};
//Definition de la variable globale controleur
  MonControleur *monControleur;

//------------------------------------------------------------------------
// The class declarations
//------------------------------------------------------------------------
class MyControlPanel ;

//------------------------------------------------------------------------
class MyApp: public wxApp
//------------------------------------------------------------------------
{
    virtual bool OnInit() ;
};

//------------------------------------------------------------------------
class MyDrawingPanel: public wxPanel
//------------------------------------------------------------------------
{
public:
	MyDrawingPanel( wxWindow *parent ) ;
	void OpenFile(wxString fileName) ;
	void SaveFile(wxString fileName) ;

private:
	void OnMouseMove(wxMouseEvent &event) ;
	void OnMouseLeftDown(wxMouseEvent &event) ;
	void OnPaint(wxPaintEvent &event) ;
	wxPoint m_mousePoint ;
	wxPoint m_onePoint ;
};

//------------------------------------------------------------------------
class MyControlPanel: public wxPanel
//------------------------------------------------------------------------
{
public:
	MyControlPanel( wxWindow *parent ) ;
	int GetSliderValue() {return m_slider->GetValue() ;} ;
	int GetSliderColorREDValue() {return m_slider_red->GetValue() ;} ;
	int GetSliderColorGREENValue() {return m_slider_green->GetValue() ;} ;
	int GetSliderColorBLUEValue() {return m_slider_blue->GetValue() ;} ;
	bool GetCheckBoxValue() {return m_checkBox->GetValue() ;} ;

private:
	void OnButton(wxCommandEvent &event) ;
	void OnSlider(wxScrollEvent &event) ;
	void OnCheckBox(wxCommandEvent &event) ;
	wxButton* m_button ;
	wxSlider* m_slider ;
	wxSlider* m_slider_red ;
	wxSlider* m_slider_green ;
	wxSlider* m_slider_blue ;
	wxCheckBox* m_checkBox ;
};

//------------------------------------------------------------------------
class MyFrame: public wxFrame
//------------------------------------------------------------------------
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	MyControlPanel* GetControlPanel(){return m_controlPanel ;} ;
	void RefreshDrawing(){m_drawingPanel->Refresh() ;} ;
	
	//Points temporaires
	wxPoint* m_PointTmp1;
	wxPoint* m_PointTmp2;
	wxPoint* m_PointTmp3;
	
	//Fonctions
	void ResetPts();
	void SetPts(int stepPt, int x, int y);
	int GetPts(int stepPt, bool isX);

protected:
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOpenFile(wxCommandEvent& WXUNUSED(event) ) ;
	void OnSaveFile(wxCommandEvent & WXUNUSED(event)) ;
	void OnClose(wxCloseEvent& event) ;
	void OnSize(wxSizeEvent &event) ;

	MyControlPanel *m_controlPanel; // the panel with controls
	MyDrawingPanel *m_drawingPanel; // the panel in which we draw

} ;

//************************************************************************
//************************************************************************
// MyDrawingPanel class (where controls are displayed)
//************************************************************************
//************************************************************************

//------------------------------------------------------------------------
MyControlPanel::MyControlPanel(wxWindow *parent) : wxPanel(parent)
//------------------------------------------------------------------------
// In this constructor, create the controls and associate each of them (bind) a method
{
	///PANEAU DE CONTROLE A GAUCHE///

	int w, h, y ;
	GetParent()->GetSize(&w,&h) ;
	SetSize(wxRect(wxPoint(0,0), wxPoint(WIDGET_PANEL_WIDTH, h))) ;
	SetBackgroundColour(*wxLIGHT_GREY) ;

	//Texte entete outils
	y = WIDGET_Y0 ;
	wxStaticText* textOutils = new wxStaticText(this, wxID_ANY, wxT("Outils"), wxPoint(10, y)) ;
	
	//Ajout d'un bouton (Pinceau)
	y += WIDGET_Y_SPACE_BTN ; //Emplacement dans le panneau en fonction de la verticalité
	m_button = new wxButton(this, ID_BUTTON_LINE, wxT("Ligne"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnButton, this, ID_BUTTON_LINE) ;
	
	//Ajout d'un bouton (Rectangle)
	y += WIDGET_Y_SPACE_BTN ; //Emplacement dans le panneau en fonction de la verticalité
	m_button = new wxButton(this, ID_BUTTON_RECT, wxT("Rectangle"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnButton, this, ID_BUTTON_RECT) ;
	
	//Ajout d'un bouton (Cercle)
	y += WIDGET_Y_SPACE_BTN ; //Emplacement dans le panneau en fonction de la verticalité
	m_button = new wxButton(this, ID_BUTTON_CIRCLE, wxT("Circle"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnButton, this, ID_BUTTON_CIRCLE) ;
	
	//Ajout d'un bouton (Triangle)
	y += WIDGET_Y_SPACE_BTN ; //Emplacement dans le panneau en fonction de la verticalité
	m_button = new wxButton(this, ID_BUTTON_TRIANGLE, wxT("Triangle"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnButton, this, ID_BUTTON_TRIANGLE) ;

	y+= WIDGET_Y_SPACE_SLINE ;
	wxStaticLine *sline1 = new wxStaticLine(this, wxID_ANY, wxPoint(20, y), wxSize(100,2));
	
	y+= WIDGET_Y_SPACE_TITLE ;
	wxStaticText* text1 = new wxStaticText(this, wxID_ANY, wxT("Opacity"), wxPoint(10, y)) ;
	
	y+= WIDGET_Y_SPACE_BTN ;
	m_slider = new wxSlider(this, ID_SLIDER_TRANSPARENCY, 10, 2, 255, wxPoint(10, y), wxSize(100,20), wxSL_LABELS) ;
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyControlPanel::OnSlider, this, ID_SLIDER_TRANSPARENCY) ;	

	y+= WIDGET_Y_SPACE_SLINE ;
	wxStaticLine *sline2 = new wxStaticLine(this, wxID_ANY, wxPoint(20, y), wxSize(100,2));
	
	y+= WIDGET_Y_SPACE_TITLE ;
	wxStaticText* textColor = new wxStaticText(this, wxID_ANY, wxT("Color"), wxPoint(10, y)) ;
	//wxClientDC dc(this);	
	//dc.SetBrush(wxColour(77,0,77,255));
    //wxRect* rect_color = new wxRect(wxPoint(70,y), wxPoint(80, y+10));

	y+= WIDGET_Y_SPACE_BTN ;
	m_slider_red = new wxSlider(this, ID_SLIDER_RED, 10, 2, 255, wxPoint(10, y), wxSize(100,20), wxSL_LABELS) ;
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyControlPanel::OnSlider, this, ID_SLIDER_RED) ;	

	y+= WIDGET_Y_SPACE_BTN ;
	m_slider_green = new wxSlider(this, ID_SLIDER_GREEN, 10, 2, 255, wxPoint(10, y), wxSize(100,20), wxSL_LABELS) ;
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyControlPanel::OnSlider, this, ID_SLIDER_GREEN) ;	

	y+= WIDGET_Y_SPACE_BTN ;
	m_slider_blue = new wxSlider(this, ID_SLIDER_BLUE, 10, 2, 255, wxPoint(10, y), wxSize(100,20), wxSL_LABELS) ;
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyControlPanel::OnSlider, this, ID_SLIDER_BLUE) ;
	//https://www.wxishiko.com/wxWidgetsTutorials/wxcolourpickerctrl.html
	
	y+= WIDGET_Y_SPACE_BTN ;
	wxStaticLine *sline3 = new wxStaticLine(this, wxID_ANY, wxPoint(20, y), wxSize(100,2));
	
	y+= WIDGET_Y_STEP ;
	m_checkBox = new wxCheckBox(this, ID_CHECKBOX1, "Show (x,y)", wxPoint(10, y), wxSize(100,20)) ;
	Bind(wxEVT_CHECKBOX, &MyControlPanel::OnCheckBox, this, ID_CHECKBOX1) ;	

	MyFrame* frame = (MyFrame*)GetParent() ;
	//int col_red = frame->GetControlPanel()->GetSliderColorREDValue() ;
	//int col_green = frame->GetControlPanel()->GetSliderColorGREENValue() ;
	//int col_blue = frame->GetControlPanel()->GetSliderColorBLUEValue() ;
	wxClientDC dc(this);
	dc.SetBrush(*wxBLACK);
	dc.DrawRectangle(wxPoint(10,10), wxSize(20,20));
	dc.SetBrush(wxColour(0,255,0,255));
	dc.DrawRectangle(wxPoint(12,12), wxSize(16,16));
}

//------------------------------------------------------------------------
void MyControlPanel::OnButton(wxCommandEvent &event)
//------------------------------------------------------------------------
{
//	char* s = GetCString() ;
//	wxMessageBox(wxString::FromAscii(s)) ; // call a C function located in the sample.cp module
//	free(s) ;

	//On recupère l'id du btn qui viens d'etre cliqué
	monControleur->btnSelected = event.GetId();

	//On affiche quel btn viens d'etre selectioné avec une pop up
	switch(monControleur->btnSelected){
		case ID_BUTTON_LINE :
			//A chaque nouveau ligne on definit son action
			wxMessageBox(wxT("Ligne activé")) ;
			break;
		case ID_BUTTON_RECT :
			//A chaque nouveau rectangle on definit son action
			wxMessageBox(wxT("Rectangle activé")) ;
			break;
		case ID_BUTTON_CIRCLE :
			//A chaque nouveau rectangle on definit son action
			wxMessageBox(wxT("Cercle activé")) ;
			break;
		case ID_BUTTON_TRIANGLE :
			//A chaque nouveau rectangle on definit son action
			wxMessageBox(wxT("Triangle activé")) ;
			break;
		default:
			wxMessageBox(wxT("Bouton inutilisé")) ;
			break;
	}

	//Suppression des formes entamés et non finies
	monControleur->stepShape = 0;
	monControleur->ResetPts();


	Refresh();


}

//------------------------------------------------------------------------
void MyControlPanel::OnSlider(wxScrollEvent &event)
//------------------------------------------------------------------------
{
	MyFrame* frame = (MyFrame*)GetParent() ;
	int col_red = frame->GetControlPanel()->GetSliderColorREDValue() ;
	int col_green = frame->GetControlPanel()->GetSliderColorGREENValue() ;
	int col_blue = frame->GetControlPanel()->GetSliderColorBLUEValue() ;
	wxClientDC dc(this);
	dc.SetBrush(*wxBLACK);
	dc.DrawRectangle(wxPoint(10,10), wxSize(20,20));
	dc.SetBrush(wxColour(col_red,col_green,col_blue,255));
	dc.DrawRectangle(wxPoint(12,12), wxSize(16,16));
	frame->RefreshDrawing() ;	// update the drawing panel
}


//------------------------------------------------------------------------
void MyControlPanel::OnCheckBox(wxCommandEvent &event)
//------------------------------------------------------------------------
{
	MyFrame* frame = (MyFrame*)GetParent() ;
	int col_red = frame->GetControlPanel()->GetSliderColorREDValue() ;
	int col_green = frame->GetControlPanel()->GetSliderColorGREENValue() ;
	int col_blue = frame->GetControlPanel()->GetSliderColorBLUEValue() ;
	wxClientDC dc(this);
	dc.SetBrush(*wxBLACK);
	dc.DrawRectangle(wxPoint(10,10), wxSize(20,20));
	dc.SetBrush(wxColour(col_red,col_green,col_blue,255));
	dc.DrawRectangle(wxPoint(12,12), wxSize(16,16));
	frame->RefreshDrawing() ;	// update the drawing panel
}

//************************************************************************
//************************************************************************
// MyDrawingPanel class (where drawings are displayed)
//************************************************************************
//************************************************************************

//------------------------------------------------------------------------
MyDrawingPanel::MyDrawingPanel(wxWindow *parent) : wxPanel(parent)
//------------------------------------------------------------------------
// In this constructor, bind some mouse events and the paint event with the appropriate methods
{
	int w, h ;
	GetParent()->GetClientSize(&w,&h) ;
	SetSize(wxRect(wxPoint(WIDGET_PANEL_WIDTH,0), wxPoint(w, h))) ;
	SetBackgroundColour(wxColour(0xFF,0xFF,0xFF)) ;
	Bind(wxEVT_MOTION, &MyDrawingPanel::OnMouseMove, this);
	Bind(wxEVT_LEFT_DOWN, &MyDrawingPanel::OnMouseLeftDown, this);
	Bind(wxEVT_PAINT, &MyDrawingPanel::OnPaint, this) ;
	m_onePoint.x = (w-WIDGET_PANEL_WIDTH)/2 ;
	m_onePoint.y = h/2 ;
	m_mousePoint = m_onePoint ;
}

//------------------------------------------------------------------------
void MyDrawingPanel::OnMouseMove(wxMouseEvent &event)
//------------------------------------------------------------------------
// called when the mouse is moved
{
	m_mousePoint.x = event.m_x ;
	m_mousePoint.y = event.m_y ;
	Refresh() ;	// send an event that calls the OnPaint method
}

//------------------------------------------------------------------------
void MyDrawingPanel::OnMouseLeftDown(wxMouseEvent &event)
//------------------------------------------------------------------------
// called when the mouse left button is pressed
{
	m_onePoint.x = event.m_x ;
	m_onePoint.y = event.m_y ;

	
	switch(monControleur->btnSelected){
		case ID_BUTTON_LINE :
			//A chaque nouvelle ligne on definit son action
			if(monControleur->stepShape == 0){
				monControleur->ResetPts();
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape++;
			}
			else{
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape = 0;
				monControleur->AddLigne();
			}
			break;
		case ID_BUTTON_RECT :
			//A chaque nouveau rectangle on definit son action
			if(monControleur->stepShape == 0){
				monControleur->ResetPts();
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape++;
			}
			else{
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape = 0;
				monControleur->AddRectangle();
			}
			break;
		case ID_BUTTON_CIRCLE :
			//A chaque nouveau cercle on definit son action
			if(monControleur->stepShape == 0){
				monControleur->ResetPts();
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape++;
			}
			else{
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				//CREATION
				monControleur->stepShape = 0;
				monControleur->AddCercle();
			}
			break;
		case ID_BUTTON_TRIANGLE :
			//A chaque nouveau cercle on definit son action
			if(monControleur->stepShape == 0){
				monControleur->ResetPts();
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape++;
			}
			else if(monControleur->stepShape == 1){
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				monControleur->stepShape++;
			}
			else{
				monControleur->SetPts(monControleur->stepShape, m_onePoint.x, m_onePoint.y);
				//CREATION
				monControleur->stepShape = 0;
				monControleur->AddTriangle();
			}
			break;
		default:
			break;
	}

	Refresh() ; // send an event that calls the OnPaint method
}

//------------------------------------------------------------------------
void MyDrawingPanel::OnPaint(wxPaintEvent &event)
//------------------------------------------------------------------------
// called automatically when the panel is shown for the first time or
// when the panel is resized
// You have to call OnPaint with Refresh() when you need to update the panel content
{
	// read the control values
	MyFrame* frame =  (MyFrame*)GetParent() ;
	int transparency = frame->GetControlPanel()->GetSliderValue() ;
	bool check = frame->GetControlPanel()->GetCheckBoxValue() ;
	
	int col_red = frame->GetControlPanel()->GetSliderColorREDValue() ;
	int col_green = frame->GetControlPanel()->GetSliderColorGREENValue() ;
	int col_blue = frame->GetControlPanel()->GetSliderColorBLUEValue() ;

	// then paint
	wxPaintDC dc(this);	

	///Affichage de toutes les formes crées///
	monControleur->AfficheFormeSaved(dc);

	///Affiche de la forme en cours de creation///
	dc.SetBrush(wxColour(col_red,col_green,col_blue,transparency));
		
	//LINE AFFICHE quand il a pas le deuxième pt définit
	if(monControleur->stepShape == 1 && (monControleur->btnSelected == ID_BUTTON_LINE || monControleur->btnSelected == ID_BUTTON_TRIANGLE)){dc.DrawLine(m_mousePoint, m_onePoint) ;}

	//TRIANGLE Affiche est quasiment similaire et est complete ligne
	if(monControleur->stepShape == 2 && monControleur->btnSelected == ID_BUTTON_TRIANGLE){
		dc.DrawLine(wxPoint(monControleur->GetFrame()->m_PointTmp1->x, monControleur->GetFrame()->m_PointTmp1->y), wxPoint(monControleur->GetFrame()->m_PointTmp2->x, monControleur->GetFrame()->m_PointTmp2->y));
		dc.DrawLine(m_mousePoint, m_onePoint) ;
	}
	
	//RECT AFFICHE quand il a pas le deuxième pt définit
	if(monControleur->stepShape == 1 && monControleur->btnSelected == ID_BUTTON_RECT){dc.DrawRectangle(wxPoint(monControleur->GetFrame()->m_PointTmp1->x, monControleur->GetFrame()->m_PointTmp1->y), wxSize(m_mousePoint.x-monControleur->GetFrame()->m_PointTmp1->x,m_mousePoint.y-monControleur->GetFrame()->m_PointTmp1->y)) ;}
	
	//CIRCLE AFFICHE quand il a pas le deuxième pt définit
	if(monControleur->stepShape == 1 && monControleur->btnSelected == ID_BUTTON_CIRCLE){dc.DrawCircle(wxPoint(*monControleur->GetFrame()->m_PointTmp1), sqrt(pow(m_mousePoint.x-monControleur->GetFrame()->m_PointTmp1->x, 2) + pow(m_mousePoint.y-monControleur->GetFrame()->m_PointTmp1->y, 2))) ;}
	
	///Affichage du curseur///
	dc.SetBrush(*wxWHITE);
	//dc.SetPen(*wxRED);
	dc.DrawCircle(wxPoint(m_mousePoint),5);

	if (check)

	{
		wxString coordinates ;
		coordinates.sprintf(wxT("(%d,%d)"), m_mousePoint.x, m_mousePoint.y) ;
		dc.DrawText(coordinates, wxPoint(m_mousePoint.x, m_mousePoint.y+20)) ;
	}
}

//------------------------------------------------------------------------
void MyDrawingPanel::OpenFile(wxString fileName)
//------------------------------------------------------------------------
{
	// just to open (and close) any file 
	FILE* f = fopen(fileName, "r") ;
   	char s[81];
	if (f)
	{
		/*Abandon temporaire
		//On boucle sur tout le dossier
		while(!feof(f))
        {
			int cx;
			fscanf( f, "cx=\"%d\"", &cx);
			printf("%i",test);
			fflush(stdout);
			//exit(0);


			//fgets(s,10,f);
			if(strcmp(s,"width") == 0){
				printf( "%s\n", "YEAY" );
			}
			printf( "%s\n", s );
			//printf( "%s\n", s[0-5] );
        }*/

		wxMessageBox(wxT("The file was opened then closed")) ;
		fclose(f) ;
	}
}

//------------------------------------------------------------------------
void MyDrawingPanel::SaveFile(wxString fileName)
//------------------------------------------------------------------------
{
	//TMP 
	//MyApp* myApp = wxApp();

	// just to create a tiny file
	FILE* f = fopen(fileName, "w") ;
	if (!f)
		wxMessageBox(wxT("Cannot save file"));
	else
	{
		//La string qui va acceuillir toutes nos balises
		stringstream ss;

		//Entete du fichier
		ss << "<svg width=\""<< monControleur->GetFrame()->m_width << "\" height=\"" << "\">" ;

		//On remplie avec les formes
		//ss << "<rect width=\"100%\" height=\"100%\" fill=\"red\" />";
		//RAJOUT DE METHODE TOSTRING POUR CHAQUE FORME

		//Fin du svg
		ss << "</svg>";

		//On passe le tout dans le bon format
		string str = ss.str();
		char const *pchar = str.c_str();  //use char const* as target type

		//On ecrit dans le fichier
		fprintf(f, pchar) ;
		wxMessageBox(wxT("The file was saved")) ;
		fclose(f) ;
	}
}

//************************************************************************
//************************************************************************
// Frame class (the main window)
//************************************************************************
//************************************************************************

//------------------------------------------------------------------------
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
//------------------------------------------------------------------------
// The constructor of the main frame that creates the menu stuffs and the 2 panels
{
	wxMenu *fileMenu = new wxMenu();
	fileMenu->Append(ID_LOAD, wxT("&Open file..."));
	fileMenu->Append(ID_SAVE, wxT("&Save file..."));
	fileMenu->Append(ID_ABOUT, wxT("&About..."));
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_QUIT, wxT("&Exit"));

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("&File"));

	Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, ID_LOAD);
	Bind(wxEVT_MENU, &MyFrame::OnSaveFile, this, ID_SAVE);
	Bind(wxEVT_MENU, &MyFrame::OnQuit, this, ID_QUIT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_ABOUT);
	Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
	Bind(wxEVT_SIZE, &MyFrame::OnSize, this);

	SetMenuBar( menuBar );

// create the panel that will contain the controls
	m_controlPanel = new MyControlPanel(this);
// create the panel that will display the graphics
	m_drawingPanel = new MyDrawingPanel(this);
	CreateStatusBar() ;
	SetStatusText(wxT("click in the right panel and tune the controls of the left panel. Visit the File menu!")) ;
	Centre() ; // Guess what it does ;-)
}

//------------------------------------------------------------------------
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
//------------------------------------------------------------------------
{
	Close(true) ;
}

//------------------------------------------------------------------------
void MyFrame::OnClose(wxCloseEvent& event)
//------------------------------------------------------------------------
{
	delete m_controlPanel ;
	delete m_drawingPanel ;
	event.Skip() ;
}

//------------------------------------------------------------------------
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
//------------------------------------------------------------------------
{
	wxMessageBox(wxT("How to .. \n\n- use 2 panels (one for controls, one for drawings)\n- manage basic events (so that controls impact drawings)\n\n... with wxWidgets (3.0.2)\n\nPascal Bertolino UGA - GIPSA-lab, Grenoble - France\npascal.bertolino@gipsa-lab.fr"),
                  wxT(APP_NAME), wxOK | wxICON_INFORMATION ) ;
}

//------------------------------------------------------------------------
void MyFrame::OnOpenFile(wxCommandEvent& WXUNUSED(event) )
//------------------------------------------------------------------------
{
	wxString filename = wxFileSelector(wxT("Select file"));
	if ( !filename.empty() )
		m_drawingPanel->OpenFile(filename) ;
}

//------------------------------------------------------------------------
void MyFrame::OnSaveFile(wxCommandEvent & WXUNUSED(event))
//------------------------------------------------------------------------
{
	wxString filename = wxSaveFileSelector(wxT("Save file as"), wxT("*.txt"), wxT("data"));
	if ( !filename.empty() )
		m_drawingPanel->SaveFile(filename) ;
}

//------------------------------------------------------------------------
void MyFrame::OnSize(wxSizeEvent &event)
//------------------------------------------------------------------------
// Called when you resize the frame
{
	int w, h ;
	GetSize(&w,&h) ;	
	m_controlPanel->SetSize(wxRect(wxPoint(0,0), wxPoint(WIDGET_PANEL_WIDTH, h))) ;
	m_drawingPanel->SetSize(wxRect(wxPoint(WIDGET_PANEL_WIDTH,0), wxPoint(w, h))) ;
}

//------------------------------------------------------------------------
void MyFrame::ResetPts()
//------------------------------------------------------------------------
{
	m_PointTmp1 = nullptr;
	m_PointTmp2 = nullptr;
	m_PointTmp3 = nullptr;
}

//------------------------------------------------------------------------
void MyFrame::SetPts(int stepPt, int x, int y)
//------------------------------------------------------------------------
{
	switch(stepPt){
		case 0:
			m_PointTmp1 = new wxPoint();
			m_PointTmp1->x = x;
			m_PointTmp1->y = y;
			break;
		case 1:
			m_PointTmp2 = new wxPoint();
			m_PointTmp2->x = x;
			m_PointTmp2->y = y;
			break;
		case 2:
			m_PointTmp3 = new wxPoint();
			m_PointTmp3->x = x;
			m_PointTmp3->y = y;
			break;
		default:
			break;
	}
}

//------------------------------------------------------------------------
int MyFrame::GetPts(int stepPt, bool isX)
//------------------------------------------------------------------------
{
	switch(stepPt){
		case 0:
			if(isX){
				return m_PointTmp1->x;
			}
			else{
				return m_PointTmp1->y;
			}
			break;
		case 1:
			if(isX){
				return m_PointTmp2->x;
			}
			else{
				return m_PointTmp2->y;
			}
			break;
		case 2:
			if(isX){
				return m_PointTmp3->x;
			}
			else{
				return m_PointTmp3->y;
			}
			break;
		default:
			break;
	}
}

//************************************************************************
//************************************************************************
// Application class
//************************************************************************
//************************************************************************

IMPLEMENT_APP(MyApp) // macro that contains the main() function

//------------------------------------------------------------------------
bool MyApp::OnInit()
//------------------------------------------------------------------------
{
	monControleur = new MonControleur();
	SetTopWindow(monControleur->GetFrame()) ;
	return true ;
}

//////////////////////////////////////////////////////////////////////////////

MonControleur::MonControleur(){
	frame = new MyFrame(wxT(APP_NAME), wxDefaultPosition, wxSize(APPLICATION_WIDTH,APPLICATION_HEIGHT)) ;
	frame->Show(true) ;
	dessin = new Dessin();
}

MonControleur::~MonControleur(){
	frame = nullptr;
}

void MonControleur::ResetPts(){
	frame->ResetPts();
} 

void MonControleur::SetPts(int stepPt, int x, int y){
	switch(stepPt){
		case 0:
			x1 = x;
			y1 = y;
			break;
		case 1:
			x2 = x;
			y2 = y;
			break;
		case 2:
			x3 = x;
			y3 = y;
			break;
		default:
			break;
	}
	frame->SetPts(stepPt, x, y);
} 

void MonControleur::AddRectangle(){
	const Point* p1 = new Point(frame->GetPts(0, true), frame->GetPts(0, false));
	dessin->addVector(new Rectangle (*p1, frame->GetPts(1, true)-frame->GetPts(0, true), frame->GetPts(1, false)-frame->GetPts(0, false), profondId, "Rectangle"));
	profondId++;
}

void MonControleur::AddLigne(){
	const Point* p1 = new Point(frame->GetPts(0, true), frame->GetPts(0, false));
	const Point* p2 = new Point(frame->GetPts(1, true), frame->GetPts(1, false));
	dessin->addVector(new Ligne (*p1, *p2, profondId, "Ligne"));
	profondId++;
}

void MonControleur::AddCercle(){
	const Point* p1 = new Point(frame->GetPts(0, true), frame->GetPts(0, false));
	const Point* p2 = new Point(frame->GetPts(1, true), frame->GetPts(1, false));
	dessin->addVector(new Cercle (*p1, sqrt(pow(monControleur->GetFrame()->m_PointTmp2->x-monControleur->GetFrame()->m_PointTmp1->x, 2) + pow(monControleur->GetFrame()->m_PointTmp2->y-monControleur->GetFrame()->m_PointTmp1->y, 2)), profondId, "Cercle"));
	profondId++;
}

void MonControleur::AddTriangle(){
	const Point* p1 = new Point(frame->GetPts(0, true), frame->GetPts(0, false));
	const Point* p2 = new Point(frame->GetPts(1, true), frame->GetPts(1, false));
	const Point* p3 = new Point(frame->GetPts(2, true), frame->GetPts(2, false));
	dessin->addVector(new Triangle(*p1, *p2, *p3, profondId, "Triangle"));
	profondId++;
}

MyFrame* MonControleur::GetFrame(){
	return frame;
} 

void MonControleur::AfficheFormeSaved(wxClientDC& dc){
	for(Forme* forme : dessin->getVector()){
		forme->draw(dc);
	}
}

//////////////////////////////////////////////////////////////////////////////