#include <wx/wx.h>
#include "GUIMyFrame1.h"

/*
	Grafika, Projekt 042

	Autorzy:

		Patryk ŒledŸ
		Kamil Sudo³
		Jakub Struga³a

*/

class MyApp : public wxApp {

public:

	 virtual bool OnInit();
	 virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() 
{
	 GUIMyFrame1 *mainFrame = new GUIMyFrame1(NULL);
	 wxImage::AddHandler(new wxTIFFHandler);

	 mainFrame->Show(true);
	 SetTopWindow(mainFrame);

	 return true;
}