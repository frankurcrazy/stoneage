#ifndef _ITEMS_MALL_H__
#define _ITEMS_MALL_H__

#include <map>


#define ITEMS_MALL_FILE_NAME "shopsellitems.bin"


typedef struct ITEMSMALL
{
	int id;                  //id
	int itemId;              //物品/寵物ID
	char itemName[128];      //物品/寵物名字
	int itemFlag;            //是物品還是寵物，物品為：1；寵物為：2。
	int bmpNo;               //寵物/物品外觀圖片
	int currencyType;        //購買些物品所需的貨幣種類
	int currencyNum;        //購買此物品所需的金幣數量，不能用此貨幣購買，則此字段為：-1
	int recordType;          //物品種類：1錶示最新上價；4錶示其它貨品；
	char szLine1[128];
	char szLine2[128];
	char szLine3[128];
}*LP_ITEMSMALL;

//內置商城相關操作顯示類
class ItemsMall
{
public:
	static ItemsMall& MakeInstance();
	static void Destroy();

	void SetItemDatas(char* pszData);
	
	int GetItemsNums();
	int GetPetsNums();
	int GetAllItemSize() { return g_mapItemsMall.size(); }

	ITEMSMALL* GetItemByIndex(int nIndex);
	ITEMSMALL* GetItemByType(int nIndex, int nType, int recordType = 1);   //recodType默認值為1錶示最新上價物品，4為其它物品
	ITEMSMALL* GetAllItemsByIndex(int nIndex, int nType);
	ITEMSMALL* GetAllPetsByIndex(int nIndex, int nType);
	ITEMSMALL* GetAllOtherItemsByIndex(int nIndex, int nType);

	int GetCurrentItemNum(int nCurrencyType, int nType);

	//int GetAllLatestNum();  //最新上價貨品數量
	//int GetAllItemsNum(); //裝備貨品數量
	//int GetAllPetsNum(); //寵物貨品數量
	//int GetAllOthersNum(); //其它貨品數量

protected:
	ItemsMall(void){}
	ItemsMall(ItemsMall&);

	~ItemsMall(void){}

	static ItemsMall* instance;
	static std::map<int, ITEMSMALL> g_mapItemsMall;  

	//static int m_nAllLatestNum;
	//static int m_nAllItemsNum;
	//static int m_nAllPetsNum;
	//static int m_nAllOthersNum;
};

#endif