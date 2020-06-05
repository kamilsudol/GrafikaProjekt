#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));

 //img = cimg_library::CImg<float>::CImg(Img_Org.GetWidth(), Img_Org.GetHeight(), 1, 1);
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
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
	img.load_tiff("new.tif");

	CImg<unsigned char> img_normalized = img.get_normalize(0, 255);
	img_normalized.display("test");

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
	wxClientDC dc_1(m_scrolledWindow);

	wxBufferedDC dc1(&dc_1);
	
	dc1.Clear();
	
	dc1.DrawBitmap(bitMapHistogramRGB, 200, 0, true);
	dc1.DrawBitmap(bitMapHistogramR, 200, 100 + margin, true);
	dc1.DrawBitmap(bitMapHistogramG, 200, 2 * (100 + margin), true);
	dc1.DrawBitmap(bitMapHistogramB, 200, 3 * (100 + margin), true);

	return;
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{


}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
 

}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{


}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{

}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{

}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
 
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{

}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{

}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
 
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
 
}


void GUIMyFrame1::Contrast(int value)
{

}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	//dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia

}

void GUIMyFrame1::Brightness(int value)
{

}