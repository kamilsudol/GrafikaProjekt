#include "GUIMyFrame1.h"
#pragma omp parallel

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
	 this->SetBackgroundColour(wxColor(192, 192, 192));

	 m_Window->SetBackgroundColour(wxColor(192, 192, 192));

	 histogram->SetBackgroundColour(wxColor(255, 255, 255));
	 histogram2->SetBackgroundColour(wxColor(255, 255, 255));

	 Img_tmp = wxImage();
}

void GUIMyFrame1::m_Window_update( wxUpdateUIEvent& event )
{
	Repaint();
}

void GUIMyFrame1::m_histogram_update(wxUpdateUIEvent& event) 
{
	Repaint();
}

void GUIMyFrame1::m_histogram2_update(wxUpdateUIEvent& event) 
{
	Repaint();
}

void GUIMyFrame1::Repaint()
{
	wxClientDC dc(m_Window);
	pBitmap = wxBitmap(Img_tmp);
	dc.DrawBitmap(pBitmap, 0, 0, false);
}

wxImage GUIMyFrame1::getImage(cv::Mat &result) 
{
	int w = result.cols;
	int h = result.rows;
	int size = w * h * 3 * sizeof(unsigned char);

	unsigned char* data = new unsigned char[size];

	cv::Mat cv2wx = cv::Mat(h, w, CV_8UC3, data);
	switch (result.channels())
	{
		case 3:
		{
			int mapping[] = { 0,2,1,1,2,0 };
			cv::mixChannels(&result, 1, &cv2wx, 1, mapping, 3);
		} break;
	}

	return wxImage(w, h, data);
}

void GUIMyFrame1::open_file_click(wxCommandEvent& event)
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("TIFF file (*.tiff;*.tif)|*.tiff;*.tif"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		image_org = cv::imread(static_cast<std::string>(WxOpenFileDialog.GetPath()), CV_LOAD_IMAGE_COLOR);
		if (!image_org.data)
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		}
		else
		{
			gamma_correction_slider->Disable();
			gamma_correction_slider->SetValue(slid_size / 2.);
			result = image_org.clone();
			Img_tmp = getImage(result);
			wxRect screen = m_Window->GetSize();
			Img_tmp.Rescale(screen.GetWidth(), screen.GetHeight());
			histogram_fun(histogram, Img_tmp);
			histogram2->ClearBackground();
			Repaint();
		}
	}

}

void GUIMyFrame1::save_file_click(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save converted TIFF file"), "", "", "TIFF files (*.tiff)|*.tiff", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_OK) {
		std::string save_path = static_cast<std::string>(saveFileDialog.GetFilename());

		if (result.data)
		{
			cv::imwrite(save_path, result);
			wxMessageBox(_("Pomy\u015Blnie zapisano plik."));
		}
		else 
		{
			wxMessageBox(_("Brak pliku do zapisania!"));
		}
	}
}

void GUIMyFrame1::conversion_8bit_click( wxCommandEvent& event )
{
	Img_tmp = getImage(image_org);
	histogram_fun(histogram, Img_tmp);
	gamma_correction_slider->Disable();
	gamma_correction_slider->SetValue(slid_size/2.);
	if (result.data) 
	{
		histogram_fun(histogram, Img_tmp);
		result = image_org.clone();
		result.convertTo(result, CV_8UC3);
		Img_tmp = getImage(result);
		wxRect screen = m_Window->GetSize();
		Img_tmp.Rescale(screen.GetWidth(), screen.GetHeight());
		histogram_fun(histogram2, Img_tmp);
		Repaint();
	}
	else 
	{
		wxMessageBox(_("Prosz\u0119 wczyta\u0107 plik!"));
	}
}

void GUIMyFrame1::conversion_with_gamma_click(wxCommandEvent& event) 
{
	if (result.data) 
	{
		gamma_correction_slider->Enable();
		result = image_org.clone();
		Img_tmp = getImage(result);
		wxRect screen = m_Window->GetSize();
		Img_tmp.Rescale(screen.GetWidth(), screen.GetHeight());
		histogram_fun(histogram, Img_tmp);
		histogram2->ClearBackground();
		histogram_fun(histogram2, Img_tmp);
		Repaint();
	}
	else 
	{
		wxMessageBox(_("Prosz\u0119 wczyta\u0107 plik!"));
	}
}

