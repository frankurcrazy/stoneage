--此lua應該是裝備鑲嵌和融閤C相關，丸子看不懂!
function getIntPart(x)
    if x <= 0 then
       return math.ceil(x);
    end
    if math.ceil(x) == x then
       return math.ceil(x);
    else
       return math.ceil(x) - 1;
    end
end

function GetTtileBuff(id)
	if id >96 or id < 1 then
		return 0,0,0,0
	end
	return titleinfo[id][3],titleinfo[id][4],titleinfo[id][5],titleinfo[id][6],titleinfo[id][7],titleinfo[id][8],titleinfo[id][9],titleinfo[id][10],titleinfo[id][11]
end

function FreeComplianceParameter( charaindex )
	if char.getInt(charaindex, "類型") == 3 then
		local data= char.getChar(charaindex,"祝福狀態")
		if data~="" then
			local hp = other.atoi(other.getString(data, "|", 1))
			local at = other.atoi(other.getString(data, "|", 2))
			local df = other.atoi(other.getString(data, "|", 3))
			local dx = other.atoi(other.getString(data, "|", 4))

			char.setWorkInt(charaindex, "最大HP", char.getWorkInt(charaindex, "最大HP") + hp)
			char.setWorkInt(charaindex, "攻擊力", char.getWorkInt(charaindex, "攻擊力") + at)
			char.setWorkInt(charaindex, "防禦力", char.getWorkInt(charaindex, "防禦力") + df)
			char.setWorkInt(charaindex, "敏捷力", char.getWorkInt(charaindex, "敏捷力") + dx)

		end
	end



	if char.getInt(charaindex, "類型") == 1 then
		local itemindex =  char.getItemIndex(charaindex,6)
		if itemindex > 0 then
			local data1 = item.getChar(itemindex, "字段")
			local attrate = other.atoi(other.getString(data1, "|", 1))
			local defrate = other.atoi(other.getString(data1, "|", 2))
			local dexrate = other.atoi(other.getString(data1, "|", 3))
			char.setWorkInt(charaindex, "攻擊力", math.floor(char.getWorkInt(charaindex, "攻擊力") * (100+attrate)/100))
			char.setWorkInt(charaindex, "防禦力", math.floor(char.getWorkInt(charaindex, "防禦力") * (100+defrate)/100))
			char.setWorkInt(charaindex, "敏捷力", math.floor(char.getWorkInt(charaindex, "敏捷力") * (100+dexrate)/100))
			char.setWorkInt(charaindex, "最大HP", char.getWorkInt(charaindex, "最大HP") + 150)
		end

		for i = 1,96 do
			if char.getCharNewTitleMode(charaindex,i-1)== 1 then
				temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9 = GetTtileBuff(i)
				addhp = addhp + temp1
				addat = addat + temp2
				adddf = adddf + temp3
				adddx = adddx + temp4
				addpo = addpo + temp5
				addpa = addpa + temp6
				addsl = addsl + temp7
				addst = addst + temp8
				addco = addco + temp9
			end
		end
		char.setWorkInt(charaindex, "最大HP", char.getWorkInt(charaindex, "最大HP") + addhp)
		char.setWorkInt(charaindex, "攻擊力", char.getWorkInt(charaindex, "攻擊力") + addat)
		char.setWorkInt(charaindex, "防禦力", char.getWorkInt(charaindex, "防禦力") + adddf)
		char.setWorkInt(charaindex, "敏捷力", char.getWorkInt(charaindex, "敏捷力") + adddx)
		char.setWorkInt(charaindex, "毒抗附加", addpo)
		char.setWorkInt(charaindex, "麻抗附加", addpa)
		char.setWorkInt(charaindex, "睡抗附加", addsl)
		char.setWorkInt(charaindex, "石抗附加", addst)
		char.setWorkInt(charaindex, "混抗附加", addco)

	end

end

function data()
	titleinfo =	{	--描述 序號 體 攻 防 敏 毒 麻 睡 石 混
				 {"大地的精靈 防+5",1,0,0,5,0,0,0,0,0,0}
				,{"水的精靈 HP+20",2,20,0,0,0,0,0,0,0,0}
				,{"火炎的精靈 攻+5",3,0,5,0,0,0,0,0,0,0}
				,{"疾風的精靈 敏+5",4,0,0,0,5,0,0,0,0,0}
				,{"奧蘿拉的精靈 全+1",5,1,1,1,1,0,0,0,0,0}
				,{"彩虹的精靈 全+2",6,2,2,2,2,0,0,0,0,0}
				,{"初心使者 HP+10",7,10,0,0,0,0,0,0,0,0}
				,{"無名的旅人 全+2",8,2,2,2,2,0,0,0,0,0}
				,{"路邊的落葉 全+4",9,4,4,4,4,0,0,0,0,0}
				,{"水麵的小草 全+6",10,6,6,6,6,0,0,0,0,0}
				,{"呢喃的歌聲 全+8",11,8,8,8,8,0,0,0,0,0}
				,{"地上的月影 全+10",12,10,10,10,10,0,0,0,0,0}
				,{"奔跑的春風 全+12",13,12,12,12,12,0,0,0,0,0}
				,{"蒼穹的風雲 全+14",14,14,14,14,14,0,0,0,0,0}
				,{"搖曳的金星 全+16",15,16,16,16,16,0,0,0,0,0}
				,{"歡喜的慈雨 全+18",16,18,18,18,18,0,0,0,0,0}
				,{"蘊含的太陽 全+20",17,20,20,20,20,0,0,0,0,0}
				,{"敬畏的寂靜 全+30",18,30,30,30,30,0,0,0,0,0}
				,{"精`封印者 攻+5",19,0,5,0,0,0,0,0,0,0}
				,{"五轉輪迴 防+20",20,0,0,20,0,0,0,0,0,0}
				,{"盜賊討伐者 攻+5",21,0,5,0,0,0,0,0,0,0}
				,{"盜賊幫眾 混亂抗性+5",22,0,0,0,0,0,0,0,0,5}
				,{"奪寶奇兵 石化抗性+5",23,0,0,0,0,0,0,0,5,0}
				,{"勇闖奪寶島 睡抗性+5",24,0,0,0,0,0,0,5,0,0}
				,{"閤成達人 敏+5",25,0,0,0,5,0,0,0,0,0}
				,{"閤成高手 敏+3",26,0,0,0,3,0,0,0,0,0}
				,{"練寵達人 攻+5",27,0,5,0,0,0,0,0,0,0}
				,{"練寵高手 攻+3",28,0,3,0,0,0,0,0,0,0}
				,{"任務達人 防+5",29,0,0,5,0,0,0,0,0,0}
				,{"任務高手 防+3",30,0,0,3,0,0,0,0,0,0}
				,{"初犢戰士 HP+10",31,10,0,0,0,0,0,0,0,0}
				,{"聖靈勇士 HP+15",32,15,0,0,0,0,0,0,0,0}
				,{"瑪麗那絲英雄 HP+20",33,20,0,0,0,0,0,0,0,0}
				,{"薩姆吉爾英雄 HP+25",34,25,0,0,0,0,0,0,0,0}
				,{"薩伊那斯使者 HP+30",35,30,0,0,0,0,0,0,0,0}
				,{"尼斯大陸英雄 HP+100",36,100,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				,{"","",0,0,0,0,0,0,0,0,0}
				}




end

function main()
	data()
end
