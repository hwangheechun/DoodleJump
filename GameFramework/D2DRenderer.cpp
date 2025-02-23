#include "stdafx.h"
#include "D2DRenderer.h"

D2DRenderer::D2DRenderer()
	:_D2DFactory(nullptr), _D2DRenderTarget(nullptr), _DWFactory(nullptr)
{
	this->CreateFactory();
	this->CreateRenderTarget();
	this->CreateDefaultBrush();
	this->AddTextFormat(L"맑은고딕");
	_D2DRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
}

D2DRenderer::~D2DRenderer()
{
	TextIter iter = _fontList.begin();
	for (; iter != _fontList.end(); ++iter)
		SAFE_RELEASE(iter->second);

	for (UINT i = 0; i < (UINT)DefaultBrush::End; ++i)
		SAFE_RELEASE(_defaultBrushList[i]);

	SAFE_RELEASE(_DWFactory);

	SAFE_RELEASE(_D2DSurface);
	SAFE_RELEASE(_D2DRenderTarget);
	SAFE_RELEASE(_D2DFactory);
}

void D2DRenderer::BeginRender(const D2D1::ColorF& backgroundColor)
{
	_D2DRenderTarget->BeginDraw();
	_D2DRenderTarget->Clear(backgroundColor);
}

void D2DRenderer::EndRender()
{
	_D2DRenderTarget->EndDraw();
}


void D2DRenderer::CreateFactory()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_D2DFactory);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*&_DWFactory),
		(IUnknown**)&_DWFactory
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}

void D2DRenderer::CreateRenderTarget()
{
	// Render Target : 백버퍼의 역할을 하는 클래스, 여러 렌더링을 위한 유틸적인 것들이 들어 있음 (WinAPI의 HDC)
	// 화면에 렌더링을 요청하려면, 렌더 타겟을 통해서만 가능함

	HRESULT hr;

	// 1. 윈도우 핸들을 통한 화면 Rect 가져오기
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);

	// 2. 디바이스 DPI 정보
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(_hdc, LOGPIXELSX));
	FLOAT dpiY = static_cast<FLOAT>(GetDeviceCaps(_hdc, LOGPIXELSY));

	// 3. Render Target을 생성하기 위한 속성 값 초기화
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// 4. Render Target의 사이즈 (= clientRect)
	D2D1_SIZE_U renderTargetSize = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	// 5. Render Target 생성
	hr = _D2DFactory->CreateHwndRenderTarget(renderTargetProperties, D2D1::HwndRenderTargetProperties(_hWnd, renderTargetSize), &_D2DRenderTarget);

	assert(SUCCEEDED(hr));
}

void D2DRenderer::CreateDefaultBrush()
{
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Black]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::White]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Yellow]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Red]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Blue]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Green]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Gray]);
}

void D2DRenderer::AddTextFormat(const wstring& font, const float& defaultSize /*= 1.f*/)
{
	HRESULT hr;
	IDWriteTextFormat* format = NULL;

	hr = this->_DWFactory->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		defaultSize,
		L"ko",
		&format
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	this->_fontList.insert(std::make_pair(font, format));
}


