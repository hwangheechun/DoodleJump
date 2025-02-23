#include "stdafx.h"
#include "ImageManager.h"

#include "Image.h"
#include <io.h>

ImageManager::ImageManager()
	: mWicFactory(nullptr)
{
	// WIC(Windows Imaging Component) 팩토리 생성
	// Direct2D는 이미지를 로드하는 기능이 없음 -> WIC라는 라이브러리의 이미지로부터 이미지 데이터를 만들 수 있음
	HRESULT hr1 = CoInitialize(NULL);
	HRESULT hr2 = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mWicFactory));
#ifdef _DEBUG
	assert(SUCCEEDED(hr1));
	assert(SUCCEEDED(hr2));
#endif
}

ImageManager::~ImageManager()
{
	this->DeleteAll();
	SAFE_RELEASE(mWicFactory);
}

Image* ImageManager::AddImage(const wstring& key, const wstring& file)
{
	Image* image = this->FindImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = this->CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::TagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap, loadInfo);
		_imageList.insert(make_pair(key, image));
		return image;
	}
	else
		assert(SUCCEEDED(E_FAIL));

	return nullptr;
}

Image* ImageManager::AddFrameImage(const wstring& key, const wstring& file, const int maxFrameX, const int maxFrameY)
{
	Image* image = this->FindImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::TagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap,loadInfo,maxFrameX,maxFrameY);
		this->_imageList.insert(make_pair(key, image));
		return image;
	}

	return nullptr;
}

Image* ImageManager::FindImage(const wstring& key)
{
	ImageIter iter = _imageList.find(key);
	if (iter != _imageList.end())
		return iter->second;
	return nullptr;
}

ID2D1Bitmap* ImageManager::CreateD2DBitmapFromFile(const wstring & file)
{
	// 디코더 생성
	IWICBitmapDecoder* ipDecoder = nullptr;
	HRESULT hr;
	hr = mWicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	// 디코더에서 프레임 얻음
	IWICBitmapFrameDecode* ipFrame = nullptr;
	hr = ipDecoder->GetFrame(0, &ipFrame);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	// 프레임을 기반으로 포맷 컨버터 생성
	IWICFormatConverter* convertedSrcBmp = nullptr;
	hr = mWicFactory->CreateFormatConverter(&convertedSrcBmp);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	// 컨버터 초기화
	hr = convertedSrcBmp->Initialize
	(
		ipFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	// 컨버트된 데이터를 기반으로 실제 Direct2D용 비트맵을 생성
	ID2D1Bitmap* ipResult = nullptr;
	hr = D2DRenderer::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap
	(
		convertedSrcBmp,
		nullptr,
		&ipResult
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	SAFE_RELEASE(convertedSrcBmp);
	SAFE_RELEASE(ipFrame);
	SAFE_RELEASE(ipDecoder);

	return ipResult;
}

void ImageManager::DeleteAll()
{
	ImageIter iter = _imageList.begin();
	for (; iter != _imageList.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	_imageList.clear();
}