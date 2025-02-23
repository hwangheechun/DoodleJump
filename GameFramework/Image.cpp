#include "stdafx.h"
#include "Image.h"

Image::Image(ID2D1Bitmap *const bitmap, const TagLoadedImageInfo& loadinfo)
	: _bitmap(bitmap), _loadInfo(loadinfo), _scale(1.f), _alpha(1.f), _angle(0.f), _maxFrameX(1), _maxFrameY(1)
{
	this->_size.x = static_cast<float>(this->_bitmap->GetPixelSize().width);
	this->_size.y = static_cast<float>(this->_bitmap->GetPixelSize().height);

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = _size.x;
	rc.height = _size.y;
	this->_frameInfo.push_back(rc);
	this->ResetRenderOption();
}

Image::Image(ID2D1Bitmap *const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY)
	: _bitmap(bitmap), _loadInfo(loadinfo), _maxFrameX(maxFrameX), _maxFrameY(maxFrameY), _scale(1.f), _alpha(1.f), _angle(0.f)
{
	this->_size.x = static_cast<float>(_bitmap->GetPixelSize().width);
	this->_size.y = static_cast<float>(_bitmap->GetPixelSize().height);

	const float frameX = _size.x / static_cast<float>(this->_maxFrameX);
	const float frameY = _size.y / static_cast<float>(this->_maxFrameY);

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = static_cast<float>(i) * (frameX);
			rc.y = static_cast<float>(j) * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			this->_frameInfo.push_back(rc);
		}
	}

	this->ResetRenderOption();
}

Image::~Image()
{
	SAFE_RELEASE(_bitmap);
}

void Image::Render(const Vector2& position)
{
	Vector2 size = _size * _scale;

	// SRT
	// 스케일 행렬
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	// 회전 행렬
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	// 이동 행렬
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f );

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.x, size.y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha);
	ResetRenderOption();
}

void Image::FrameRender(const Vector2& position, const int frameX, const int frameY)
{
	//현재 프레임 인덱스 
	int frame = frameY * _maxFrameX + frameX;
	Vector2 size = _size * _scale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF(static_cast<float>(_frameInfo[frame].x), static_cast<float>(_frameInfo[frame].y),
		static_cast<float>(_frameInfo[frame].x + _frameInfo[frame].width),
		static_cast<float>(_frameInfo[frame].y + _frameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void Image::AniRender(const Vector2& position, Animation* ani, float scale)
{
	Vector2 tempFrameSize;
	tempFrameSize.x = ani->GetFrameWidth();
	tempFrameSize.y = ani->GetFrameHeight();

	Vector2 size = tempFrameSize * scale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scale, scale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation((position.x - size.x / 2.f), (position.y - size.y / 2.f));//(position.x - size.x / 2.f, position.y - size.y / 2.f ); // 중점 ??

	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, _size.x, _size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)ani->GetFramePos().x, (float)ani->GetFramePos().y,
		(float)(ani->GetFramePos().x + tempFrameSize.x),
		(float)(ani->GetFramePos().y + tempFrameSize.y));

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);
	ResetRenderOption();
}

void Image::ResetRenderOption()
{
	this->_alpha = 1.0f;
	this->_scale = 1.0f;
	this->_angle = 0.f;

	if (_frameInfo.size() <= 1)
	{
		this->_size.x = static_cast<float>(_bitmap->GetPixelSize().width);
		this->_size.y = static_cast<float>(_bitmap->GetPixelSize().height);
	}
	else
	{
		this->_size.x = _frameInfo[0].width;
		this->_size.y = _frameInfo[0].height;
	}
}
