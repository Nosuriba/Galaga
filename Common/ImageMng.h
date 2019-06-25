#pragma once

#include <memory>
#include <vector>
#include <map>

/// LpImageMngÇå„Ç≈è¡Ç∑
#define LpImageMng (ImageMng::GetInstance())

#define IMAGE_ID(PATH) (ImageMng::GetInstance().GetID(PATH)) 

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		return *s_Instance;
	}

	const int& GetID(const std::string& key);
private:
	ImageMng();
	~ImageMng();
	struct ImageDeleter
	{
		void operator()(ImageMng * imageMng) const
		{
			delete imageMng;
		}
	};
	static std::unique_ptr<ImageMng, ImageDeleter> s_Instance;

	std::map<std::string, int> _imgMap;
};

