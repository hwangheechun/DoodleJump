#pragma once
#include "Animation.h"

class Image final
{
public:
	struct TagLoadedImageInfo
	{
		wstring key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const wstring& key,const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct FrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap*		_bitmap;
	float				_alpha;			

	Vector2				_size;			
	float				_scale;			
	float				_angle;

	TagLoadedImageInfo	_loadInfo;		

	vector<Image::FrameRect>	_frameInfo;
	int							_maxFrameX;
	int							_maxFrameY;
private:
	friend class ImageManager;
	Image() = delete;

	// ImageManager에서 생성된 비트맵, 이미지 정보(키값,파일 경로)로 프레임 이미지가 아닌 이미지 클래스 생성
	Image( ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo);
	// ImageManager에서 생성된 비트맵, 이미지 정보(키값,파일 경로)로 프레임 이미지 클래스 생성
	Image( ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY);

	virtual ~Image();

	Image operator= (const Image& image) {}
public:
	void Render(const Vector2& position);
	void FrameRender(const Vector2& position, const int frameX, const int frameY);
	void AniRender(const Vector2& position, Animation* ani, float scale);

	// 이미지 클래스 렌더 관련 옵션들 전부 초기화
	void ResetRenderOption();

	void SetSize(const Vector2& vec) { this->_size = vec; }
	void SetAlpha(const float alpha) { this->_alpha = alpha; }
	void SetScale(const float scale) { this->_scale = scale; }
	void SetAngle(const float angle) { this->_angle = angle; }

	const int GetMaxFrameX()const{ return _maxFrameX; }
	const int GetMaxFrameY()const{ return _maxFrameY; }
	const wstring GetKey() const { return this->_loadInfo.key; }
	const UINT GetWidth() const{ return _bitmap->GetPixelSize().width; }
	const UINT GetHeight()const{ return _bitmap->GetPixelSize().height; }
	const Vector2 GetSize()const { return this->_size; }
	Vector2 GetFrameSize(const int& frame = 0) const { return Vector2(_frameInfo[frame].width, _frameInfo[frame].height); }
	const TagLoadedImageInfo& GetLoadInfo() const { return _loadInfo; }
};

