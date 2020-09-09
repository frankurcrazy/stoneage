function addpay(charaindex, data)
	local value = other.atoi(other.getString(data, " ", 1))
	local cdkey = other.getString(data, " ", 2)
	if cdkey == "" then
		local oldvalue = sasql.getPayPoint(charaindex)
		sasql.setPayPoint(charaindex, sasql.getPayPoint(charaindex) + value)
		char.TalkToCli(charaindex, -1, "成功將賬號[" .. char.getChar(charaindex, "賬號") .. "]名字[" .. char.getChar(charaindex, "名字") .. "]個人充值積分原" .. oldvalue .. "增到為" .. sasql.getPayPoint(charaindex), "青色")
	else
		local maxplayer = char.getPlayerMaxNum()
		local cimelia = other.atoi(data)
		for i = 0, maxplayer - 1 do
			if char.check(i) == 1 then
				if char.getChar(i, "賬號") ==  cdkey then
					local oldvalue = sasql.getPayPoint(i)
					sasql.setPayPoint(i, sasql.getPayPoint(i) + value)
					char.TalkToCli(charaindex, -1, "成功將賬號[" .. char.getChar(i, "賬號") .. "]名字[" .. char.getChar(i, "名字") .. "]個人充值積分原" .. oldvalue .. "增到為" .. sasql.getPayPoint(i), "青色")
					char.TalkToCli(i, -1, "GM[" .. char.getChar(charaindex, "名字") .. "]將你的個人充值積分原" .. oldvalue .. "增到為" .. sasql.getPayPoint(i), "青色")
					return
				end
			end
		end
	end
end

function main()
	minute = 0
	magic.addLUAListFunction("充值積分", "addpay", "", 1, "[]")
end

