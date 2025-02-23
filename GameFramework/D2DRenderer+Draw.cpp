#include "stdafx.h"
#include "D2DRenderer.h"

void D2DRenderer::RenderText(const int x, const int y, const wstring& text, const int size,
	const DefaultBrush& defaultBrush /*= DefaultBrush::Black*/, const DWRITE_TEXT_ALIGNMENT& align /*= DWRITE_TEXT_ALIGNMENT_LEADING*/, const wstring& font /*= L"맑은고딕"*/)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout(nullptr);
	if (HRESULT hr = _DWFactory->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()), _fontList[font], static_cast<float>(text.length() * size), static_cast<float>(size), &layout); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateTextLayout");
		return;
	}

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = static_cast<UINT32>(text.length());

	layout->SetFontSize(static_cast<float>(size), range);
	layout->SetTextAlignment(align);

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, _defaultBrushList[(UINT)defaultBrush]);

	SAFE_RELEASE(layout);
}

void D2DRenderer::RenderText(const int x, const int y, const wstring& text, const COLORREF& color,
	const float alpha, const int size, const DWRITE_TEXT_ALIGNMENT& align /*= DWRITE_TEXT_ALIGNMENT_LEADING*/, const wstring& font /*= L"맑은고딕"*/)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout(nullptr);
	if (HRESULT hr = _DWFactory->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()), _fontList[font], static_cast<float>(text.length() * size), static_cast<float>(size), &layout); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateTextLayout");
		return;
	}

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = static_cast<UINT32>(text.length());
	layout->SetFontSize(static_cast<float>(size), range);
	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	ID2D1SolidColorBrush* brush(nullptr);
	if (HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, brush);

	SAFE_RELEASE(brush);
	SAFE_RELEASE(layout);
}

void D2DRenderer::RenderTextField(const int x, const int y, const wstring& text, const int size,
	const int width, const int height, const DefaultBrush& defaultBrush /*= DefaultBrush::Black*/, const DWRITE_TEXT_ALIGNMENT& align /*= DWRITE_TEXT_ALIGNMENT_LEADING*/, const wstring& font /*= L"맑은고딕"*/)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout(nullptr);
	if (HRESULT hr = _DWFactory->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()), _fontList[font], static_cast<float>(width), static_cast<float>(height), &layout); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateTextLayout");
		return;
	}

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = static_cast<UINT32>(text.length());
	layout->SetFontSize(static_cast<float>(size), range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, _defaultBrushList[(UINT)defaultBrush]);

	SAFE_RELEASE(layout);
}

void D2DRenderer::RenderTextField(const int x, const int y, const wstring& text, const COLORREF& color,
	const int size, const int width, const int height, const float alpha /*= 1.0f*/, const DWRITE_TEXT_ALIGNMENT& align /*= DWRITE_TEXT_ALIGNMENT_LEADING*/, const wstring& font /*= L"맑은고딕"*/)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout(nullptr);
	if (HRESULT hr = _DWFactory->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()), _fontList[font], static_cast<float>(width), static_cast<float>(height), &layout); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateTextLayout");
		return;
	}

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = static_cast<UINT32>(text.length());
	layout->SetFontSize(static_cast<float>(size), range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	ID2D1SolidColorBrush* brush(nullptr);
	if (HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(static_cast<float>(x), static_cast<float>(y)), layout, brush);

	SAFE_RELEASE(layout);
	SAFE_RELEASE(brush);
}

void D2DRenderer::DrawLine(const Vector2& start, const Vector2& end, const D2D1::ColorF::Enum& color, const float alpha, const float strokeWidth /*= 1.f*/)
{
	ID2D1SolidColorBrush* brush(nullptr);
	if (HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;

	_D2DRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y), D2D1::Point2F(endPos.x, endPos.y), brush, strokeWidth);
	SAFE_RELEASE(brush);
}

void D2DRenderer::DrawLine(const Vector2& start, const Vector2& end, const DefaultBrush& defaultBrush /*= DefaultBrush::Black*/, const float strokeWidth /*= 1.f*/)
{
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;

	_D2DRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y),
		D2D1::Point2F(endPos.x, endPos.y), _defaultBrushList[(UINT)defaultBrush], strokeWidth);

}

