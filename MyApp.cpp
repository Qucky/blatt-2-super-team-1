#include <wx/wxprec.h>


#include <iostream>

#include "C:\Users\flori_001\Source\Repos\blatt-2-super-team-1\include\word_table.hpp"
#include "C:\Users\flori_001\Source\Repos\blatt-2-super-team-1\include\words.hpp"
using namespace std;

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
	wxTextCtrl *text;
	MyFrame();
	Words w;
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void onButtonClick(wxCommandEvent& event);
};
enum
{
	ID_Hello = 1
};
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}


MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Hello World"), w("abc")
{
	wxGridSizer *gSizer = new wxGridSizer(0, 2, 0, 0);



	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	text = new wxTextCtrl(this, wxID_ANY, "Hi!", wxDefaultPosition, wxDefaultSize);
	gSizer->Add(text, 0, 5);

	
	wxButton *m_button = new wxButton(this, wxID_ANY, wxT("Read text"), wxDefaultPosition, wxDefaultSize, 0);
	gSizer->Add(m_button, 0, wxALL, 5);
	m_button->Bind(wxEVT_BUTTON, &MyFrame::onButtonClick, this);

	this->SetSizer(gSizer);
	this->Layout();

	this->Centre(wxBOTH);

}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	/*
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	for (Words::Iterator it = w.begin(); it != w.end(); ++it) {
		cout << *it << endl;
	}

	string output = to_string(w.size());

	wxLogMessage(wxFormatString(output));
	*/
	
	Words::entry_ptr entry_ptr = w.find("abc");
	int i = 7;
}

void MyFrame::onButtonClick(wxCommandEvent& event) {
	//Words words("abc\n");
	wxString wxStr = text->GetValue();
	string str = wxStr.ToStdString();
	str += "\n";
	
	Words words(str);
	for (Words::Iterator it = words.begin(); it != words.end(); ++it) {
		cout << *it << endl;
	}
	cout << "pause" << endl;

	wxLogMessage(wxFormatString(str));

}

