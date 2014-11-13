#include "stdafx.h"
#include "DilationFilter.h"
#include "Histogram.h"

CDilationFilter::CDilationFilter()
	: CFilterBase(_T("Dilation Filter"))
{
}


CDilationFilter::~CDilationFilter()
{
}

void CDilationFilter::_onApplyFilter(CRawImage *pImage, ColorChannel nChannel)
{
	CHistogram histo(nChannel, 8);
	histo.ComputeHisogram(pImage);
	float otsu = histo.ComputeOtsuThreshold();

	auto pNewImage = CRawImage::CreateCompatibleImage(pImage);

	auto pPxlBuff = pImage->GetBitmapBits();
	auto pDestBuff = pNewImage->GetBitmapBits();

	int nHeight = pImage->Height();
	int nWidth = pImage->Width();

	for (int y = 0; y < nHeight ; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			BOOL bIn = FALSE;

			if (y != 0 && x != 0 && y != (nHeight - 1) && x != (nWidth - 1))
			{
				for (int j = -1; j < 2 && !bIn; ++j) {
					for (int i = -1; i < 2; ++i) {
						if (pPxlBuff[(y + j)*nWidth + (x + i)][nChannel] > otsu) {
							bIn = TRUE; break;
						}
					}
				}
			}

			if (bIn) {
				*pDestBuff = pPxlBuff[y *nWidth + x];
			}
			else {
				*pDestBuff = 0.0f;
			}

			++pDestBuff;
		}
	}

	pImage->Attach(pNewImage->Detach());
}