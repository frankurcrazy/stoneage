function GetCharNewTitleNo(charaindex,id)
	if char.check(charaindex)~=1 then
		return 0
	end
	if id< 32 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態1"),id)~= 0 then
			return titleinfo[id+1][2]
		end
	elseif id< 64 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態2"),id-32)~= 0 then
			return titleinfo[id+1][2]
		end
	elseif id< 96 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態3"),id-64)~= 0 then
			return titleinfo[id+1][2]
		end
	end
	return 0
end

function GetCharNewTitleString(charaindex,id)
	if char.check(charaindex)~=1 then
		return 0
	end
	if id< 32 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態1"),id)~= 0 then
			return titleinfo[id+1][2]
		end
	elseif id< 64 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態2"),id-32)~= 0 then
			return titleinfo[id+1][2]
		end
	elseif id< 96 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態3"),id-64)~= 0 then
			return titleinfo[id+1][2]
		end
	end
	return ""
end


function GetCharNewTitleName(charaindex,id)
	if char.check(charaindex)~=1 then
		return 0
	end

	if id< 32 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態1"),id)~= 0 then
			return titleinfo[id+1][1]
		end
	elseif (id >=32 and id< 64) then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態2"),id-32)~= 0 then
			return titleinfo[id+1][1]
		end
	elseif(id >=64 and id< 96) then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態3"),id-64)~= 0 then
			return titleinfo[id+1][1]
		end
	end
	return ""
end

function GetCharNewTitleMode(charaindex,id)
	if char.check(charaindex)~=1 then
		return 0
	end

	if id< 32 then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態1"),id)~= 0 then
			return 1
		end
	elseif (id >=32 and id< 64) then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態2"),id-32)~= 0 then
			return 1
		end
	elseif(id >=64 and id< 96) then
		if other.DataAndData(char.getInt(charaindex,"稱號狀態3"),id-64)~= 0 then
			return 1
		end
	end
	return 0
end

function TitleListSend(charaindex)
	if char.check(charaindex)~=1 then
		return
	end
	local Nodata=""
	local jiedata=""
	local indexdata=""
	local num=0
	local fd = char.getFd(charaindex)
	for i = 1,96 do
		if GetCharNewTitleMode(charaindex,i-1)>0 then
			num = num + 1
--			print(num, GetCharNewTitleMode(charaindex,i-1))
			Nodata = Nodata..GetCharNewTitleString(charaindex,i-1).."|"
			jiedata = jiedata..GetCharNewTitleName(charaindex,i-1).."|"
			indexdata = indexdata..(i-1).."|"
		end
	end
	local data = string.format("%d|%d#@%s#@%s#@%s#@",char.getInt(charaindex,"文字稱號"),num,Nodata,jiedata,indexdata)
	lssproto.CharTitleSend(fd,data)
--	print("CharTitleSend發送成功！"..data.."\n")
end

function GetTtileBuff(id)
	if id >96 or id < 1 then
		return 0,0,0,0
	end
	return titleinfo[id][3],titleinfo[id][4],titleinfo[id][5],titleinfo[id][6]
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
	data();
end
