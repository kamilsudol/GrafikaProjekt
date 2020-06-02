///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  8 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/frame.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
public:
		wxScrolledWindow* m_scrolledWindow;
		wxScrolledWindow* histogram;
		wxScrolledWindow* histogram2;
		wxButton* m_b_grayscale;
		wxButton* m_b_blur;
		wxButton* m_b_mirror;

		wxButton* m_b_rescale;
		wxButton* m_b_rotate;

		wxSlider* m_s_brightness;
		wxChoice* m_choice;
		wxStaticText* m_staticText_font2;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_scrolledWindow_update( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_histogram_update( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_histogram2_update( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_b_grayscale_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_b_blur_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_b_mirror_click( wxCommandEvent& event ) { event.Skip(); }

		virtual void m_b_rescale_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_b_rotate_click( wxCommandEvent& event ) { event.Skip(); }

		virtual void m_s_brightness_scroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_b_choice_click( wxCommandEvent& event ) { event.Skip(); }
		
	
	
		wxStaticText* m_staticText1;
		
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Patryk Sledz Lab 06"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__GUI_H__
