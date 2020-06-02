#include "GUIMyFrame1.h"
#pragma omp parallel
#include <stdlib.h>



GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Korekcja gamma"));
// m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 //m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));

 //histogram->SetScrollbars(25, 25, 52, 40);
 histogram->SetBackgroundColour(wxColor(255, 255, 255));
 histogram2->SetBackgroundColour(wxColor(255, 255, 255));

 pWxImg = wxImage();

 //img = cimg_library::CImg<float>::CImg(Img_Org.GetWidth(), Img_Org.GetHeight(), 1, 1);
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

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
 // TO DO: Konwersja do skali szarosci  
	//Img_Cpy = Img_Org.ConvertToGreyscale();
	/*
	Img_Cpy = Img_Org.Copy();
	unsigned char *data = Img_Cpy.GetData();
	int size = Img_Org.GetHeight()*Img_Org.GetWidth() * 3;
	
	uint16 *data_cur = (uint16*)Img_Org.GetData();
	UCHAR *data_trans = (UCHAR*)Img_Cpy.GetData();
	
	double min = data_cur[0];
	double max = data_cur[0];

	for (int i = 0; i < size / 3; i++) {
		if (data_cur[i] > max) {
			max = data_cur[i];
		}
		if (data_cur[i] < min) {
			min = data_cur[i];
		}
	}

	int range = max - min;
	
	if (range > 0) {
		for (int i = 0; i < Img_Org.GetHeight()*Img_Org.GetWidth(); i++) {
			int val = (static_cast<int>(*++data_cur & 0xffff) - min);
			data_trans[i] = static_cast<UCHAR>(val);
		}
	}/*
	else {
		for (int i = 0; i < size / 2; i++) {
			int val = static_cast<int>(*++data_cur & 0xffff);
			data_trans[i] = static_cast<UCHAR>(val);
		}
	}
	*/
	img.load_tiff("malin.tiff");

	CImg<unsigned short> img_normalized = img.get_normalize(0, 255);
	img_normalized.display("test");
	//img.display("test");

}

void GUIMyFrame1::updateHistogram(void) {
	int rgb_count_n[256] = { 0 };
	int r_count_n[256] = { 0 };
	int g_count_n[256] = { 0 };
	int b_count_n[256] = { 0 };

	calculateHistograms(Img_Org, rgb_count_n, r_count_n, g_count_n, b_count_n);
	generate_hist_img(imgHistogramRGB_n, bitMapHistogramRGB_n, rgb_count_n, 0x00, 0x00, 0x00);
	generate_hist_img(imgHistogramR_n, bitMapHistogramR_n, r_count_n, 0xff, 0x00, 0x00);
	generate_hist_img(imgHistogramG_n, bitMapHistogramG_n, g_count_n, 0x00, 0xff, 0x00);
	generate_hist_img(imgHistogramB_n, bitMapHistogramB_n, b_count_n, 0x00, 0x00, 0xff);
	Repaint();
	return;
}



