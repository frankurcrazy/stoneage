記錄道具記錄={};


function WindowTalked ( meindex, charaindex, seqno, select, data)
	if seqno == 1 then
		local 寵物位置 = other.atoi(data);
		if 寵物位置 >=1 and 寵物位置<=4 then
			local 寵物索引 = char.getCharPet(charaindex, 寵物位置-1);
			if char.check(寵物索引) == 1 then
				記錄道具記錄[charaindex][3] = 寵物索引;
				local 對話內容 = "是否讓 "..char.getChar(寵物索引,"名字") .." 學習該特效！"
				lssproto.windows(charaindex, "對話框", "確定|取消", 2,  char.getWorkInt( npcindex, "對象"),對話內容 )
			end
		end
	elseif seqno == 2 then
		if select == 1 then
			local 攻擊特效ID = other.atoi(item.getChar(記錄道具記錄[charaindex][1], "字段"))
			char.setInt(記錄道具記錄[charaindex][3],"攻擊特效",攻擊特效ID);
			char.DelItem(charaindex, 記錄道具記錄[charaindex][2]);
			char.TalkToCli(charaindex, -1, "您的寵物"..char.getChar(記錄道具記錄[charaindex][3],"名字").."習得攻擊特效,快去體驗吧！", "紅色")
			記錄道具記錄[charaindex]=nil;
		end
	end
end

function attackeffect(itemindex, charaindex, toindex, haveitemindex)
	記錄道具記錄[charaindex]={};
	記錄道具記錄[charaindex][1]=itemindex;
	記錄道具記錄[charaindex][2]=haveitemindex;
	lssproto.windows(charaindex, "寵物框", "確定", 1,  char.getWorkInt( npcindex, "對象"), "")
end

function Create(name, metamo, floor, x, y, dir)
	--創建NPC(NPC名字，圖像號，地圖號，坐標X，坐標Y，方嚮號)將返迴一個NPC索引
	npcindex = npc.CreateNpc(name, metamo, floor, x, y, dir)
	char.setFunctionPointer(npcindex, "窗口事件", "WindowTalked", "")
end


function data()
end

function main()
	Create("攻擊特效NPC",100000,777,20,20,3);

	item.addLUAListFunction( "ITEM_ATTACKEFFECT", "attackeffect", "")
end
