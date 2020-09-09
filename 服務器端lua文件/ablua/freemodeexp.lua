function FreeModeExp( charindex, getexp, modexp )
	local exp = getexp*config.getBattleexp() + ((getexp*modexp*2)/100)
	local fmmap = char.getWorkInt(charindex,"傢族地圖")

	if char.getInt(charindex,"傢族地位")>0 and char.getInt(charindex,"傢族地位")~=2  then
		if char.getChar(charindex, "傢族") == other.getString(family.ShowPointListArray(0), "|", 6) then
			exp = math.floor(exp*1.2)
		elseif char.getChar(charindex, "傢族") == other.getString(family.ShowPointListArray(1), "|", 6) then
			exp = math.floor(exp*1.2)
		end
	end

	return exp
end

function data()

end

function main()
	data()
end
