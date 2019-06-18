#include <DxLib.h>
#include "ImageMng.h"

std::unique_ptr<ImageMng, ImageMng::ImageMngDeleter> ImageMng::s_Instance(new ImageMng());


int ImageMng::GetID(std::string image)
{
	if (_imgMap.find(image) == _imgMap.end())
	{
		_imgMap[image] = DxLib::LoadGraph(image.c_str());
	}
	
	return _imgMap[image];
}

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}
