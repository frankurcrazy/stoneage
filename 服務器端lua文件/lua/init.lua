function 腳本加載(路徑)
	return dofile(路徑);
end

function 主函數()
	腳本加載("./data/lua/onlineshop/main.lua");
	--時間種子
	math.randomseed(os.time());
end

主函數()

