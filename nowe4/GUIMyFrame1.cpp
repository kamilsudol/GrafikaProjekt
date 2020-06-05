#include "GUIMyFrame1.h"
#pragma omp parallel
#include <stdlib.h>

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Korekcja gamma"));
 this->SetBackgroundColour(wxColor(192, 192, 192));

 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));

 histogram->SetBackgroundColour(wxColor(255, 255, 255));
 histogram2->SetBackgroundColour(wxColor(255, 255, 255));

 pWxImg = wxImage();
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
	 Repaint();
}

void GUIMyFrame1::m_histogram_update(wxUpdateUIEvent& event) {
	Repaint();
}

void GUIMyFrame1::m_histogram2_update(wxUpdateUIEvent& event) {
	Repaint();
}

void GUIMyFrame1::conversion_8bit_click( wxCommandEvent& event )
{	
	if (result.data) {
		result = image.clone();
		result.convertTo(result, CV_8UC1);
		pWxImg = getImage(result);
		wxRect screen = m_scrolledWindow->GetSize();
		pWxImg.Rescale(screen.GetWidth(), screen.GetHeight());
		histogram_fun(histogram2, pWxImg);
		Repaint();
	}
	else {
		wxMessageBox(_("Prosze wczytac plik!"));
	}
}

void GUIMyFrame1::updateHistogram(void) {
	int rgb_count_n[256] = { 0 };

	calculateHistograms(Img_Org, rgb_count_n);
	generate_hist_img(imgHistogramRGB_n, bitMapHistogramRGB_n, rgb_count_n, 0x00, 0x00, 0x00);
	Repaint();
	return;
}

void GUIMyFrame1::calculateHistograms(wxImage &img, int rgb_count[256]) {
	unsigned char *pixels = img.GetData();
	int w = img.GetWidth();
	int h = img.GetHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int r = pixels[3 * (y*w + x)];
			int g = pixels[3 * (y*w + x) + 1];
			int b = pixels[3 * (y*w + x) + 2];
			rgb_count[(r + g + b) / 3]++;
		}
	}
}

void GUIMyFrame1::generate_hist_img(wxImage &img, wxBitmap &bitmap, int count[256], int r, int g, int b) {
	int hist_max = 1;
	for (int i = 0; i < 256; i++) {
		if (count[i] > hist_max) {
			hist_max = count[i];
		}
	}
	for (int i = 0; i < 256; i++) {
		count[i] = (100 * count[i]) / hist_max;
	}
	unsigned char hist_pixels[100 * 256 * 3];
	for (int i = 0; i < 100 * 256 * 3; i++) {
		hist_pixels[i] = 0xff;
	}
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < count[x]; y++) {
			hist_pixels[3 * ((99 - y) * 256 + x)] = r;
			hist_pixels[3 * ((99 - y) * 256 + x) + 1] = g;
			hist_pixels[3 * ((99 - y) * 256 + x) + 2] = b;
		}
	}
	img = wxImage(256, 100, hist_pixels, true);
	bitmap = wxBitmap(img);
}


void GUIMyFrame1::open_file_click( wxCommandEvent& event )
{	
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("TIFF file (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK) {
		image = cv::imread(static_cast<std::string>(WxOpenFileDialog.GetPath()), CV_LOAD_IMAGE_COLOR);
		if (!image.data) {
			wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		}
		else {
			result = image.clone();
			pWxImg = getImage(result);
			wxRect screen = m_scrolledWindow->GetSize();
			pWxImg.Rescale(screen.GetWidth(), screen.GetHeight());
			histogram_fun(histogram, pWxImg);
			histogram2->ClearBackground();
			Repaint();
		}
	}

}

void GUIMyFrame1::save_file_click( wxCommandEvent& event )
{
	//wxFileDialog saveFileDialog(this, _("Save converted TIFF file"), "", "", "TIFF files (*.tiff)|*.tiff", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	//std::string save_path = static_cast<std::string>(saveFileDialog.GetFilename());
	//cv::imwrite(static_cast<std::string>(saveFileDialog.GetPath()), result);
	//cv::imwrite("C:\Users\gruby\source\repos\GrafikaPatryk\GrafikaPatryk\masnoni.tiff", result);
	//if (saveFileDialog.ShowModal() == wxID_OK) {
		//cv::imwrite(save_path, result);
	//}
	if (result.data) {
		cv::imwrite("converted.tiff", result);
		wxMessageBox(_("Pomyslnie zapisano plik."));
	}
	else {
		wxMessageBox(_("Brak pliku do zapisania!"));
	}
	
}

