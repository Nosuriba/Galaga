#include <DxLib.h>
#include "ImageMng.h"

std::unique_ptr<ImageMng, ImageMng::ImageDeleter> ImageMng::s_Instance(new ImageMng());

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}

const int & ImageMng::GetID(const std::string& key)
{
	if (_imgMap.find(key) == _imgMap.end())
	{
		_imgMap[key] = DxLib::LoadGraph(key.c_str());
	}
	return _imgMap[key];
}