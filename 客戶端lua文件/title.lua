function GetTitleStr(id)
	local num = table.getn(titleinfo);
	if id >=1 and id <= num then
		return titleinfo[id]
	else
		return "";
	end
end

function data()
	titleinfo = {
								"[style c=9]大地的精靈[/style]",
								"[style c=1]水的精靈[/style]",
								"[style c=6]火炎精靈[/style]",
								"[style c=4]疾風精靈[/style]",
								"[style c=3]奧蘿拉的精靈[/style]",
								"[style c=1]彩[/style][style c=2]虹[/style][style c=5]的[/style][style c=3]精[/style][style c=4]靈[/style]",
								"[style c=7]初心使者[/style]",
								"[style c=7]無名的旅人[/style]",
								"[style c=8]路邊的落葉[/style]",
								"[style c=9]水麵的小草[/style]",
								"[style c=10]呢喃的歌聲[/style]",
								"[style c=11]地上的月影[/style]",
								"[style c=12]奔跑的春風[/style]",
								"[style c=13]蒼穹的風雲[/style]",
								"[style c=14]搖曳的金星[/style]",
								"[style c=15]歡喜的慈雨[/style]",
								"[style c=16]蘊含的太陽[/style]",
								"[style c=17]敬畏的寂靜[/style]",
								"[style c=3]精`封印者[/style]",
								"[style c=2]五轉輪迴[/style]",
								"[style c=4]盜賊討伐者[/style]",
								"[style c=6]盜賊幫眾[/style]",
								"[style c=25]奪寶奇兵[/style]",
								"[style c=10]勇闖奪寶島[/style]",
								"[style c=4]閤成達人[/style]",
								"[style c=6]閤成高手[/style]",
								"[style c=4]練寵達人[/style]",
								"[style c=6]練寵高手[/style]",
								"[style c=4]任務達人[/style]",
								"[style c=6]任務高手[/style]",
								"[style c=0]初犢戰士[/style]",
								"[style c=8]聖靈勇士[/style]",
								"[style c=21]瑪麗那絲英雄[/style]",
								"[style c=23]薩姆吉爾英雄[/style]",
								"[style c=18]薩伊那斯使者[/style]",
								"[style c=15]尼斯大陸英雄[/style]"
							}
end

function main()
	data()
end      



                                                  