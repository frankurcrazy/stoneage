function useitemmax(itemindex, charaindex, toindex, haveitemindex)

	local data = other.atoi(item.getChar(itemindex, "字段"))
	if (char.getInt(charaindex,"道具欄狀態")~=2 and data == 3)
		or (char.getInt(charaindex,"道具欄狀態")~=0 and data == 2) then
		char.TalkToCli(charaindex, -1,"請用相對應的擴展道具來擴展包裹！", "紅色")
		return
	end
	if char.getInt(charaindex,"道具欄狀態") == 2 then
		char.setInt(charaindex,"道具欄狀態",6);
		char.DelItem(charaindex, haveitemindex)
		char.TalkToCli(charaindex, -1,"恭喜您開啓第三欄道具欄!", "黃色")
		char.UpCahrData(charaindex,"p");
	elseif char.getInt(charaindex,"道具欄狀態") == 6 then
		char.TalkToCli(charaindex, -1,"您已經全部開放瞭!", "黃色")
	else
		char.DelItem(charaindex, haveitemindex)
		char.setInt(charaindex,"道具欄狀態",2);
		char.TalkToCli(charaindex, -1,"恭喜您開啓第二欄道具欄!", "黃色")
		char.UpCahrData(charaindex,"p");
	end
end

function main()
	item.addLUAListFunction( "ITEM_USEITEMMAX", "useitemmax", "")
end
