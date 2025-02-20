#pragma once
#include <map>
#include <string>
#include <vector>

struct MaterialParam
{
	std::string file_path;
	int all_num;
	int num_x;
	int num_y;
	int size_x;
	int size_y;
};

//リソース管理クラス
class ResourceManager
{
private:
	//自クラスのポインタ（アドレス先に実体がある）
	static ResourceManager* instance;

	//画像コンテナ
	std::map<std::string, std::vector<int>> images_container;
	//音源コンテナ
	std::map<std::string, int> sounds_container;
public:
	//自クラスのメンバでしか生成できないようにする
	ResourceManager() = default;

	//コピーガード
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	//~コピーガード

public:
	~ResourceManager() = default;

public:
	/// <summary>
	///	リソース管理クラスのインスタンス取得処理
	/// </summary>
	/// <returns>クラスのポインタ</returns>
	static ResourceManager* GetInstance();

	/// <summary>
	/// リソース管理クラスのインスタンス削除処理
	/// </summary>
	static void DeleteInstance();

public:
	/**
	*画像を取得する
	* @param file_name ファイルパス
	* @param all_num	画像の総数
	* @param num_x		横の総数
	* @param num_y		縦の総数
	* @param size_x		横のサイズ（px）
	* @param size_y		縦のサイズ（px）
	* @return 読み込んだ画像ハンドルのstd::vector配列
	*/
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(MaterialParam element);

	/**
	*音源を取得する
	* @param file_name ファイルパス
	*/
	const int& GetSounds(std::string file_name);

	/**
	* 全ての画像を削除する
	* @param meterial_handle 削除したい画像ハンドルのstd::vector配列
	*/
	void UnloadResourcesAll();

private:
	/**
	* 画像ハンドルを読込リソースを作成する
	* @param file_name　ファイルパス
	*/
	void CreateImagesResource(std::string file_name);

	/**
	*画像を取得する
	* @param file_name ファイルパス
	* @param all_num	画像の総数
	* @param num_x		横の総数
	* @param num_y		縦の総数
	* @param size_x		横のサイズ（px）
	* @param size_y		縦のサイズ（px）
	* @return 読み込んだ画像ハンドルのstd::vector配列
	*/
	void CreateImagesResource(std::string& file_name,int all_num,int num_x,int num_y,int size_x,int size_y);

	/**
	* 音源ハンドルを読込リソースを作成する
	* @param file_name　ファイルパス
	*/
	void CreateSoundsResource(std::string& file_name);


};
