--此LUA是離綫判斷時間和扣除時間還有下綫後記錄上一次在綫期間産生的個人信息!
function getIntPart(x)
    if x <= 0 then
       return math.ceil(x);
    end

    if math.ceil(x) == x then
       x = math.ceil(x);
    else
       x = math.ceil(x) - 1;
    end
    return x;
end

function FreeCharLogout( charindex )
	if char.getWorkInt(charindex, "離綫") == 1 then
		--if char.getWorkInt(charindex, "擺攤") == -1 then
		--	if config.getGameservername() ~= "零九石器二綫" and config.getGameservername() ~= "零九石器三綫" then
		--		local offtime = other.time() - char.getWorkInt(charindex, "登陸時間")
		--		char.setInt(charindex, "離綫時間", math.max(char.getInt(charindex, "離綫時間") - offtime / 60), 0)
		--	end
		--end
		other.setLuaPLayerNum(other.getLuaPLayerNum()-1)
	else
		local offtime = other.time() - char.getWorkInt(charindex, "登陸時間")
		if char.getInt(charindex, "等級") == 140 then
			local onlinetime = char.getInt(charindex, "下綫時間") - char.getWorkInt(charindex, "登陸時間")
			if char.getInt(charindex, "轉數") == 5 then
				char.setInt(charindex, "在綫時間", char.getInt(charindex, "在綫時間") + getIntPart(onlinetime / 2) )
			elseif char.getInt(charindex, "轉數") == 6 then
				char.setInt(charindex, "在綫時間", char.getInt(charindex, "在綫時間") + onlinetime)
			end
		end
	end
	
	--if config.getGameservername() == "零九石器單綫" then
	--	token = "DELETE FROM `OnlinePlayer` "
	--										.. " WHERE `cdkey` = '" .. char.getChar(charindex, "賬號") .. "'"
	--	ret = sasql.query(token)
	--end
	
	token = "SELECT * FROM `CSAinfo` "
										.. " WHERE `cdkey` = '" .. char.getChar(charindex, "賬號") .. "'"
										.. " AND `saveindex` = '" .. char.getInt(charindex, "存檔") .. "'"
	ret = sasql.query(token)
	if ret == 1 then
		sasql.free_result()
		sasql.store_result()
		num = sasql.num_rows()
		if num > 0 then
			token = "UPDATE `CSAinfo` SET "
						.. "`name` = '" .. char.getChar(charindex, "名字") .. "',"
						.. "`famename` = '"  .. char.getChar(charindex, "傢族") .. "', "
						.. "`level` = '"  .. char.getInt(charindex, "等級") .. "',"
						.. "`trans` = '"  .. char.getInt(charindex, "轉數") .. "',"
						.. "`alive` = '"  .. char.getInt(charindex, "活力") .. "',"
						.. "`fame` = '"  .. char.getInt(charindex, "聲望") .. "',"
						.. "`TITLE_LV` = '"  .. 0 .. "',"
						.. "`DUELBATTLECOUNT` = '" .. char.getInt(charindex, "PK次數") .. "',"
						.. "`DUELWINCOUNT` = '" .. char.getInt(charindex, "PK贏數") .. "',"
						.. "`DUELLOSECOUNT` = '" .. char.getInt(charindex, "PK敗數") .. "',"
						.. "`DUELSTWINCOUNT` = '" .. char.getInt(charindex, "PK連勝") .. "',"
						.. "`DUELSTLOSECOUNT` = '" .. char.getInt(charindex, "PK連敗") .. "',"
						.. "`DUELMAXSTWINCOUNT` = '" .. char.getInt(charindex, "PK最高連勝") .. "',"
						.. "`vip` = '"  .. char.getInt(charindex, "會員") .. "',"
						.. "`time` = NOW()"
						.. " WHERE `cdkey` = '" .. char.getChar(charindex, "賬號") .. "'"
						.. " AND `saveindex` = '" .. char.getInt(charindex, "存檔") .. "'"
			ret = sasql.query(token)
		else
			token = "INSERT INTO `CSAinfo` ( "
							.. "`cdkey` ,"
							.. "`saveindex` ,"
							.. "`name` ,"
							.. "`famename` ,"
							.. "`level` ,"
							.. "`trans` ,"
							.. "`alive` ,"
							.. "`fame` ,"
							.. "`TITLE_LV` ,"
							.. "`DUELBATTLECOUNT` ,"
							.. "`DUELWINCOUNT` ,"
							.. "`DUELLOSECOUNT` ,"
							.. "`DUELSTWINCOUNT` ,"
							.. "`DUELSTLOSECOUNT` ,"
							.. "`DUELMAXSTWINCOUNT` ,"
							.. "`vip` ,"
							.. "`time`"
							.. ")"
							.. "VALUES ("
							.. "'" .. char.getChar(charindex, "賬號")
							.. "', '" .. char.getInt(charindex, "存檔")
							.. "', '" .. char.getChar(charindex, "名字")
							.. "', '"  .. char.getChar(charindex, "傢族")
							.. "', '"  .. char.getInt(charindex, "等級")
							.. "', '"  .. char.getInt(charindex, "轉數")
							.. "', '"  .. char.getInt(charindex, "活力")
							.. "', '"  .. char.getInt(charindex, "聲望")
							.. "', '"  .. char.getInt(charindex, "英雄稱號")
							.. "', '"  .. char.getInt(charindex, "PK次數")
							.. "', '"  .. char.getInt(charindex, "PK贏數")
							.. "', '"  .. char.getInt(charindex, "PK敗數")
							.. "', '"  .. char.getInt(charindex, "PK連勝")
							.. "', '"  .. char.getInt(charindex, "PK連敗")
							.. "', '"  .. char.getInt(charindex, "PK最高連勝")
							.. "', '"  .. char.getInt(charindex, "會員")
							.. "', NOW()"
							.. ");"

			ret = sasql.query(token)
		end
	end
	token = "update `CSAlogin` set `Offline`=0 where `Name`='" .. char.getChar(charindex,"賬號") .. "'"
	sasql.query(token)
	
end

function data()

end

function main()
	data()
end
