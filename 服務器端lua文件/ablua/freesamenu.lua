function FreeSaMenu(meindex, index)
--	char.TalkToCli(meindex, -1, char.getWorkInt(meindex,"NPC臨時3"), "綠色")
	local 戰模 = char.getWorkInt(meindex,"戰鬥");
	parameter = {meindex}
	if index == 11 then
		if 戰模 ==0 then
			char.Encounter(meindex)
			char.TalkToCli(meindex, -1, "開啓原地遇敵！", "紅色")
		else
			char.TalkToCli(meindex, -1, "您已經戰鬥中！", "紅色")
		end
	elseif index == 12 then
		char.ClearEncounter(meindex);
		char.TalkToCli(meindex, -1, "關閉原地遇敵！", "紅色")
	elseif index == 13 then
		if 戰模 == 0 then
			other.CallFunction("CheckTalked", "data/ablua/npc/check/check.lua", parameter)
		end
	--	other.CallFunction("ShowHead", "data/ablua/npc/vipshop/vipshop.lua", parameter)
	elseif index == 14 then
			other.CallFunction("QueryMissionTalked", "data/ablua/npc/querymission/querymission.lua", parameter)
	elseif index == 16 then
		other.CallFunction("FreeDataInfoShow", "data/ablua/freedatainfoshow.lua", parameter)
	elseif index == 17 then
		lssproto.SaMenu(meindex, index, "http://www.stoneage.es")
	elseif index == 18 then
		lssproto.SaMenu(meindex, index, "http://www.stoneage.es/forum.php")
	elseif index == 19 then
		lssproto.SaMenu(meindex, index, "http://www.stoneage.es/pay.php")
	elseif index == 20 then
		char.setWorkInt(meindex,"NPC臨時3",1)
		other.CallFunction("OnlineService", "data/ablua/npc/onlineservice/onlineservice.lua", parameter)
	elseif index == 21 then
		lssproto.SaMenu(meindex, index, "http://www.stoneage.es/forum.php?mod=viewthread&tid=54&extra=page%3D1")
	elseif index == 22 then
		lssproto.SaMenu(meindex, index, "http://www.stoneage.es/bbs/forum.php?mod=viewthread&tid=226")
	elseif index == 30 then--切換隊長
		if char.getWorkInt(meindex, "組隊") == 1 then
			轉移動伍[meindex]={};
			local 隊員名 = "";
			local 計數=0;
			for i=1,4 do
				local 隊員索引 = char.getWorkInt(meindex, "隊員" .. i+1)
				if char.check(隊員索引) == 1 then
					計數 = 計數 + 1;
					轉移動伍[meindex][計數] = 隊員索引;
					隊員名 = string.format("%s        %s\n",隊員名,char.getChar(轉移動伍[meindex][計數],"名字"));
				end
			end
			local 內容 = "1 						請選擇新的隊長\n"..隊員名;
			lssproto.windows(meindex, 2, 8, 0, char.getWorkInt( npcindex, "對象"), 內容)
		else
			char.TalkToCli(meindex, -1, "該功能需要隊長權限", "紅色")
		end
	else
		char.TalkToCli(meindex, -1, "暫未開放", "紅色")
	end
end


function WindowTalked( NPC索引, 玩傢索引, 序號, 按鈕, 數據)
	if 序號 == 0 then
		local 選項 = tonumber(數據);
		if 選項 > 0 and 選項 < 5 then
			char.DischargeParty(玩傢索引,0);
			char.JoinParty(轉移動伍[玩傢索引][選項],玩傢索引,0);
			char.TalkToCli(轉移動伍[玩傢索引][選項], -1, "您的隊友【"..char.getChar(玩傢索引,"名字").."】把隊長權力交給您！", "黃色")
			char.TalkToCli(玩傢索引, -1, "您成功把隊長權力交給隊友【"..char.getChar(轉移動伍[玩傢索引][選項],"名字").."】", "黃色");
			for i =1,table.getn(轉移動伍[玩傢索引]) do
				if i ~= 選項 then
					char.JoinParty(轉移動伍[玩傢索引][選項],轉移動伍[玩傢索引][i],0);
				end
			end
			char.Encounter(轉移動伍[玩傢索引][選項])
		end
	end
end

function Create(name, metamo, floor, x, y, dir)
	npcindex = npc.CreateNpc(name, metamo, floor, x, y, dir)
	char.setFunctionPointer(npcindex, "窗口事件", "WindowTalked", "")
end

function data()
 轉移動伍={};
--[[

11 原地遇敵
12 取消原地
13 支票製作
14 任務查詢
16 個人信息
20 卡密使用
21 任務攻略
22 新手幫助


]]


end

function main()
	data()
	Create("查詢寵物NPC臨時", 100000, 777, 20, 21, 4);
end

