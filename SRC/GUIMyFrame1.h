#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

#include "GUI.h"

#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/log.h> 

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/opencv.hpp>

class GUIMyFrame1 : public MyFrame1
{
	protected:
		void m_Window_update( wxUpdateUIEvent& event );
		void conversion_8bit_click( wxCommandEvent& event );
		void conversion_with_gamma_click( wxCommandEvent& event );
		void open_file_click( wxCommandEvent& event );
		void save_file_click( wxCommandEvent& event );
		void gamma_correction_scroll( wxScrollEvent& event );
		void m_b_choice_click(wxCommandEvent& event);
		void m_histogram_update(wxUpdateUIEvent& event);
		void m_histogram2_update(wxUpdateUIEvent& event);
	public:
		GUIMyFrame1( wxWindow* parent );

  void Repaint();
  cv::Mat &correctGamma(cv::Mat& img, double gamma);
  wxImage getImage(cv::Mat &img);
  void histogram_fun(wxScrolledWindow *window, wxImage &img);
 
  wxBitmap pBitmap;
  wxImage Img_tmp, Org;

  cv::Mat image_org, result;
};

#endif