void GUIMyFrame1::calculateHistograms(wxImage &img, int rgb_count[256], int r_count[256], int g_count[256], int b_count[256]) {
	unsigned char *pixels = img.GetData();
	int w = img.GetWidth();
	int h = img.GetHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int r = pixels[3 * (y*w + x)];
			int g = pixels[3 * (y*w + x) + 1];
			int b = pixels[3 * (y*w + x) + 2];
			rgb_count[(r + g + b) / 3]++;
			r_count[r]++;
			g_count[g]++;
			b_count[b]++;
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


void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	//***** Calculating the histograms *****
	int rgb_count[256] = { 0 };
	int r_count[256] = { 0 };
	int g_count[256] = { 0 };
	int b_count[256] = { 0 };

	calculateHistograms(Img_Org, rgb_count, r_count, g_count, b_count);

	//***** Creating the histogram images *****
	generate_hist_img(imgHistogramRGB, bitMapHistogramRGB, rgb_count, 0x00, 0x00, 0x00);
	generate_hist_img(imgHistogramR, bitMapHistogramR, r_count, 0xff, 0x00, 0x00);
	generate_hist_img(imgHistogramG, bitMapHistogramG, g_count, 0x00, 0xff, 0x00);
	generate_hist_img(imgHistogramB, bitMapHistogramB, b_count, 0x00, 0x00, 0xff);

	
	//***** Drawing the histogram images *****
	histogramsGenerated = true;
	int margin = 70;
	wxClientDC dc_1(histogram);

	wxBufferedDC dc1(&dc_1);
	
	dc1.Clear();
	
	dc1.DrawBitmap(bitMapHistogramRGB, 0, 0, true);
	//dc1.DrawBitmap(bitMapHistogramR, 200, 100 + margin, true);
	//dc1.DrawBitmap(bitMapHistogramG, 200, 2 * (100 + margin), true);
	//dc1.DrawBitmap(bitMapHistogramB, 200, 3 * (100 + margin), true);

	return;
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{

	img.load_tiff("malin.tiff");

	//CImg<unsigned char> img_normalized = img.get_normalize(0, 255);
	//img_normalized.display("test");
	img.display("test");
}


void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	//histogram_fun(histogram, Img_Org);
	//histogram_fun(histogram2, Img_Org);
	/*
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("TIFF file (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK) {
		if (!source_image.LoadFile(WxOpenFileDialog.GetPath())) {
			wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		}
		else {
			// wyczytuje obraz
			source_image.LoadFile(WxOpenFileDialog.GetPath());
			bmp = FreeImage_Load(FIF_TIFF, WxOpenFileDialog.GetPath(), TIFF_DEFAULT);
			test = true;
			// kopiuje do image
			image = source_image.Copy();
			// narysuj
			Repaint();
		}
	}
	*/
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("JPEG file (*.tiff)|*.tiff"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK) {
		//if (cv::imread(WxOpenFileDialog.GetPath().c_str)) {
		//	wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		//}
		//else {
			// wyczytuje obraz
		const char* str = WxOpenFileDialog.GetFilename().mb_str();
		wxLogMessage(wxString::FromUTF8(str));
		load_img = cv::imread(str);
		unsigned char* dataMat = load_img.data;
		//cv::imshow("im", load_img);
		//cv::imshow("im", result);
		//cv::waitKey(0);
		//wczyt = wxImage(load_img.cols, load_img.rows, dataMat, TRUE);
		//wxRect screen = m_scrolledWindow->GetSize();
		//wczyt.Rescale(screen.GetWidth(), screen.GetHeight());
			//Repaint();
	//	}
	}

}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	/*
	wxClientDC dc_client(this->m_panel);
	wxBufferedDC dc_buffer(&dc_client);
	PrepareDC(dc_buffer);
	wxInitAllImageHandlers();

	if (m_saveDialog->ShowModal() == wxID_OK)
	{
		m_saveBitmap = new wxBitmap(m_panel->GetVirtualSize());

		wxMemoryDC memory;
		memory.SelectObject(*m_saveBitmap);
		memory.Blit(0, 0, m_panel->GetVirtualSize().GetX(), m_panel->GetVirtualSize().GetY(), &dc_buffer, 0, 0, wxCOPY, true);

		myRefresh();

		wxImage result = m_saveBitmap->ConvertToImage();
		result.SaveFile("result.png", wxBITMAP_TYPE_PNG);
	}
	*/
}


void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
	//FILE *f = fopen("gamma.txt", "a");
	cv::Mat image = cv::imread("new2.tif");
	//cv::namedWindow("tesoweAUUUUUUUU", CV_WINDOW_NORMAL);

	//cv::Mat image_grayscale = image.clone();
	//image_grayscale.convertTo(image_grayscale, CV_8U, 1 / 256.0);
	//cv::Mat res = image_grayscale / 257;

	//dst.convertTo(image, CV_8UC1);
	//fprintf(f, "%f \n", (m_s_brightness->GetValue()) / 50. -1);
	cv::Mat result = correctGamma(image, (m_s_brightness->GetValue())/50.); //poprawie to na casey, zeby ladnie odwzorowywac te skurwione gammy
	//cv::imshow("im", res);
	/////////////////////////////result.convertTo(image, CV_8UC1);
	/////////////////////////cv::imshow("im", result);
	//cv::waitKey(0);
	//fclose(f);

	///////////////////////////////////////////////////////////////////

	
	result.convertTo(result, CV_8UC1);
	unsigned char* dataMat = result.data;
	pWxImg = wxImage(result.cols, result.rows, dataMat, TRUE);
	//wxDisplay display(wxDisplay::GetFromWindow(m_scrolledWindow));
	wxRect screen = m_scrolledWindow->GetSize();
	pWxImg.Rescale(screen.GetWidth(), screen.GetHeight());//skalowanie do okna
	//cv::imshow("im", result);
	histogram_fun(histogram, pWxImg);
	histogram_fun(histogram2, pWxImg);
	Repaint();

	///////////////////////////////////////////////////////////////

}

void GUIMyFrame1::Contrast(int value)
{

}

void GUIMyFrame1::Repaint()
{
 //wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
// m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	                  //dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia

 pBitmap = wxBitmap(pWxImg);
 dc.DrawBitmap(pBitmap, 0, 0, false);

}

void GUIMyFrame1::Brightness(int value)
{

}

