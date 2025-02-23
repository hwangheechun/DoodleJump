#pragma once

class ImageManager final : public SingletonBase<ImageManager>
{
private:
	ImageManager();
	virtual ~ImageManager();

	typedef map<wstring, class Image*>::iterator ImageIter; 
	friend class SingletonBase<ImageManager>;

private:
	map<wstring, class Image*> _imageList; 

	struct IWICImagingFactory* mWicFactory;

public:
	class Image* AddImage(const wstring& key, const wstring& file);
	class Image* AddFrameImage(const wstring& key,const wstring& file,const int maxFrameX, const int maxFrameY);
	class Image* FindImage(const wstring& key);

private:
	ID2D1Bitmap* CreateD2DBitmapFromFile(const wstring& file);
	void DeleteAll();
};