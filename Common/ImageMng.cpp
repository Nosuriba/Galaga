#include <DxLib.h>
#include "ImageMng.h"

std::unique_ptr<ImageMng, ImageMng::ImageMngDeleter> ImageMng::s_Instance(new ImageMng());

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}

const int & ImageMng::GetID(std::string key)
{
	return GetID(key, key);
}

const int & ImageMng::GetID(std::string key, std::string fileName)
{
	if (_imgMap.find(key) == _imgMap.end())
	{
		_imgMap[key].resize(1);
		_imgMap[key][0] = DxLib::LoadGraph(fileName.c_str());
	}
	return _imgMap[key][0];
}

const VEC_INT & ImageMng::GetID(std::string key, std::string fileName, const Vector2 & cnt, const Vector2 & size)
{
	if (_imgMap.find(key) == _imgMap.end())
	{
		_imgMap[key].resize(cnt.x * cnt.y);
		DxLib::LoadDivGraph(key.c_str(), cnt.x * cnt.y, cnt.x, cnt.y,
							size.x, size.y, &_imgMap[fileName][0]);
	}
	return _imgMap[key];
}

const VEC_INT& ImageMng::GetID(std::string key, const Vector2& cnt, const Vector2& size)
{
	GetID(key, key, cnt, size);
	return _imgMap[key];
}