wxImage GUIMyFrame1::getImage(cv::Mat &result) { 
	int w = result.cols;
	int h = result.rows;
	int size = w * h * 3 * sizeof(unsigned char);

	// allocate memory for internal wxImage data
	unsigned char* wxData = new unsigned char[size];

	// the matrix stores BGR image for conversion
	cv::Mat cvRGBImg = cv::Mat(h, w, CV_8UC3, wxData);
	switch (result.channels())
	{
	case 3: // 3-channel case: swap R&B channels
	{
		int mapping[] = { 0,2,1,1,2,0 }; // CV(BGR) to WX(RGB)
		mixChannels(&result, 1, &cvRGBImg, 1, mapping, 3);
	} break;
	}

	return wxImage(w, h, wxData);
}


void GUIMyFrame1::gamma_correction_scroll( wxScrollEvent& event )
{
	if (result.data) {
		result = image.clone();
		result = correctGamma(image, (gamma_correction_slider->GetMax() - gamma_correction_slider->GetValue()) / 1000.); //poprawie to na casey, zeby ladnie odwzorowywac te skurwione gammy

		result.convertTo(result, CV_8UC1);

		pWxImg = getImage(result);
		wxRect screen = m_scrolledWindow->GetSize();
		pWxImg.Rescale(screen.GetWidth(), screen.GetHeight());
		histogram_fun(histogram, wxImage(image.cols, image.rows, image.data, TRUE));
		histogram_fun(histogram2, pWxImg);
		Repaint();
	}
	else {
		wxMessageBox(_("Prosze wczytac plik!"));
	}
}

void GUIMyFrame1::Repaint()
{
	 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
	 pBitmap = wxBitmap(pWxImg);
	 dc.DrawBitmap(pBitmap, 0, 0, false);
}

cv::Mat &GUIMyFrame1::correctGamma(cv::Mat& img, double gamma) {
	double inverse_gamma = 1.0 / gamma;

	cv::Mat lut_matrix(1, 256, CV_8UC1);
	uchar * ptr = lut_matrix.ptr();
	for (int i = 0; i < 256; i++)
		ptr[i] = static_cast<int>((pow((double)i / 255.0, inverse_gamma) * 255.0));

	cv::Mat *result = new cv::Mat;
	LUT(img, lut_matrix, *result);

	return *result;
}

void GUIMyFrame1::m_b_choice_click(wxCommandEvent& event) {

	if (result.data) {
		result = image.clone();
		unsigned char* dataMat = result.data;
		int size = result.cols*result.rows * 3;

		if (m_choice->GetSelection()) {
			for (int i = 0; i < size; i++) {
				if (dataMat[i] < pow(2, m_choice->GetSelection() - 1)) {
					dataMat[i] = pow(2, m_choice->GetSelection() - 1) - 1;
				}
				else if (dataMat[i] > pow(2, m_choice->GetSelection() + 7) - 1) {
					dataMat[i] = pow(2, m_choice->GetSelection() + 7) - 1;
				}
			}
		}
		pWxImg = getImage(result);

		wxRect screen = m_scrolledWindow->GetSize();
		pWxImg.Rescale(screen.GetWidth(), screen.GetHeight());//skalowanie do okna
		histogram_fun(histogram2, pWxImg);

		Repaint();
	}
	else {
		wxMessageBox(_("Prosze wczytac plik!"));
	}
}

void GUIMyFrame1::histogram_fun(wxScrolledWindow* histogram, wxImage Img) {
	//***** Calculating the histograms *****
	int rgb_count[256] = { 0 };

	calculateHistograms(Img, rgb_count);

	//***** Creating the histogram images *****
	generate_hist_img(imgHistogramRGB, bitMapHistogramRGB, rgb_count, 0x00, 0x00, 0x00);

	//***** Drawing the histogram images *****
	histogramsGenerated = true;

	wxClientDC dc_1(histogram);
	wxBufferedDC dc1(&dc_1);
	dc1.Clear();
	dc1.DrawBitmap(bitMapHistogramRGB, 0, 0, true);
	return;
}