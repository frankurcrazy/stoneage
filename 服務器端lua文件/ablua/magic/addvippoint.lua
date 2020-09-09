function addvip(charaindex, data)
	local value = other.atoi(other.getString(data, " ", 1))
	local cdkey = other.getString(data, " ", 2)
	if cdkey == "" then
		local oldvalue = sasql.getVipPoint(charaindex)
		sasql.setVipPoint(charaindex, sasql.getVipPoint(charaindex) + value)
		char.TalkToCli(charaindex, -1, "成功將賬號[" .. char.getChar(charaindex, "賬號") .. "]名字[" .. char.getChar(charaindex, "名字") .. "]個人會員點原" .. oldvalue .. "增到為" .. sasql.getVipPoint(charaindex), "青色")
	else
		local maxplayer = char.getPlayerMaxNum()
		local cimelia = other.atoi(data)
		for i = 0, maxplayer - 1 do
			if char.check(i) == 1 then
				if char.getChar(i, "賬號") ==  cdkey then
					local oldvalue = sasql.getVipPoint(i)
					sasql.setVipPoint(i, sasql.getVipPoint(i) + value)
					char.TalkToCli(charaindex, -1, "成功將賬號[" .. char.getChar(i, "賬號") .. "]名字[" .. char.getChar(i, "名字") .. "]個人會員點原" .. oldvalue .. "增到為" .. sasql.getVipPoint(i), "青色")
					char.TalkToCli(i, -1, "GM[" .. char.getChar(charaindex, "名字") .. "]將你的個人會員點原" .. oldvalue .. "增到為" .. sasql.getVipPoint(i), "青色")
					return
				end
			end
		end
	end
end

function main()
	minute = 0
	magic.addLUAListFunction("會員點", "addvip", "", 1, "[]")
end

