#pragma once

#include <memory>
#include <vector>
#include <map>

/// �g��Ȃ��̂Ō�ź��ı�Ă���
#include "../Vector2.h"
using VEC_INT = std::vector<int>;		/// LoadDivGraph�p�̌^

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		return *s_Instance;
	}

	const int& GetID(std::string key);
	
	/// �g��Ȃ��̂Ō�ź��ı�Ă���
	const VEC_INT& GetID(std::string fileName, const Vector2& cnt, const Vector2& size);		

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

	//std::map<std::string, int> _imgMap;	// LoadGraph���g���\��Ȃ̂ŁA����Ă���
	std::map<std::string, std::vector<int>> _imgMap;
};

