///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  8 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800, 540 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 5, 5 );
	bSizer1->Add( m_scrolledWindow, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_b_grayscale = new wxButton( this, wxID_ANY, _("Konwersja na 8bit"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_b_grayscale, 0, wxALL, 5 );
	
	m_b_blur = new wxButton( this, wxID_ANY, _("Histogramy"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_b_blur, 0, wxALL, 5 );
	
	m_b_mirror = new wxButton( this, wxID_ANY, _("Oryginal"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_b_mirror, 0, wxALL, 5 );
	
	
	m_b_rescale = new wxButton( this, wxID_ANY, _("Wczytaj plik"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_b_rescale, 0, wxALL, 5 );
	
	m_b_rotate = new wxButton( this, wxID_ANY, _("Zapisz plik"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_b_rotate, 0, wxALL, 5 );
	
	
	
	bSizer2->Add( gSizer1, 1, wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Korekcja gamma"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_s_brightness = new wxSlider( this, wxID_ANY, 100, 0, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer2->Add( m_s_brightness, 0, wxEXPAND, 5 );
	

	m_staticText_font2 = new wxStaticText(this, wxID_ANY, wxT("Zakres bitow do przeniesienia:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_font2->Wrap(-1);
	bSizer2->Add(m_staticText_font2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxString m_choiceChoices[] = { wxT("-"), wxT("1 - 8"), wxT("2 - 9"), wxT("3 - 10"), wxT("4 - 11"), wxT("5 - 12"), wxT("6 - 13"), wxT("7 - 14"), wxT("8 - 15"), wxT("9 - 16") };
	int m_choiceNChoices = sizeof(m_choiceChoices) / sizeof(wxString);
	m_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNChoices, m_choiceChoices, 0);
	m_choice->SetSelection(0);
	bSizer2->Add(m_choice, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Histogram dla obrazu 16-bitowego:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer2->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	histogram = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(256,100), wxHSCROLL | wxVSCROLL);
	histogram->SetScrollRate(5, 5);
	bSizer2->Add(histogram, 1, wxEXPAND | wxALL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("Histogram dla obrazu 8-bitowego:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer2->Add(m_staticText3, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	histogram2 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(256, 100), wxHSCROLL | wxVSCROLL);
	histogram2->SetScrollRate(5, 5);
	bSizer2->Add(histogram2, 1, wxEXPAND | wxALL, 5);
	
	
	bSizer1->Add( bSizer2, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_scrolledWindow->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::m_scrolledWindow_update ), NULL, this );
	m_b_grayscale->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_grayscale_click ), NULL, this );
	m_b_blur->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_blur_click ), NULL, this );
	m_b_mirror->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_mirror_click ), NULL, this );
	
	m_b_rescale->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_rescale_click ), NULL, this );
	m_b_rotate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_rotate_click ), NULL, this );

	m_s_brightness->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_choice->Bind(wxEVT_CHOICE, &MyFrame1::m_b_choice_click, this);
	histogram->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram_update), NULL, this);
	histogram2->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram2_update), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_scrolledWindow->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::m_scrolledWindow_update ), NULL, this );
	m_b_grayscale->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_grayscale_click ), NULL, this );
	m_b_blur->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_blur_click ), NULL, this );
	m_b_mirror->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_mirror_click ), NULL, this );
	
	m_b_rescale->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_rescale_click ), NULL, this );
	m_b_rotate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_b_rotate_click ), NULL, this );

	m_s_brightness->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	m_s_brightness->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_s_brightness_scroll ), NULL, this );
	histogram->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram_update), NULL, this);
	histogram2->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram2_update), NULL, this);
	
}