void D2DRenderer::DrawRectangle(const FloatRect& rc, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth /*= 1.f*/)
{
	FloatRect rect = rc;

	ID2D1SolidColorBrush* brush;
	if (HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_D2DRenderTarget->DrawRectangle(D2D1::RectF(static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.right), static_cast<float>(rect.bottom)),
		brush, strokeWidth);

	SAFE_RELEASE(brush);
}

void D2DRenderer::DrawRectangle(const FloatRect& rc, const DefaultBrush& defaultBrush /*= DefaultBrush::Black*/, const float strokeWidth /*= 1.f*/)
{
	FloatRect rect = rc;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_D2DRenderTarget->DrawRectangle(D2D1::RectF(static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.right), static_cast<float>(rect.bottom)),
		_defaultBrushList[(UINT)defaultBrush], strokeWidth);
}

void D2DRenderer::DrawEllipse(const Vector2& origin, const float radius, const DefaultBrush& defaultBrush /*= DefaultBrush::Black*/, const float strokeWidth /*= 1.f*/)
{
	FloatRect rc = RectMakePivot(origin, Vector2(radius, radius), Pivot::Center);
	Vector2 pos = origin;
	float tempRadius = radius;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawEllipse(&ellipse, _defaultBrushList[(UINT)defaultBrush], strokeWidth);
}

void D2DRenderer::DrawEllipse(const Vector2& origin, const float radius, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth /*= 1.f*/)
{
	FloatRect rc = RectMakePivot(origin, Vector2(radius, radius), Pivot::Center);
	Vector2 pos = origin;
	float tempRadius = radius;

	ID2D1SolidColorBrush* brush(nullptr);
	if (HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);

	SAFE_RELEASE(brush);
}

void D2DRenderer::FillRectangle(const FloatRect& rc, const D2D1::ColorF::Enum& color, const float alpha)
{
	FloatRect rect = rc;

	ID2D1SolidColorBrush* brush(nullptr);
	if (HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush); FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillRectangle(D2D1::RectF(static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.right), static_cast<float>(rect.bottom)), brush);

	SAFE_RELEASE(brush);
}

void D2DRenderer::FillRectangle(const FloatRect& rc, const DefaultBrush& defaultBrush /*= DefaultBrush::Black*/)
{
	FloatRect rect = rc;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_D2DRenderTarget->FillRectangle(D2D1::RectF(static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.right), static_cast<float>(rect.bottom)),
		_defaultBrushList[(UINT)defaultBrush]);
}

void D2DRenderer::FiilEllipse(const Vector2& origin, const float radius, const D2D1::ColorF::Enum& color, const float alpha)
{
	FloatRect rc = RectMakePivot(origin, Vector2(radius, radius), Pivot::Center);
	Vector2 pos = origin;
	float tempRadius = radius;

	ID2D1SolidColorBrush* brush(nullptr);
	HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	if (FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillEllipse(&ellipse, brush);
	SAFE_RELEASE(brush);
}

void D2DRenderer::FiilEllipse(const Vector2& origin, const float radius, const DefaultBrush& brush /*= DefaultBrush::Black*/)
{
	FloatRect rc = RectMakePivot(origin, Vector2(radius, radius), Pivot::Center);
	Vector2 pos = origin;
	float tempRadius = radius;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillEllipse(&ellipse, _defaultBrushList[(UINT)brush]);
}

void D2DRenderer::DrawRotationNullRectangle(const FloatRect& rc, const D2D1::ColorF::Enum& color, const float alpha, const float angle, const float strokeWidth /*= 1.f*/)
{
	FloatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.GetWidth() / 2;
	offset.y = rect.top + rect.GetHeight() / 2;

	ID2D1SolidColorBrush* brush(nullptr);
	HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	if (FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));
	_D2DRenderTarget->DrawRectangle(D2D1::RectF(static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.right), static_cast<float>(rect.bottom)), brush, strokeWidth);

	SAFE_RELEASE(brush);
}

void D2DRenderer::DrawRotationFillRectangle(const FloatRect& rc, const D2D1::ColorF& color, const float angle)
{
	FloatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.GetWidth() / 2;
	offset.y = rect.top + rect.GetHeight() / 2;

	ID2D1SolidColorBrush* brush(nullptr);
	HRESULT hr = _D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	if (FAILED(hr)) {
		ASSERT_NO_EXIT(FAILED(hr), L"Failed to CreateSolidColorBrush");
		return;
	}
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));
	_D2DRenderTarget->FillRectangle(D2D1::RectF(static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.right), static_cast<float>(rect.bottom)), brush);

	SAFE_RELEASE(brush);
}
