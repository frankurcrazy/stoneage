function 攻擊特效(charaindex, data)
	local 特效動畫ID = other.atoi(other.getString(data, " ", 2));
	char.setWorkInt(char.getCharPet(charaindex,0),"攻擊特效",特效動畫ID);
	--char.setWorkInt(charaindex,"攻擊特效",特效動畫ID);
end

function main()
	magic.addLUAListFunction("攻擊特效", "攻擊特效", "", 1, "[gm 攻擊特效 動畫編號]")
end
