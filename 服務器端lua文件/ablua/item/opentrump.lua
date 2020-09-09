function opentrump(itemindex, charaindex, toindex, haveitemindex)

	if char.getInt(charaindex,"法寶狀態")>0 then
		char.TalkToCli(charaindex, -1,"您已經開啓瞭法寶裝備欄!", "黃色")
		return
	end
	char.DelItem(charaindex, haveitemindex)
	char.setInt(charaindex,"法寶狀態",1);
	char.UpCahrData(charaindex,"p");
	char.TalkToCli(charaindex, -1,"您的法寶裝備欄已成功開啓!", "黃色")
end

function main()
	item.addLUAListFunction( "ITEM_OPENTRUMP", "opentrump", "")
end
