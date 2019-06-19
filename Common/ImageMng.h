#pragma once

#include <memory>
#include <vector>
#include <map>

/// 使わないので後で消す
#include "../Vector2.h"
using VEC_INT = std::vector<int>;		/// LoadDivGraph

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		return *s_Instance;
	}

	const int& GetID(std::string key);
	
	/// 使わないので後で消す
	const VEC_INT& GetID(std::string fileName, const Vector2& cnt, const Vector2& size);		

private:
	ImageMng();
	~ImageMng();

	const int& GetID(std::string key, std::string fileName);
	const VEC_INT& GetID(std::string key, std::string fileName,
						 const Vector2& cnt, const Vector2& size);

	struct ImageMngDeleter
	{
		void operator()(ImageMng * imageMng) const
		{
			delete imageMng;
		}
	};
	static std::unique_ptr<ImageMng, ImageMngDeleter> s_Instance;

	//std::map<std::string, int> _imgMap;	// LoadGraphしか使わないので、取っておく
	std::map<std::string, std::vector<int>> _imgMap;
};

