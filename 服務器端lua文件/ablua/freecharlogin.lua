function FreeCharLogin( charindex )
	if char.getWorkInt(charindex, "服務器ID") == 48 then
		char.TalkToCli(charindex, -1, "版本過期，請更新最新的脫機外掛後登陸遊戲。", "黃色")
		char.logou(charindex)
		return 0;
	end
	if char.getWorkInt(charindex, "服務器ID") == 4096 and config.getGameservername() == "石器重製版單號綫" then
		char.TalkToCli(charindex, -1, "進單號綫提示【為瞭遊戲的平衡，單號綫路隻能用外掛登陸】", "黃色")
		char.logou(charindex)
		return 0;
	end
	for i = 1, table.getn(unlawthislogut) do
		if char.getInt(charindex, "計時器") <= other.time() then
			if char.getInt(charindex, "地圖號") == unlawthislogut[i][1] then
				char.setInt(charindex, "地圖號", unlawthislogut[i][2][1] )
				char.setInt(charindex, "坐標X", unlawthislogut[i][2][2] )
				char.setInt(charindex, "坐標Y", unlawthislogut[i][2][3] )
			end
		end
	end
	if char.getInt(charindex, "地圖號") >=800 and char.getInt(charindex, "地圖號") <=851 then
		char.WarpToSpecificPoint(charindex, 1000, 71, 49)
	end

	if char.getInt(charindex, "地圖號") == 500 then
		if char.getInt(charindex, "等級")< 80 then
			char.WarpToSpecificPoint(charindex, 1000, 71, 49)
		end
	end
	if char.getInt(charindex,"傢族地位")>0 and char.getInt(charindex,"傢族地位")~=2  then
		if char.getChar(charindex, "傢族") == other.getString(family.ShowPointListArray(0), "|", 6) then
			char.setWorkInt(charindex,"莊園特效",103213)
		elseif char.getChar(charindex, "傢族") == other.getString(family.ShowPointListArray(1), "|", 6) then
			char.setWorkInt(charindex,"莊園特效",103214)
		end
	end
	if char.getInt(charindex, "離綫時間") < 0 then
		char.setInt(charindex, "離綫時間", 0)
	end

	if char.getInt(charindex, "極品") ~=1 then
		local vital = char.getInt(charindex, "體力")
		local str = char.getInt(charindex, "腕力")
		local tgh = char.getInt(charindex, "耐力")
		local dex = char.getInt(charindex, "速度")
		local skillpoint = char.getInt(charindex, "技能點")
		local sum = vital + str + tgh + dex + skillpoint * 100
		if sum > 63700 then
			char.setInt(charindex, "體力", 1000)
			char.setInt(charindex, "腕力", 0)
			char.setInt(charindex, "耐力", 0)
			char.setInt(charindex, "速度", 0)
			char.setInt(charindex, "技能點", 627)
		end
	else
		local vital = char.getInt(charindex, "體力")
		local str = char.getInt(charindex, "腕力")
		local tgh = char.getInt(charindex, "耐力")
		local dex = char.getInt(charindex, "速度")
		local skillpoint = char.getInt(charindex, "技能點")
		local sum = vital + str + tgh + dex + skillpoint * 100
		if sum > 61000 then
			char.setInt(charindex, "體力", 1000)
			char.setInt(charindex, "腕力", 0)
			char.setInt(charindex, "耐力", 0)
			char.setInt(charindex, "速度", 0)
			char.setInt(charindex, "技能點", 600)
		end
	end

	token = "UPDATE CSAlogin set Offline = 0 , MAC = '" .. char.getWorkChar(charindex, "MAC") .. "', ServerName = '" .. config.getGameservername() .. "', ServerId = " .. char.getWorkInt(charindex, "服務器ID") + 1 .. " WHERE Name=BINARY'" .. char.getChar(charindex, "賬號") .. "'"

	ret = sasql.query(token)
	token = "SELECT `newsafe`, `flg` FROM `safedata` "
				.. " WHERE `cdkey` = '" .. char.getChar(charindex, "賬號") .. "'"
	ret = sasql.query(token)
	if ret == 1 then
		sasql.free_result()
		sasql.store_result()
		num = sasql.num_rows()
		if num > 0 then
			sasql.fetch_row(0)
			if sasql.data(1) ~= char.getWorkChar(charindex, "MAC2") then
				if sasql.data(2) == "0" then
					char.setInt(charindex, "安全鎖", 2)
				end
				token = "UPDATE `safedata` SET "
							.. "`newsafe` = '" .. char.getWorkChar(charindex, "MAC2") .. "',"
							.. "`oldsafe` = '" .. sasql.data(1) .. "',"
							.. "`FixTime` = NOW()"
							.. " WHERE `cdkey` = '" .. char.getChar(charindex, "賬號") .. "'"
				ret = sasql.query(token)
			end
		else
			token = "INSERT INTO `safedata` ( "
							.. "`cdkey` ,"
							.. "`newsafe` ,"
							.. "`oldsafe` ,"
							.. "`flg`,"
							.. "`FixTime`"
							.. ")"
							.. " VALUES ("
							.. "'" .. char.getChar(charindex, "賬號")
							.. "', '" .. char.getWorkChar(charindex, "MAC2")
							.. "', '" .. char.getWorkChar(charindex, "MAC2")
							.. "', 0, NOW()"
							.. ");"
			ret = sasql.query(token)
		end
	end

	return 1;
end


function data()

	unlawthislogut = {{125, {1000, 92, 99}}
									 ,{126, {1000, 92, 99}}
									 ,{127, {1000, 92, 99}}
									 ,{128, {1000, 92, 99}}
									 ,{140, {141, 25, 17}}
									 ,{8190, {2000, 44, 67}}
									 ,{12345, {1000, 92, 99}}
									 ,{40001, {1000, 92, 99}}
									 ,{40002, {1000, 92, 99}}
									 ,{40003, {1000, 92, 99}}
									 ,{40004, {1000, 92, 99}}
									 ,{40005, {1000, 92, 99}}
									 ,{40006, {1000, 92, 99}}
									 ,{40007, {1000, 92, 99}}
									 ,{40008, {1000, 92, 99}}
									 ,{40009, {1000, 92, 99}}
									 ,{40010, {1000, 92, 99}}
									 ,{50001, {1000, 92, 99}}
									 ,{50002, {1000, 92, 99}}
									 ,{50003, {1000, 92, 99}}
									 ,{50004, {1000, 92, 99}}
									 ,{104, 	{1000, 92, 99}}
									 ,{133, 	{1000, 92, 99}}
									 ,{130, 	{1000, 92, 99}}
									 ,{602, 	{1000, 92, 99}}
									 ,{61001, 	{1000, 92, 99}}
									 ,{65501, 	{1000, 92, 99}}
									 ,{50005, 	{1000, 92, 99}}
									 }
end

function main()
	data()
end