cv::Mat &GUIMyFrame1::correctGamma(cv::Mat& img, double gamma) {
	double inverse_gamma = 1.0 / gamma;

	cv::Mat lut_matrix(1, 256, CV_8UC1);
	uchar * ptr = lut_matrix.ptr();
	for (int i = 0; i < 256; i++)
		ptr[i] = (int)(pow((double)i / 255.0, inverse_gamma) * 255.0);

	cv::Mat *result = new cv::Mat;
	LUT(img, lut_matrix, *result);

	return *result;
}

void GUIMyFrame1::m_b_choice_click(wxCommandEvent& event) {
	cv::Mat image = cv::imread("new.tiff");
	unsigned char* dataMat = image.data;
	int size = image.cols*image.rows * 3;
	if (m_choice->GetSelection() == 1) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] > 255) {
				dataMat[i] = 255;
			}
		}
	}
	else if (m_choice->GetSelection() == 2) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2,2)) {
				dataMat[i] = pow(2, 2);
			}
			else if(dataMat[i] > pow(2, 9)-1){
				dataMat[i] = pow(2, 9)-1;
			}
		}
	}
	else if (m_choice->GetSelection() == 3) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 3)) {
				dataMat[i] = pow(2, 3);
			}
			else if (dataMat[i] > pow(2, 10) - 1) {
				dataMat[i] = pow(2, 10) - 1;
			}
		}
	}
	else if (m_choice->GetSelection() == 4) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 4)) {
				dataMat[i] = pow(2, 4);
			}
			else if (dataMat[i] > pow(2, 11) - 1) {
				dataMat[i] = pow(2, 11) - 1;
			}
		}
	}
	else if (m_choice->GetSelection() == 5) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 5)) {
				dataMat[i] = pow(2, 5);
			}
			else if (dataMat[i] > pow(2, 12) - 1) {
				dataMat[i] = pow(2, 12) - 1;
			}
		}
	}
	else if (m_choice->GetSelection() == 6) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 6)) {
				dataMat[i] = pow(2, 6);
			}
			else if (dataMat[i] > pow(2, 13) - 1) {
				dataMat[i] = pow(2, 13) - 1;
			}
		}
	}
	else if (m_choice->GetSelection() == 7) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 7)) {
				dataMat[i] = pow(2, 7);
			}
			else if (dataMat[i] > pow(2, 14) - 1) {
				dataMat[i] = pow(2, 14) - 1;
			}
		}
	}
	else if (m_choice->GetSelection() == 8) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 8)) {
				dataMat[i] = pow(2, 8);
			}
			else if (dataMat[i] > pow(2, 15) - 1) {
				dataMat[i] = pow(2, 15) - 1;
			}
		}
	}
	else if (m_choice->GetSelection() == 9) {
		for (int i = 0; i < size; i++) {
			if (dataMat[i] < pow(2, 9)) {
				dataMat[i] = pow(2, 9);
			}
			else if (dataMat[i] > pow(2, 16) - 1) {
				dataMat[i] = pow(2, 16) - 1;
			}
		}
	}
	else { ; }
	
	pWxImg = wxImage(image.cols, image.rows, dataMat, TRUE);
	//wxDisplay display(wxDisplay::GetFromWindow(m_scrolledWindow));
	wxRect screen = m_scrolledWindow->GetSize();
	pWxImg.Rescale(screen.GetWidth(), screen.GetHeight());//skalowanie do okna
	//cv::imshow("im", image);
	histogram_fun(histogram, pWxImg);

	Repaint();
}

void GUIMyFrame1::histogram_fun(wxScrolledWindow* histogram, wxImage Img) {
	//***** Calculating the histograms *****
	int rgb_count[256] = { 0 };
	int r_count[256] = { 0 };
	int g_count[256] = { 0 };
	int b_count[256] = { 0 };

	calculateHistograms(Img, rgb_count, r_count, g_count, b_count);

	//***** Creating the histogram images *****
	generate_hist_img(imgHistogramRGB, bitMapHistogramRGB, rgb_count, 0x00, 0x00, 0x00);
	generate_hist_img(imgHistogramR, bitMapHistogramR, r_count, 0xff, 0x00, 0x00);
	generate_hist_img(imgHistogramG, bitMapHistogramG, g_count, 0x00, 0xff, 0x00);
	generate_hist_img(imgHistogramB, bitMapHistogramB, b_count, 0x00, 0x00, 0xff);


	//***** Drawing the histogram images *****
	histogramsGenerated = true;
	int margin = 70;
	wxClientDC dc_1(histogram);

	wxBufferedDC dc1(&dc_1);

	dc1.Clear();

	dc1.DrawBitmap(bitMapHistogramRGB, 0, 0, true);
	//dc1.DrawBitmap(bitMapHistogramR, 200, 100 + margin, true);
	//dc1.DrawBitmap(bitMapHistogramG, 200, 2 * (100 + margin), true);
	//dc1.DrawBitmap(bitMapHistogramB, 200, 3 * (100 + margin), true);

	return;
}