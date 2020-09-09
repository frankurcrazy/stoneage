local 傢族徽章數據={};
local 徽章內容="";



function 字符串切割(數據,切割字符)
	數據 = 數據 .. 切割字符
	local t = {}
	local 目前位置 = 1
	repeat
			local nexti = string.find(數據, 切割字符, 目前位置)
			table.insert(t, string.sub(數據, 目前位置,nexti-string.len(切割字符)))
			目前位置 = nexti + string.len(切割字符)
	until 目前位置 > string.len(數據)
	return t
end


function LoadFamilyBadge(fd)
	lssproto.FamilyBadge(fd,徽章內容);
end

function 讀取傢族徽章數據()
	local 文件號;
	local 數據,數量;
	文件號 = assert(io.open("./data/ablua/other/familybadge/data.txt", "r"))
	數據 = 文件號:read("*a"); -- 讀取所有內容
	文件號:close();
	徽章內容 = 換徽章價格.."|"
	if 數據 ~= "" then
		數量 = 0;
		數據 = 字符串切割(數據,"\n");
		for b = 1,table.getn(數據) do 
			if string.sub(數據[b],1,1) ~= "#" then
				數量 = 數量 + 1;
				傢族徽章數據[數量] = tonumber(數據[b]);
			end
		end
		for b=1,table.getn(傢族徽章數據) do 
			if b~=table.getn(傢族徽章數據) then
				徽章內容 = 徽章內容 .. 傢族徽章數據[b].."|";
			else
				徽章內容 = 徽章內容 .. 傢族徽章數據[b];
			end
		end
	end
end

function main()
	換徽章價格=1000;
	讀取傢族徽章數據();
	lssproto.GetFBData(傢族徽章數據,換徽章價格);
end
main();

