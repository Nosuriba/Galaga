#pragma once

#include <memory>
#include <vector>
#include <map>

#define LpImageMng (ImageMng::GetInstance())

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

	std::map<std::string, int> _imgMap;	// LoadGraph‚ğg‚¤—\’è‚È‚Ì‚ÅAæ‚Á‚Ä‚¨‚­
};

