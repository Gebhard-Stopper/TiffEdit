#include "stdafx.h"
#include "ErosionFilter.h"
#include "Histogram.h"

CErosionFilter::CErosionFilter()
	: CFilterBase(_T("Erosion Filter"))
{
}


CErosionFilter::~CErosionFilter()
{
}

void CErosionFilter::_applyFilter(CRawImage *pImage) 
{
	CHistogram histo(CHistogram::Grey, 8);
	histo.ComputeHisogram(pImage);
	float otsu = histo.ComputeOtsuThreshold() * .5;

	float *pPxlBuff = static_cast<float*>(pImage->GetBitmapBits());

	auto pNewImage = CRawImage::CreateCompatibleImage(pImage);
	float *pDestBuff = static_cast<float*>(pNewImage->GetBitmapBits());

	int nHeight = pImage->Height();
	int nWidth = pImage->Width();

	BOOL ourCount = 0;

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			BOOL bIn = TRUE;

			if (y != 0 && x != 0 && y != (nHeight - 1) && x != (nWidth - 1))
			{
				for (int j = -1; j < 2 && bIn; ++j) {
					for (int i = -1; i < 2; ++i) {
						if (pPxlBuff[(y + j)*nWidth + (x + i)] < otsu) {
							++ourCount;

							bIn = FALSE; break;
						}
					}
				}
			}

			if (bIn) {
				*pDestBuff = pPxlBuff[y *nWidth + x ];
			}
			else {
				*pDestBuff = 0.0f;
			}

			++pDestBuff;
		}
	}

	pImage->Attach(pNewImage->Detach());
	delete pNewImage;
}

void CErosionFilter::_applyFilterRGBA(CRawImage *pImage) {}