void GUIMyFrame1::gamma_correction_scroll(wxScrollEvent& event)
{
	result = image_org.clone();

	int val = gamma_correction_slider->GetValue();

	if (val == slid_size / 2) 
	{
		result = correctGamma(image_org, 1.);
	}
	else if (val > slid_size / 2) 
	{
		result = correctGamma(image_org, (gamma_correction_slider->GetMax() - val) / (slid_size / 2.));
	}
	else 
	{
		result = correctGamma(image_org, pow((gamma_correction_slider->GetMax() / 2. - val) / (slid_size / 10.) + 1., 2));
	}

	result.convertTo(result, CV_8UC3);
	Org = wxImage(image_org.cols, image_org.rows, image_org.data, TRUE);
	histogram_fun(histogram, Org);
	Img_tmp = getImage(result);
	wxRect screen = m_Window->GetSize();
	Img_tmp.Rescale(screen.GetWidth(), screen.GetHeight());
	histogram_fun(histogram2, Img_tmp);
	Repaint();
}

cv::Mat &GUIMyFrame1::correctGamma(cv::Mat& img, double gamma) 
{
	cv::Mat lut_data(1, 256, CV_8UC1);
	uchar * data = lut_data.ptr();
	for (int i = 0; i < 256; i++) 
	{
		data[i] = static_cast<int>((pow(static_cast<double>(i) / 255.0, 1. / gamma) * 255.0));
	}

	cv::Mat *result = new cv::Mat;
	cv::LUT(img, lut_data, *result);

	return *result;
}

void GUIMyFrame1::m_b_choice_click(wxCommandEvent& event) 
{
	Img_tmp = getImage(image_org);
	histogram_fun(histogram, Img_tmp);
	gamma_correction_slider->Disable();
	gamma_correction_slider->SetValue(slid_size / 2.);
	if (result.data) 
	{
		result = image_org.clone();
		unsigned char* dataMat = result.data;
		int size = result.cols*result.rows * 3;

		if (m_choice->GetSelection()) 
		{
			if (m_choice->GetSelection() == 1)
			{
				for (int i = 0; i < size; i++)
				{
					if (dataMat[i] < pow(2, m_choice->GetSelection() - 1))
					{
						dataMat[i] = pow(2, m_choice->GetSelection() - 1) - 1;
					}
					else if (dataMat[i] > pow(2, m_choice->GetSelection() + 7) - 1)
					{
						dataMat[i] = pow(2, m_choice->GetSelection() + 7) - 1;
					}
				}
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					if (dataMat[i] < pow(2, m_choice->GetSelection() - 1))
					{
						dataMat[i] = pow(2, m_choice->GetSelection() - 1);
					}
					else if (dataMat[i] > pow(2, m_choice->GetSelection() + 7) - 1)
					{
						dataMat[i] = pow(2, m_choice->GetSelection() + 7) - 1;
					}
				}
			}
		}

		Img_tmp = getImage(result);

		wxRect screen = m_Window->GetSize();
		Img_tmp.Rescale(screen.GetWidth(), screen.GetHeight());
		histogram_fun(histogram2, Img_tmp);

		Repaint();
	}
	else 
	{
		wxMessageBox(_("Prosz\u0119 wczyta\u0107 plik!"));
	}
}

void GUIMyFrame1::histogram_fun(wxScrolledWindow* histogram, wxImage& Img) 
{
	int w = Img.GetWidth(), h = Img.GetHeight(), rgb_tab[256], r, g, b, max = 0;

	const int size = 100 * 256 * 3;
	unsigned char hist_data[size];

	for (int i = 0; i < 256; i++) 
	{
		rgb_tab[i] = 0;
	}

	for (int i = 0; i < size; i++)
	{
		hist_data[i] = 255;
	}

	unsigned char *data = Img.GetData();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = data[3 * (i * w + j)];
			g = data[3 * (i * w + j) + 1];
			b = data[3 * (i * w + j) + 2];
			rgb_tab[(r + g + b) / 3]++;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		if (rgb_tab[i] > max)
		{
			max = rgb_tab[i];
		}
	}

	for (int i = 0; i < 256; i++)
	{
		rgb_tab[i] = (100 * rgb_tab[i]) / max;
	}

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < rgb_tab[i]; j++)
		{
			hist_data[3 * ((99 - j) * 256 + i)] = 0;
			hist_data[3 * ((99 - j) * 256 + i) + 1] = 0;
			hist_data[3 * ((99 - j) * 256 + i) + 2] = 0;
		}
	}

	wxClientDC dc(histogram);
	dc.DrawBitmap(wxBitmap(wxImage(256, 100, hist_data, true)), 0, 0, true);
}
