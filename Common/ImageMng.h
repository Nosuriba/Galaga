#pragma once

#include <memory>
#include <vector>
#include <map>

/// 使わないので後でｺﾒﾝﾄｱｳﾄする
#include "../Vector2.h"
using VEC_INT = std::vector<int>;		/// LoadDivGraph用の型

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		return *s_Instance;
	}

	const int& GetID(const std::string& key);
	
	/// 使わないので後でｺﾒﾝﾄｱｳﾄする
	const VEC_INT& GetID(const std::string& fileName, const Vector2& cnt, const Vector2& size);		

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

	//std::map<std::string, int> _imgMap;	// LoadGraphを使う予定なので、取っておく
	std::map<std::string, std::vector<int>> _imgMap;
};

