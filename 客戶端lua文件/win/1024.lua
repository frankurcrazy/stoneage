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

function lua_string_split(str, split_char)
    local sub_str_tab = {};
    while (true) do
        local pos = string.find(str, split_char);
        if (not pos) then
            sub_str_tab[#sub_str_tab + 1] = str;
            break;
        end
        local sub_str = string.sub(str, 1, pos - 1);
        sub_str_tab[#sub_str_tab + 1] = sub_str;
        str = string.sub(str, pos + 1, #str);
    end

    return sub_str_tab;
end

function WindowInit(strdata)
	winW = 6
	winH = 4
	winX = (800 - winW*64)/4
	winY = (600 - winH*48)/4
	if addr ~= 0 then
		sa.DeathAction(addr)
		addr = 0
	end
	data()
	vippoint = tonumber(strdata);
	win.InitStrBuffer(winX + 180,winY + 180,6,0,1);

end

function CreateWinType()
	if addr == 0 then
		addr = sa.MakeWindowDisp(winX,winY,winW, winH, 0, 1)
	end
	sa.PlaySe(202, 320, 240)
	return addr;
end

function ServerWindowType()
	win.SetInputMsgNum()

	sa.StockFontBuffer(winX + 230,winY + 80, 1, 10, "【發紅包】", 0)
	local id ;
	local color={};

	local posy = 0

	sa.StockFontBuffer(winX + 100,winY + 100 + posy, 1, 0, "當前金幣：", 0)

	sa.StockFontBuffer(winX + 180,winY + 100 + posy, 1, 0,"".. vippoint, 0);

	sa.StockFontBuffer(winX + 100,winY + 120 + posy, 1, 0, "對像模式：", 0);


	if familymode == 0 then
		color[1]=1;
		color[2]=0;
		color[3]=0;
	elseif familymode == 1 then
		color[1]=0;
		color[2]=1;
		color[3]=0;
	elseif familymode == 2 then
		color[1]=0;
		color[2]=0;
		color[3]=1;
	end

	id = sa.StockFontBuffer(winX + 180,winY + 120 + posy, 1, color[1], "傢族", 2);

	if win.getHitFontNo() == id then
		win.ShowBottomLineString(0,"隻有傢族成員方可領取！");
		if win.getMouseLeftCrick() > 0 then
			familymode=0;
		end
	end
	id = sa.StockFontBuffer(winX + 240,winY + 120 + posy, 1, color[2], "全服", 2);
	if win.getHitFontNo() == id then
		win.ShowBottomLineString(0,"全服玩傢都可領取！");
		if win.getMouseLeftCrick() > 0 then
			familymode=1;
		end
	end

	sa.StockFontBuffer(winX + 100,winY + 140 + posy, 1, 0, "領取方式：", 0);

	if getmode == 0 then
		color[1]=1;
		color[2]=0;
	else
		color[1]=0;
		color[2]=1;
	end

	id = sa.StockFontBuffer(winX + 180,winY + 140 + posy, 1, color[1], "拼手氣", 2);
	if win.getHitFontNo() == id then
		win.ShowBottomLineString(0,"玩傢領取的紅包純拼手氣！");
		if win.getMouseLeftCrick() > 0 then
			getmode=0;
		end
	end
	id = sa.StockFontBuffer(winX + 240,winY + 140 + posy, 1, color[2], "平均", 2);
	if win.getHitFontNo() == id then
		win.ShowBottomLineString(0,"玩傢領取的紅包每個都一樣！");
		if win.getMouseLeftCrick() > 0 then
			getmode=1;
		end
	end

	sa.StockFontBuffer(winX + 100,winY + 160 + posy, 1, 0, "紅包個數：", 0);

	id = sa.StockFontBuffer(winX + 180,winY + 160 + posy, 1, 0, "           ", 2);
	if win.getHitFontNo() == id then
		if win.getMouseLeftCrick() > 0 then
			win.InitStrBuffer(winX + 180,winY + 160,2,0,1);
			win.GetKeyInputFocus();
			Focus=1;
		end
	end


	if Focus == -1 then
		sa.StockFontBuffer(winX + 180,winY + 160 + posy, 1, 0,rednum , 2);
		sa.StockFontBuffer(winX + 180,winY + 180 + posy, 1, 0,redValue, 0);
	elseif Focus == 1 then
		sa.StockFontBuffer(winX + 180,winY + 180 + posy, 1, 0,redValue, 0);
		if string.len(win.GetInputMsg()) > 0 then
			rednum = tonumber(win.GetInputMsg());
		end
	elseif Focus == 2 then
		if string.len(win.GetInputMsg()) > 0 then
			redValue = tonumber(win.GetInputMsg());
		end
		sa.StockFontBuffer(winX + 180,winY + 160 + posy, 1, 0,rednum , 2);
	end


	sa.StockFontBuffer(winX + 100,winY + 180 + posy, 1, 0, "總  金  額：", 0);
	id = sa.StockFontBuffer(winX + 180,winY + 180 + posy, 1, 0, "           ", 2);
	if win.getHitFontNo() == id then
		if win.getMouseLeftCrick() > 0 then
			win.InitStrBuffer(winX + 180,winY + 180,6,0,1);
			win.GetKeyInputFocus();
			Focus=2;
		end
	end
	if getmode==0 then
		sa.StockFontBuffer(winX + 300,winY + 180 + posy, 1, 4, "當前為拼手氣紅包", 0);
	else
		sa.StockFontBuffer(winX + 300,winY + 180 + posy, 1, 4, "當前為平均紅包", 0);
	end

	id = sa.StockFontBuffer( winX + 180 , winY + 210 + posy, 1, 4, "塞進紅包", 2);
	if win.getHitFontNo() == id then
		if win.getMouseLeftCrick() > 0 then
			if rednum > 0 then
				if redValue > 0 and redValue >= rednum * 10 then
					if redValue <= vippoint then
						local token = familymode.."|"..getmode.."|"..rednum.."|"..redValue
						lssproto.windows(win.getIndexWN(), win.getIdWN(),1,token);
						win.CloseWindow()
					else
						sa.ShowMessage("您當前的金幣不足！",4)
					end
				else
					sa.ShowMessage("紅包大小不能為0且大於或等於紅包個數的10倍！",4)
				end
			else
				sa.ShowMessage("紅包個數不能為0！",4)
			end
		end
	end
	id = sa.StockFontBuffer(winX + 310,winY + 210 + posy, 1, 4, "關    閉", 2);
	if win.getHitFontNo() == id then
		if win.getMouseLeftCrick() > 0 then
			win.CloseWindow()
		end
	end
	win.StockFontBuffer2();
	if win.DelWindow() == 1 then
		sa.DeathAction(addr)
		win.CloseFlg()
		addr = 0;
		sa.GetKeyInputFocus()
		win.CloseWindow()
	end
	return addr;
end


function data()
	addr=0;
	familymode=0;
	getmode=0;
	rednum=0;
	redValue=0;
	Focus=-1;
end


function main()
	data()
end
