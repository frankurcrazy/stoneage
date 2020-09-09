function NetLoopFunction()
	if minute > 0 then
		if math.mod(looptime , minute) == 0 then
			char.talkToAllServer("[溫馨提示]" .. message)
		end

		looptime = looptime + 1
	end
end

function announce(charaindex, data)
	message = other.getString(data, " ", 1)
	char.talkToAllServer("[溫馨提示]" .. message)
	minute = other.atoi(other.getString(data, " ", 2))
	looptime = 1
end

function main()
	minute = 0
	magic.addLUAListFunction("公告", "announce", "", 1, "[公告 內容 間隔(分鍾)")
end

