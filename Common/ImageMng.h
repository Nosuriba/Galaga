#pragma once

#include <memory>
#include <map>

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		return *s_Instance;
	}

	int GetID(std::string image);

private:
	ImageMng();
	~ImageMng();

	struct ImageMngDeleter
	{
		void operator()(ImageMng * imageMng) const
		{
			delete imageMng;
		}
	};
	static std::unique_ptr<ImageMng, ImageMngDeleter> s_Instance;

	std::map<std::string, int> _imgMap;
};

