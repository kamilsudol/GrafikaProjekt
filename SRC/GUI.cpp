#include "GUI.h"

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800, 540 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_Window = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	bSizer1->Add( m_Window, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );
	
	open_file = new wxButton( this, wxID_ANY, _("Wczytaj plik"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( open_file, 0, wxALL, 5 );
	
	save_file = new wxButton( this, wxID_ANY, _("Zapisz plik"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( save_file, 0, wxALL, 5 );
	
	conversion_8bit = new wxButton(this, wxID_ANY, _("Konwersja na 8bit"), wxDefaultPosition, wxDefaultSize, 0);
	gSizer1->Add(conversion_8bit, 0, wxALL, 5);

	conversion_with_gamma = new wxButton(this, wxID_ANY, _("Konwersja z korekcj\u0105"), wxDefaultPosition, wxDefaultSize, 0);
	gSizer1->Add(conversion_with_gamma, 0, wxALL, 5);
	
	bSizer2->Add( gSizer1, 1, wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Korekcja gamma"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALIGN_CENTER|wxALL, 5 );

	slid_size = 5000;
	gamma_correction_slider = new wxSlider( this, wxID_ANY, slid_size/2 , 0, slid_size, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gamma_correction_slider->Disable();
	bSizer2->Add( gamma_correction_slider, 0, wxEXPAND, 5 );
	
	m_staticText_font2 = new wxStaticText(this, wxID_ANY, wxT("Zakres bit\u00F3w do przeniesienia:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_font2->Wrap(-1);
	bSizer2->Add(m_staticText_font2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxString m_choiceChoices[] = { wxT("-"), wxT("0 - 8"), wxT("1 - 9"), wxT("2 - 10"), wxT("3 - 11"), wxT("4 - 12"), wxT("5 - 13"), wxT("6 - 14"), wxT("7 - 15"), wxT("8 - 16") };
	int m_choiceNChoices = sizeof(m_choiceChoices) / sizeof(wxString);
	m_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNChoices, m_choiceChoices, 0);
	m_choice->SetSelection(0);
	bSizer2->Add(m_choice, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Histogram jasno\u015Bci dla obrazu 16-bitowego:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer2->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	histogram = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(256,100), wxHSCROLL | wxVSCROLL);
	bSizer2->Add(histogram, 1, wxEXPAND | wxALL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("Histogram jasno\u015Bci dla obrazu 8-bitowego:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer2->Add(m_staticText3, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	histogram2 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(256, 100), wxHSCROLL | wxVSCROLL);
	bSizer2->Add(histogram2, 1, wxEXPAND | wxALL, 5);
	
	
	bSizer1->Add( bSizer2, 0, wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	m_Window->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::m_Window_update ), NULL, this );
	conversion_8bit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::conversion_8bit_click ), NULL, this );
	conversion_with_gamma->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::conversion_with_gamma_click ), NULL, this );
	open_file->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::open_file_click ), NULL, this );
	save_file->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::save_file_click ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	m_choice->Bind(wxEVT_CHOICE, &MyFrame1::m_b_choice_click, this);
	histogram->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram_update), NULL, this);
	histogram2->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram2_update), NULL, this);
}

MyFrame1::~MyFrame1()
{
	m_Window->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::m_Window_update ), NULL, this );
	conversion_8bit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::conversion_8bit_click ), NULL, this );
	conversion_with_gamma->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::conversion_with_gamma_click ), NULL, this );
	open_file->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::open_file_click ), NULL, this );
	save_file->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::save_file_click ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	gamma_correction_slider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::gamma_correction_scroll ), NULL, this );
	m_choice->Unbind(wxEVT_CHOICE, &MyFrame1::m_b_choice_click, this);
	histogram->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram_update), NULL, this);
	histogram2->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_histogram2_update), NULL, this);
	
}
