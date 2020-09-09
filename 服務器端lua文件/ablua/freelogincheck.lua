--登錄過程讀取和驗證
function FreeLoginCheck(fd)
	local mun = 0
	local maxnum = 0
	local maxplayer = config.getFdnum() - 1
	local mac = net.getMac(fd)
	local ip = net.getIP(fd)

	if mac == "" then
		lssproto.CharList(fd, "由於你使用非本服的認可的程序進入遊戲，所以禁止你的登陸！")
		return 0
	end
	if string.len(mac) < 32 then
		lssproto.CharList(fd, "由於你使用非本服的認可的程序進入遊戲，所以禁止你的登陸！")
		return 0
	end
	local key = other.getString(mac, "-", 1)
	if key ~= "ver100" then
		lssproto.CharList(fd, "由於你的版本過舊，請更新後再進入遊戲！")
		return 0
	end

	local mainmac = other.getString(mac, "-", 2)

	maxnum = 2
	for i = 5, maxplayer do
		if net.getUse(i) == 1 then
			if mac == net.getMac(i) then
				mun = mun + 1
				if mun > maxnum then
					lssproto.CharList(fd, "你的遊戲賬號登陸已以達" .. mun - 1 .. "個，請不要過量進入遊戲！")
					return 0
				end
			end
		end
	end

	token = "SELECT count(*) FROM `CSAlogin` "
					.. " WHERE `MAC` = '" .. mac .. "' and `Online` > 0"
	ret = sasql.query(token)
	local totalnum = 1
	if ret == 1 then
		sasql.free_result()
		sasql.store_result()
		num = sasql.num_rows()
		if num > 0 then
			sasql.fetch_row(0)
			onlinenum = other.atoi(sasql.data(1))
			if onlinenum > totalnum then
				lssproto.CharList(fd, "您的遊戲登錄賬號數量已達上限，請不要過量進入遊戲。")
				return 0
			end
		end
	end

	return 1
end

function CheckNologin(mac)
	for j=1,table.getn(nologin) do
		if mac==nologin[j] then
			return 1
		end
	end
	return 0
end

function data()


end

function main()
	data()
end
